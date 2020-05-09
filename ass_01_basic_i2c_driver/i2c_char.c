#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/errno.h>
#include <asm/uaccess.h>
#include <linux/slab.h>
#include <linux/platform_data/serial-omap.h>
#include "i2c_char.h"

static int my_open(struct inode *i, struct file *f)
{
	return 0;
}

static int my_close(struct inode *i, struct file *f)
{
	return 0;
}

static ssize_t my_read(struct file *f, char __user *buf, size_t count, loff_t *off)
{
	// TODO: Add the code here
	printk(KERN_ALERT "my_read done\n");
	//i2c_receive(struct i2c_msg *i2c_msg, size_t len);
	return 0;
}

static ssize_t my_write(struct file *f, const char __user *buf, size_t count, loff_t *off)
{
	// TODO: Add the code here
	printk(KERN_ALERT "my_write done\n");
	return count;
}

static struct file_operations driver_fops =
{
	.owner = THIS_MODULE,
	.open = my_open,
	.release = my_close,
	.read = my_read,
	.write = my_write
};

int chrdrv_init(struct omap_i2c_dev *i2c_dev)
{
	static int i2c_num = 0;
	struct device *dev_ret;
	int ret;

	int init_result = alloc_chrdev_region(&i2c_dev->devt, 0, 1, "i2c_drv");

	if (0 > init_result)
	{
		printk(KERN_ALERT "Device Registration failed\n");
		return -1;
	}
	printk("Major Nr: %d\n", MAJOR(i2c_dev->devt));

	// TODO: Create the device file

	if (IS_ERR(dev_ret = device_create(i2c_dev->i2c_class, NULL, i2c_dev->devt, NULL, "myi2c")))
	{
		printk(KERN_ALERT "TONY: Error 3\n");
		class_destroy(i2c_dev->i2c_class);
		unregister_chrdev_region(i2c_dev->devt, 1);
		return PTR_ERR(dev_ret);
	}

	// TODO: Register the file_operations
    	cdev_init(&i2c_dev->cdev, &driver_fops);

	if ((ret = cdev_add(&i2c_dev->cdev, i2c_dev->devt, 1)) < 0)
	{
		printk(KERN_ALERT "TONY: Error 4\n");
		device_destroy(i2c_dev->i2c_class, i2c_dev->devt);
		class_destroy(i2c_dev->i2c_class);
		unregister_chrdev_region(i2c_dev->devt, 1);
		return ret;
	}

	printk(KERN_INFO "chrdrv_init successful");
	return 0;
}

void chrdrv_exit(struct omap_i2c_dev *i2c_dev)
{
	// TODO: Delete the device file
	device_destroy(i2c_dev->i2c_class, i2c_dev->devt);
	// TODO: Unregister file operations
	cdev_del(&i2c_dev->cdev);
	// TODO: Unregister character driver
	unregister_chrdev_region(i2c_dev->devt, 1);
    
	printk(KERN_INFO "Alvida: chrdrv_exit");
}

