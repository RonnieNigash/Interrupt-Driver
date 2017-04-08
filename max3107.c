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

static void __init max3107_register_init(struct max3107_port *s)
{
	// disable Tx and Rx
	// Disable interrupt bit
	// Clear Fifos
	// Read Clear on Reads
	// Enable Hardware Flow Control
	// END Clear Fifos
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
