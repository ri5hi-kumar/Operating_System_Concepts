#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#include "list.h"
#include "schedulers.h"
#include "task.h"
#include "cpu.h"

struct node *tasklist = NULL;

void add(char *name, int priority, int burst) {
	Task *t = malloc(sizeof(Task));
	t->name = malloc(sizeof(char) * (strlen(name) + 1));
	strcpy(t->name, name);
	t->priority = priority;
	t->burst = burst;

	insert(&tasklist, t);
}

Task *pickNext() {
	struct node *last = tasklist;
	while(1) {
		if(last->next == NULL)
			break;
		last = last->next;
	}
	return last->task;
}

void schedule() {
	while(tasklist) {
		Task *t = pickNext();
		run(t, t->burst);
		delete(&tasklist, t);
	}
}
