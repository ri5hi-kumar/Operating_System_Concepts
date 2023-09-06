#include<linux/module.h>
#include<linux/slab.h>
#include<linux/init.h>
#include<linux/kernel.h>
#include<linux/list.h>
#include<linux/types.h>
#include<linux/moduleparam.h>

static int start = 1;

module_param(start, int, 0);

struct series_node {
	int data;
	struct list_head list;
};
static LIST_HEAD(series_list);

static int collatz_module_init(void)
{
	printk(KERN_INFO "module loaded\n");
	if(start < 0) {
		printk(KERN_INFO "Enter a positve number\n");
		return 0;
	}

	int temp = start;

	while(temp != 1) {
		struct series_node *value;
		value = kmalloc(sizeof(struct series_node),
				GFP_KERNEL);
		value->data = temp;
		INIT_LIST_HEAD(&value->list);
		list_add_tail(&value->list, &series_list);

		if(temp % 2 == 0)
			temp /= 2;
		else
			temp = 3 * temp + 1;
	}

	return 0;
}

static void collatz_module_exit(void)
{
	struct series_node *ptr, *temp;
	list_for_each_entry_safe(ptr, temp, &series_list, list) {
		printk(KERN_INFO "%d ", ptr->data);
		list_del(&ptr->list);
		kfree(ptr);
	}

	printk(KERN_INFO "module unloaded\n");
}

module_init(collatz_module_init);
module_exit(collatz_module_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Linked List entry of collatz series");
MODULE_AUTHOR("Rishi");
