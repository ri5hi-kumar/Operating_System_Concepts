#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>

#define MIN_PID 300
#define MAX_PID 5000
#define BITMAP_SIZE (MAX_PID - MIN_PID + 1)

typedef struct {
	int min_pid;
	int max_pid;
	unsigned char *bitmap;
}PidManager;

int allocate_map(PidManager *manager){
	manager->bitmap = (unsigned char *)calloc(BITMAP_SIZE/8 + 1, 
			sizeof(unsigned char));
	if(manager->bitmap == NULL){
		return -1;
	}

	manager->min_pid = MIN_PID;
	manager->max_pid = MAX_PID;

	return 1;
}

int allocate_pid(PidManager *manager){
	for(int i = manager->min_pid; i <= manager->max_pid; i++){
		int index = (i - manager->min_pid) / 8;
		int bit = (i - manager->min_pid) % 8;

		if((manager->bitmap[index] & (1 << bit)) == 0){
			manager->bitmap[index] |= (1 << bit);
			return i;
		}
	}

	return -1;
}

void release_pid(PidManager *manager, int pid){
	if(pid < manager->min_pid || pid > manager->max_pid){
		printf("Invalid pid: %d\n", pid);
		return;
	}
	int index = (pid - manager->min_pid) / 8;
	int bit = (pid - manager->max_pid) % 8;

	manager->bitmap[index] &= ~(1 << bit);
}

int main(){
	PidManager manager;
	int pid;

	if(allocate_map(&manager) == -1){
		printf("Unable to allocate map\n");
		return 1;
	}

	pid = allocate_pid(&manager);

	if(pid != -1){
		printf("Allocated: %d\n", pid);
	}
	else{
		printf("No PIDs Available\n");
	}

	release_pid(&manager, pid);

	free(manager.bitmap);

	return 0;
}
