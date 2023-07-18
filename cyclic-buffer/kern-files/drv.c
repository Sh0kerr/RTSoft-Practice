#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>

#define MAX_SIZE_OF_BUFF 256
#define DEVICE_NAME "taskbuff"
#define CLASS_NAME "task"

MODULE_LICENSE("GPL");

static int major_num;
static char buffer[MAX_SIZE_OF_BUFF] = {0};
static short size_of_buffer;
static struct class* TaskbuffClass = NULL;
static struct device* TaskbuffDevice = NULL;

static char* head;
static char* tail;
static bool buffer_full = 0;

static int dev_open(struct inode *, struct file *);
static int dev_release(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char *, size_t, loff_t *);
static ssize_t dev_write(struct file *, const char *, size_t, loff_t *);

static struct file_operations fops = {
	.open = dev_open,
	.release = dev_release,
	.read = dev_read,
	.write = dev_write
};

static int __init dev_init(void) {
	printk(KERN_INFO "Initializing\n");
	
	major_num = register_chrdev(0, DEVICE_NAME, &fops);
	if (major_num < 0) {
		printk(KERN_ALERT "Initialization failed\n");
		return major_num;
	}
	
	TaskbuffClass = class_create(THIS_MODULE, CLASS_NAME);
	TaskbuffDevice = device_create(TaskbuffClass, NULL, MKDEV(major_num, 0), NULL, DEVICE_NAME);
	
	head = buffer;
	tail = buffer;
	memset(buffer, 'f', sizeof(buffer));
	
	printk(KERN_INFO "Initialized successfully\n");
	return 0;
}

static void __exit dev_exit(void) {
	device_destroy(TaskbuffClass, MKDEV(major_num, 0));
	class_unregister(TaskbuffClass);
	class_destroy(TaskbuffClass);
	unregister_chrdev(major_num, DEVICE_NAME);

	printk(KERN_INFO "Closed\n");
}

static int dev_open(struct inode *inodep, struct file *filep) {
	printk(KERN_INFO "Opened\n");
	return 0;
}

static int dev_release(struct inode *inodep, struct file *filep) {
	printk(KERN_INFO "Released\n");
	return 0;
}

static ssize_t dev_read(struct file *filep, char *buff, size_t len, loff_t *offset) {
	if (head == tail && !buffer_full) {
		return -1;
	}
	
	buffer_full = 0;
	char temp[256];
	char* ptr = temp;
	len--;
	
	do {
		*ptr++ = *tail++;
		if(*tail == 0) tail = buffer;
	}while(len-- && head != tail);
	*ptr = 0;

	memset(buff, 0, MAX_SIZE_OF_BUFF);
	copy_to_user(buff, temp, strlen(temp));
	
	printk(temp);

	printk(KERN_INFO "Read\n");
	return size_of_buffer;
}

static ssize_t dev_write(struct file *filep, const char *buff, size_t len, loff_t *offset) {
	if (buffer_full) {
		return -1;
	}
	
	char temp[256];
	memset(temp, 0, 256);
	size_of_buffer = len;
	copy_from_user(temp, buff, len);
	char* ptr = temp;
	
	int counter = 0;
	while(*ptr != 0) {
		*head++ = *ptr++;
		counter++;
		if(*head == 0) head = buffer;
		if(head == tail) {
			buffer_full = 1;
       		if(*ptr != 0) return counter;
		}
	}
	
	printk(KERN_INFO "Written\n");
	return size_of_buffer;
}

module_init(dev_init);
module_exit(dev_exit);

