#include <linux/module.h>
#include <linux/delay.h>
#include <linux/i2c.h>
#include <linux/err.h>
#include <linux/platform_device.h>
#include <linux/clk.h>
#include <linux/io.h>
#include <linux/of.h>
#include <linux/of_device.h>
#include <linux/slab.h>
#include <linux/platform_data/i2c-omap.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>
#include <linux/spinlock.h>
#include <asm/uaccess.h>
#include "i2c_char.h"


static struct omap_i2c_dev i2c_dev;

int i2c_transmit(struct i2c_msg *msg, size_t count)
{
	ENTER();
	return 0;
}

int i2c_receive(struct i2c_msg *msg, size_t count)
{	
	ENTER();
	return 0;
}


static int __init omap_i2c_init_driver(void)
{

	printk(KERN_ALERT "TONY: omap_i2c_init_driver\n");
	/* Char interface related initialization */
	// TODO: Create the class with name i2cdrv

	if (IS_ERR(i2c_dev.i2c_class = class_create(THIS_MODULE, "i2cdrv")))
	{
		printk(KERN_ALERT "TONY: Error 2\n");
		unregister_chrdev_region(i2c_dev.devt, 1);
		return PTR_ERR(i2c_dev.i2c_class);
	}

	// TODO: Initialize the character driver interface
	chrdrv_init(&i2c_dev);

	return 0;
}

static void __exit omap_i2c_exit_driver(void)
{
	printk(KERN_ALERT "TONY: omap_i2c_exit_driver\n");
	// TODO: De-initialize the character driver interface
	chrdrv_exit(&i2c_dev);
	// TODO: Delete the i2cdrv class
	class_destroy(i2c_dev.i2c_class);
}

module_init(omap_i2c_init_driver);
module_exit(omap_i2c_exit_driver);

MODULE_AUTHOR("SysPlay Workshops <workshop@sysplay.in>");
MODULE_DESCRIPTION("Low level I2C driver");
MODULE_LICENSE("GPL");
