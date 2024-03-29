#include <linux/module.h>
#include <linux/kernel.h> // KERN_ALERT
#include <linux/init.h> // __init, __exit macros
#include <linux/device.h>

#include "max3107.h"

// Global variables
static int loopback = 0;
// End globals

MODULE_PARAM(loopback, "i"); // loopback is an integer type --> "i"
MODULE_PARAM_DESC(loopback, "Set to 1 to enable loopback (connect rx and tx) on max3107");
// usage: $ insmod max3107.ko loopback=1

static const struct max3107_group groups [] = {
	[0] = {
	.i2cBus = 0,
	.irqLine = ER_GPIO_00,
	.irqBitMask = 0x1,
	.uartDriver = {
		.owner = THIS_MODULE,
		.driver_name = "max3107-0",
		.dev_name = "max3107-0",
		.major = 207,
		.minor = 200,
		.nr = 4,
	},
	.portCount = 1;
	.ports = {
		[0] = {
			.name = "Bus 0 Slave 0",
			.index = 0,
			.address = 0x2F,
			.uartclk = 9600,
			.dtrGPIO = MAX3107_GPIOCFG_GP0OUT_BIT,
			.dsrGPIO = MAX3107_GPIOCFG_GP1OUT_BIT,
			.carGPIO = MAX3107_GPIOCFG_GP2OUT_BIT,
			}
		}
	}
};

static void __init i2cWriteBitsOn()
{

}

static void __init i2cWriteBitsOn()
{

}

static void __init max3107_register_init(struct max3107_data *dp)
{
	struct i2c_client *client = &dp->i2cClient;

	// Reset FIFOs to get into a known clean state
	i2cWriteBitsOn( client, MAX3107_MODE2_REG, MAX3107_MODE2_RST_BIT );
	i2cWriteBitsOff( client, MAX3107_MODE2_REG, MAX3107_MODE2_RST_BIT );


	// Configure Baud Rate
	s->baud = 9600;
	//I2Cdev.writeBit( device address, register address, bit number, data );

	// Configure LCR Register to be 8N1
	s->lcr_reg = MAX3107_LCR_WORD_LEN_8;
	//I2Cdev.writeBit( device address, register address, bit number, data );
	
	s->mode1_reg = 0;
	// Enable Interrupt Bit
	s->mode1_reg |= MAX3107_MODE1_IRQSEL_BIT;
	// Disable TX
	s->mode1_reg |= MAX3107_MODE1_TXDIS_BIT;
	s->tx_enabled = 0;
	s->rx_enabled = 1;
	//I2Cdev.writeBit( device address, register address, bit number, data );
	
	s->mode2_reg |= MAX3107_WRITE_BIT;
	//I2Cdev.writeBit( device address, register address, bit number, data );
	if (loopback) {
		s->mode2_reg |= MAX3107_MODE2_LOOPBACK_BIT;
	}
	// Reset FIFOs
	s->mode2_reg |= MAX3107_MODE2_FIFORST_BIT;
	s->tx_fifo_empty = 1;
	//I2Cdev.writeBit( device address, register address, bit number, data );
	
	// Read Clear on Reads
	//I2Cdev.readBit( device address, register address, bit number, data );

	// Configure flow control levels
	
	//I2Cdev.writeBit( device address, register address, bit number, data );
	
	// Enable Hardware Flow Control
	
	//I2Cdev.writeBit( device address, register address, bit number, data );
	
	// Configure RX Timeout Register
	
	//I2Cdev.writeBit( device address, register address, bit number, data );
	
	// Configure LSR interrupt enable
	
	//I2Cdev.writeBit( device address, register address, bit number, data );
	
	// Clear IRQ Status with a Read (Clear on Read register)
	
	//I2Cdev.writeBit( device address, register address, bit number, data );
	
	// Configure interrupt enable register

	//I2Cdev.writeBit( device address, register address, bit number, data );
	
	// END Clear Fifos
	s->mode2_reg &= ~MAX3107_MODE2_FIFORST_BIT;
	//I2Cdev.writeBit( device address, register address, bit number, data );
}

static int max3107_probe(struct i2c_dev *cp, struct max3107_data *data)
{
	struct max3107_port *port;
	int return_val;

	port = kzalloc(sizeof(*port), GFP_KERNEL);
	if (!port) {
		printk(KERN_ERR "%s: Allocating port struct failure\n", __FUNCTION__);
		return -ENOMEM;
	}

	port->data = data;

	// Setup i2c for rx and tx
	// take the spinlock
	// initialize the i2c bus using the i2c group
	// Disable interrupts
	// Configure clock source
	// Initialize the virtual port data to keep track of physical nvram
	// release lock
}

static int max3107_power(struct device *dev)
{
	// i2c write to the registry bits to enable power on	
}

static int max3107_detect(struct device *dev)
{
	struct uart_port *up = dev_get_drvdata(dev);
	unsigned int value = 0;
	int registered;

	registered = regmap_read(s->regmap, MAX3107_REVID_REG, &value);
	if (registered)
		return registered;

	if ( ( (value & MAX3107_REV_MASK) != (MAX3107_REV_ID) ) ) {
		printk(KERN_ERR "%s: ID 0x%02x does not match\n", __FUNCTION__, up->devtype->name, value)
	}

	return 0;
}

static const struct max3107_devtype = {
	char name[9] 				= "MAX3107",
	int nr					= 1,
	int (*detect)(struct device *) 		= max3107_detect,
	void (*power)(struct uart_port *, int)	= max3107_power,
};

static const struct i2c_device_id max3107_id_table[] = {
	{ "max3107", (kernel_ulong_t)&max3107_devtype, }
};
MODULE_DEVICE_TABLE(i2c, max3107_id_table);

static struct i2c_driver max3107_uart_driver = {
	.driver = {
		.name	= "max3107",
	},
	.probe		= max3107_probe,
	.remove		= max3107_remove,
	.id_table	= max3107_id_table,
};

static int __init max3107_init(void)
{
	int registered;

	registered = uart_register_driver(&max3107_uart);
	if (registered) {
		prink(KERN_ALERT "Registering MAX3107 Driver failed\n");
		return registered;
	}

	registered = i2c_add_driver(&max3107_uart_driver);
	if (registered < 0) {
		printk(KERN_ALERT "Failed to initalize max3107 uart i2c : %d\n", registered);
		return registered;
	}

	return registered;
}
module_init(max3107_init);

static void __exit max3107_exit(void)
{
	i2c_del_driver(&max3107_uart_driver);

	uart_unregister_driver(&max3107_uart);
}
module_exit(max3107_exit);

MODULE_DESCRIPTION("MAX3107 Driver");
MODULE_AUTHOR("Ronnie Nigash");
MODULE_ALIAS("max3107-i2c");
MODULE_LICENSE("GPL");
