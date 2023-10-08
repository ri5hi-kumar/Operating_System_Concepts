#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "list.h"
#include "schedulers.h"
#include "task.h"
#include "cpu.h"

struct node *tasklist = NULL;
struct node *next_node;

void add(char *name, int priority, int burst) {
	Task *t = malloc(sizeof(Task));
	t->name = malloc(sizeof(char) * (strlen(name) + 1));
	strcpy(t->name, name);
	t->priority = priority;
	t->burst = burst;

	insert(&tasklist, t);
}

Task *pickNext() {
	if(!next_node)
		next_node = tasklist;
	Task *ret = next_node->task;
	next_node = (next_node->next) ? next_node->next : tasklist;
	return ret;
}

void schedule() {
	while(tasklist) {
		Task *t = pickNext();
		int slice = QUANTUM < t->burst ? QUANTUM : t->burst;
		run(t, slice);
		t->burst -= slice;
		if(t->burst == 0) {
			delete(&tasklist, t);
		}
	}
}
