#include<linux/init.h>
#include<linux/sched.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<asm/uaccess.h>

static void dfs(struct task_struct *curr, size_t count);

static int task_init(void)
{
	struct task_struct *task;
	printk(KERN_INFO "task module loaded\n");
	printk(KERN_INFO "iterating through tasks linearly\n");
	for_each_process(task) {
		printk(KERN_INFO "command=[%s] state=[%ld] pid=[%d]\n",
				task->comm, task->state, task->pid);
	}
	return 0;
}

static void task_exit(void)
{
	printk(KERN_INFO "iterating through tasks deapth first\n");
	dfs(&init_task, 0);
	printk(KERN_INFO "task module unloaded\n");
}

static void dfs(struct task_struct *curr, size_t count)
{
	struct task_struct *task;
	struct list_head *list;

	if(curr == NULL)
		return;

	if(count >= 100)
		return;

	printk(KERN_INFO "command=[%s] state=[%ld] pid=[%d]\n",
			curr->comm, curr->state, curr->pid);

	list_for_each(list, &curr->children) {
		task = list_entry(list, struct task_struct, sibling);
		dfs(task, count+1);
	}
}

module_init(task_init);
module_init(task_exit);

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("task module");
MODULE_AUTHOR("Rishi");
