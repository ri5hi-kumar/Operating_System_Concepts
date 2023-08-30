#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/hash.h>
#include<linux/gcd.h>

static int __init golden_module_init(void){
	pr_info("%lu\n", GOLDEN_RATIO_PRIME);
	return 0;
}

static void __exit golden_module_exit(void){
	pr_info("%lu\n", gcd(3300, 24));
}

module_init(golden_module_init);
module_exit(golden_module_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Golden Ratio Module");
MODULE_AUTHOR("Rishi");
