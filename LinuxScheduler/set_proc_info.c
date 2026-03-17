#include <linux/kernel.h>
#include <linux/syscalls.h>
#include <asm/uaccess.h>

asmlinkage long sys_set_proc_info(int deadline, int est_runtime){

	int OK = 1;
	printk("csd5064 called system call sys_set_proc_info with arguments: %d, %d\n",
		deadline, est_runtime);

	if(deadline <= 0) {
		printk("csd5064 deadline should be greater than zero\n");
		OK = 0;
	}
	if(est_runtime <= 0) {
		printk("csd5064 est_runtime should be greater than zero\n");
		OK = 0;
	}

	if(est_runtime>1000*deadline) {
		printk("csd5064 est_runtime>deadline\n");
		OK = 0;
	}

	if(OK){
			current->deadline = deadline;
			current->est_runtime = est_runtime;
			current->ltf_process=1;
			OK = 1;
	}else{
		OK=0;
	}

	if(OK){
		printk("csd5064 SET DONE\n");
		return 0;
	}
	else {
		printk("csd5064 PARAMS ERROR\n");
	}

	return EINVAL;
}