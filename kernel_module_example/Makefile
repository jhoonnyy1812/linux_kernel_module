obj-m += kernel_module_example.o
all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules
clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
test:
	sudo dmesg -C
	sudo insmod kernel_module_example.ko
	sudo rmmod kernel_module_example.ko
	dmesg