# obj-m += hello.o
# obj-m += hello5.o
# obj-m += chardev.o
# obj-m += golden_ratio.o
# obj-m += jiffies.o
obj-m += proc_seconds.o

KDIR := /lib/modules/$(shell uname -r)/build

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean

