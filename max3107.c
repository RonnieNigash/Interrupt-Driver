#include <linux/module.h>
#include <linux/kernel.h> // KERN_ALERT
#include <linux/init.h> // __init, __exit macros

// Global variables
static int loopback = 0;
// End globals

MODULE_PARAM(loopback, "i"); // loopback is an integer type --> "i"
MODULE_PARAM_DESC(loopback, "Set to 1 to enable loopback (connect rx and tx) on max3107");
// usage: $ insmod max3107.ko loopback=1

static void __init max3107_register_init(struct max3107_port *s)
{

}

static int __init max3107_init(void)
{
	int major = register_chrdev(0, THIS_MODULE, &operations);

	printk( KERN_ALERT "%s: Registering device with %d\n", __FUNCTION__, major);
	if ( major < 0 ) {
		printk( KERN_ALERT "%s: Registering device failed with %d\n", __FUNCTION__, major);
		return major;
	}

	// loop across uarts in group
	// 	init registers
	
	return 0;
}

static void __exit max3107_exit(void)
{
	printk( KERN_ALERT "%s: Unregistering device with %d\n", __FUNCTION__, major);

	// @TODO: unregister driver
}

module_init(max3107_init);
module_exit(max3107_exit);

MODULE_DESCRIPTION("MAX3107 Driver");
MODULE_AUTHOR("Ronnie Nigash");
MODULE_ALIAS("max3107-i2c");
MODULE_LICENSE("GPL");
