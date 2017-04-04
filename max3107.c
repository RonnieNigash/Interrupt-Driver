#include <linux/kernel.h>
#include <linux/module.h>


__init int max3107_init(void)
{
	int major = register_chrdev(0, THIS_MODULE, &operations);

	printk( KERN_INFO "%s: Registering device with %d\n", __FUNCTION__, major);
	if ( major < 0 ) {
		printk( KERN_INFO "%s: Registering device failed with %d\n", __FUNCTION__, major);
		return major;
	}
	// @TODO: init the registers in max3107
	
	return 0;
}

static void __exit max3107_exit(void)
{
	printk( KERN_INFO "%s: Registering device with %d\n", __FUNCTION__, major);

	// @TODO: unregister driver
}

module_init(max3107_init);
module_exit(max3107_exit);

MODULE_DESCRIPTION("MAX3107 Driver");
MODULE_AUTHOR("RonnieNigash");
MODULE_ALIAS("max3107-i2c");
MODULE_LICENSE("GPL");
