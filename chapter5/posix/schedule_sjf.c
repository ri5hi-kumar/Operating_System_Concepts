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
	Task *shortest = tasklist->task;
	struct node *temp = tasklist;
	while(temp) {
		if(temp->task->burst < shortest->burst)
			shortest = temp->task;
		temp = temp->next;
	}
	return shortest;
}

void schedule() {
	while(tasklist) {
		Task *t = pickNext();
		run(t, t->burst);
		delete(&tasklist, t);
	}
}
