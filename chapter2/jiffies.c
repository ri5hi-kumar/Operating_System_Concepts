#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/jiffies.h>
#include<asm/param.h>

unsigned long start;

static int __init jiffies_module_init(void){
	start = jiffies;
	pr_info("Jiffies module is installed\n");
	pr_info("HZ: %lu\n", HZ);
	pr_info("Jiffies at start: %lu\n", start);
	return 0;
}

static void __exit jiffies_module_exit(void){
	unsigned long end = jiffies;
	unsigned long diff = end - start;
	pr_info("Jiffies module is removed\n");
	pr_info("Jiffies at end: %lu\n", end);
	pr_info("In between: %lu\n", diff);
}

module_init(jiffies_module_init);
module_exit(jiffies_module_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Golden Ratio Module");
MODULE_AUTHOR("Rishi");
