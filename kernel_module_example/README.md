# Simple linux kernel module example

Steps:
1. To make all kernel module files and dependencies:

```bash
make all
```

2. To add this module to linux kernel:

```bash
sudo insmod kernel_module_example.ko
```

3. Now the module was added and the init function was called `module_init(linux_kernel_module_init);` and it printed the code inside `linux_kernel_module_init`, but `printk` function is different than `printf` function and it does not print in the console, it adds the message to the kernel log and you can read it using:

```bash
sudo dmesg
```

4. The message `Hello, World!` should stay in the bottom of the log.

5. To check if the module is running on kernel yet you need to check all the modules running:

```bash
lsmod
```

and the module name should be on top, or you call call

```bash
lsmod | grep kernel_module_example
```

and it will return `kernel_module_example` if it's running.

6. To remove the module:

```bash
sudo rmmod kernel_module_example
```

7. Try to read the kernel log again and it will show the message `Goodbye, World!`.

8. To clean the log:

```bash
sudo dmesg -C
```

9. To run this tests in automode (you will just see the messages):

```bash
make test
```
