
#include <stdio.h>
#include <unistd.h>
#include <errno.h>

struct d_params {
	int deadline;
	int est_runtime;
};

#define set_proc_info(x1, x2) syscall(341, x1, x2)
#define get_proc_info(x1) syscall(342, x1)

int period = 0;

int main(int argc, char *argv[]){
	printf("Trap to kernel level\n");

	int return_value;

	if(argc!=3){
		printf("%s [deadline] [est_runtime]\n",argv[0]);
		return -1;
	}

	int x = atoi(argv[1]);
	int y = atoi(argv[2]);
	
	return_value  = set_proc_info(x,y);
	while(1){
		while(1){
			while(1){
				while(1){
					while(1){
						x+1000*x+x+1000*x;
						y+1000*y+y+1000*y;
						break;
					}
					break;
				}
				break;
			}
			break;
		}
	}


	printf("Back to user level\n");


return 0;

}


