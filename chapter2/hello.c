#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>

static int __init hello_module_init(void){
	printk(KERN_INFO "Hello world\n");
	return 0;
}

static void __exit hello_module_exit(void){
	printk(KERN_INFO "Goodbye world!\n");
}

module_init(hello_module_init);
module_exit(hello_module_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Seconds Module");
MODULE_AUTHOR("CHATgpt");
