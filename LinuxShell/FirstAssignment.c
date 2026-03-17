/*
Μπόμπος Δημόκριτος
csd5064
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <ctype.h>  

char *command;
char *params[50];

int current_pipe_fd[2];
int previous_pipe_fd[2];

int flag_append;
int flag_write;
int flag_read;

char file_append[50];
char file_write[50];
char file_read[50];

FILE *fp_append;
FILE *fp_write;
FILE *fp_read;


int assign_flag;
char assign_r[50];


char *checkAssign(char *input){
	
	assign_flag = 0;
	if(strstr(input,"=") != NULL){
	
		assign_flag = 1;
		char *pos = strstr(input,"=") + 1;
		char *pos1 = pos;
		
		int i = 0;
		int first_space = 1;
		while( *pos != '\0'){		
			if( *pos == '"' ){
				if(first_space == 0)
					break;
			}else if( *pos == '\n' ){
					break;
			}else{
				assign_r[i] = *pos;
				i++;
				assign_r[i] = '\0';
				first_space = 0;
			}
			
			pos++;
		}	
		
		*(pos1-1) = '\0';
		
		
	}
	return input;
}


char *checkAppend(char *input){
	
	flag_append = 0;
	if(strstr(input,">>") != NULL){

		
	
		flag_append = 1;
		char *pos = strstr(input,">>") + 2;
		char *pos1 = pos;

		if(strstr(pos1,">>") != NULL){
			printf("Error in redirections >>\n");
			exit(EXIT_FAILURE);
		}
		
		int i = 0;
		int first_space = 1;
		while( *pos != '\0'){		
			if( *pos == ' ' ){
				if(first_space == 0)
					break;
			}else if( *pos == '\n' ){
					break;
			}else{
				file_append[i] = *pos;
				i++;
				file_append[i] = '\0';
				first_space = 0;
			}
			
			pos++;
		}	
		
		*(pos1-2) = '\0';
		fp_append = fopen(file_append,"a");
		
	}
	return input;
}


char *checkWrite(char *input){
	
	flag_write = 0;
	if(strstr(input,">") != NULL){

		
	
		flag_write = 1;
		char *pos = strstr(input,">") + 1;
		char *pos1 = pos;

		if(strstr(pos1,">") != NULL){
			printf("Error in redirections >\n");
			exit(EXIT_FAILURE);
		}
		
		int i = 0;
		int first_space = 1;
		while( *pos != '\0'){		
			if( *pos == ' ' ){
				if(first_space == 0)
					break;
			}else if( *pos == '\n' ){
					break;
			}else{
				file_write[i] = *pos;
				i++;
				file_write[i] = '\0';
				first_space = 0;
			}
			
			pos++;
		}	
		
		*(pos1-1) = '\0';
		fp_write = fopen(file_write,"w+");
		
	}
	return input;
}


char *checkRead(char *input){
	
	flag_read = 0;
	if(strstr(input,"<") != NULL){

		
	
		flag_read = 1;
		char *pos = strstr(input,"<") + 1;
		char *pos1 = pos;

		if(strstr(pos1,"<") != NULL){
			printf("Error in redirections <\n");
			exit(EXIT_FAILURE);
		}
		
		int i = 0;
		int first_space = 1;
		while( *pos != '\0'){		
			if( *pos == ' ' ){
				if(first_space == 0)
					break;
			}else if( *pos == '\n' ){
					break;
			}else{
				file_read[i] = *pos;
				i++;
				file_read[i] = '\0';
				first_space = 0;
			}
			
			pos++;
		}	
		
		*(pos1-1) = '\0';
		fp_read = fopen(file_read,"r");
		
	}
	return input;
}

void close_read_end(int *fd){
	close(fd[0]);
}

void close_write_end(int *fd){
	close(fd[1]);
}

void save_as_previous_pipe(int *fd, int *pfd){
	pfd[0] = fd[0];
	pfd[1] = fd[1];
}

//for if and for commands
char full_if_command1[2000];
char full_if_command2[2000];
char full_if_command3[20];
char full_if_command4[2000];

int checkIF(char *symbol){
	
					char *left = malloc(100);
					char *right = malloc(100);

					sprintf(left,"%s",strtok (full_if_command1,symbol));
					sprintf(right,"%s",strtok (0,symbol));

					while (isspace((unsigned char)*left)) left++;
					while (isspace((unsigned char)*right)) right++;

					char left1[20];
					sprintf(left1,"%s",strtok (left," "));
					

					char right1[20];
					sprintf(right1,"%s",strtok (right," "));


					int left3;
					int right3;

					if(left1[0]=='$'){
						left=&left1[1];
						char *getenv_ = getenv(left);
						left3=atoi(getenv_);
					}else{
						left3=atoi(left1);
					}

					right3=atoi(right1);

					if(strcmp(symbol,"==")==0){

						if (left3==right3) {
					        //printf("\n\n%d %s %d\nCondition is TRUE\n",left3,symbol,right3);
					        return 1;
					    } else {
					       //printf("\n\n%d %s %d\nCondition is FALSE\n",left3,symbol,right3);
					        return 0;
					    }
					}

					if(strcmp(symbol,"!=")==0){

						if (left3!=right3) {
					        //printf("\n\n%d %s %d\nCondition is TRUE\n",left3,symbol,right3);
					        return 1;
					    } else {
					       //printf("\n\n%d %s %d\nCondition is FALSE\n",left3,symbol,right3);
					        return 0;
					    }
					}


					if(strcmp(symbol,">=")==0){

						if (left3>=right3) {
					        //printf("\n\n%d %s %d\nCondition is TRUE\n",left3,symbol,right3);
					        return 1;
					    } else {
					       //printf("\n\n%d %s %d\nCondition is FALSE\n",left3,symbol,right3);
					        return 0;
					    }
					}

					if(strcmp(symbol,"<=")==0){

						if (left3<=right3) {
					        //printf("\n\n%d %s %d\nCondition is TRUE\n",left3,symbol,right3);
					        return 1;
					    } else {
					       //printf("\n\n%d %s %d\nCondition is FALSE\n",left3,symbol,right3);
					        return 0;
					    }
					}


					if(strcmp(symbol,">")==0){

						if (left3>right3) {
					        //printf("\n\n%d %s %d\nCondition is TRUE\n",left3,symbol,right3);
					        return 1;
					    } else {
					       //printf("\n\n%d %s %d\nCondition is FALSE\n",left3,symbol,right3);
					        return 0;
					    }
					}

					if(strcmp(symbol,"<")==0){

						if (left3<right3) {
					        //printf("\n\n%d %s %d\nCondition is TRUE\n",left3,symbol,right3);
					        return 1;
					    } else {
					       //printf("\n\n%d %s %d\nCondition is FALSE\n",left3,symbol,right3);
					        return 0;
					    }
					}


					return 0;
}

void echo_function(char **tokens, int tokens2){

	int i;
	char *varname;
	char *varval;

	char testBUF[1000];
	
	if(!strcmp(tokens[0], "echo")){

		for(i=0;i<tokens2;i++){

			if(tokens[i]==NULL)
				return;

			varname=strdup(tokens[i]);

			if(*varname=='$'){


				char *token = strtok(varname, "$");

				tokens[i]=malloc(10000);
				tokens[i][0]=0;
    
			    while (token != NULL) {
			        

			    	if ((varval=getenv(token)) != 0) { 
						
						sprintf(testBUF, "%s%s", tokens[i], varval);
						strcpy(tokens[i],testBUF);
					}else{
						
						sprintf(testBUF, "%s$%s", tokens[i], token);
						strcpy(tokens[i],testBUF);
					}


			        token = strtok(NULL, "$");
			    }
				
			}else{

				int firsttime = 1;
				char *token = strtok(varname, "$");

				tokens[i]=malloc(10000);
				tokens[i][0]=0;
    
			    while (token != NULL) {
			        
			    	if(firsttime){
			    		firsttime=0;
			    		strcat(tokens[i],token);
			    	}else{

				    	if ((varval=getenv(token)) != 0) { 
							
							sprintf(testBUF, "%s%s", tokens[i], varval);
							strcpy(tokens[i],testBUF);
						}else{
							
							sprintf(testBUF, "%s$%s", tokens[i], token);
							strcpy(tokens[i],testBUF);
						}
					}


			        token = strtok(NULL, "$");
			    }

			    if(varname!=NULL && *varname=='"'){
			    	varname++;
			    	tokens[i]=varname;
			    }

			    if(varname!=NULL && varname[strlen(varname)-1]=='"'){
			    	varname[strlen(varname)-1]=0;
			    	tokens[i]=varname;
			    }
			    	
			}

		}

	}

}

void insertAt(char **arr, int *size, int capacity, int k, char* value) {
    if (*size >= capacity) {
        printf("Error: array is full, cannot insert.\n");
        return;
    }
    if (k < 0 || k > *size) {
        printf("Error: invalid index.\n");
        return;
    }

    for (int i = *size; i > k; i--) {
        arr[i] = arr[i - 1];
    }

    arr[k] = value;
    (*size)++;
}



int main(){
	
	int EXIT = 0;

	char *buffer_array[50];

	char *buffer = malloc(200);
	buffer[0] = '\0';
	
	char *buffer_bak;
	
	while(!EXIT){
	
		if(buffer[0] == '\0'){
	
			printf("%s@csd5064-hy345sh:%s $  ", getlogin(),getcwd(NULL,0));

			fgets(buffer, 200, stdin);

			while (isspace((unsigned char)*buffer)) buffer++;
		}

		char *pch_first;
		pch_first = strtok (buffer,";");
		int parts = 0;
		int parts_counter = 0;

		while (pch_first != NULL)
		{
			if(parts==50)break;
			buffer_array[parts++]=strdup(pch_first);
			pch_first = strtok (0,";");
		}

		while(parts_counter<parts){
			buffer = strdup(buffer_array[parts_counter++]);


			while (isspace((unsigned char)*buffer)) buffer++;

			if(strncmp("for",buffer,3)==0){//handle for

				sprintf(full_if_command1,"%s", buffer);
				sprintf(full_if_command2,"%s", buffer_array[parts_counter]);
				sprintf(full_if_command3,"%s", buffer_array[parts_counter+1]);
				parts_counter++;
				parts_counter++;


				int keep_parts_counter=parts_counter;

				if(full_if_command1[3]!=' '){printf("Error in for format1"); continue;}

				char *s2=strstr(full_if_command3,"done");
				if(s2==NULL){printf("Error in for format6"); continue;}

				buffer=&full_if_command2[0];
				while (isspace((unsigned char)*buffer)) buffer++;
				sprintf(full_if_command4,"%s", buffer);

				if(strncmp("do",full_if_command4,2)!=0){printf("Error in for format7"); continue;}

				buffer=&full_if_command4[3];

				char *token = strtok(full_if_command1, " ");
				
				if(token==NULL){printf("Error in for format2"); continue;}
				token = strtok(NULL, " ");
				char *var = strdup(token);
				if(token==NULL){printf("Error in for format3"); continue;}
				token = strtok(NULL, " ");
				if(token==NULL){printf("Error in for format4"); continue;}
				token = strtok(NULL, " ");
				if(token==NULL){printf("Error in for format5"); continue;}
    		
    			
			    while (token != NULL) {
			        printf("[%s]\n", token);

			        char new_command[100];
    				sprintf(new_command,"%s=%s",var,token);

    				insertAt(buffer_array, &parts, 50, parts_counter++, strdup(new_command)); 
    				sprintf(new_command,"%s",buffer);
    				insertAt(buffer_array, &parts, 50, parts_counter++, strdup(new_command)); 

			        token = strtok(NULL, " ");
			    }


			    parts_counter=keep_parts_counter;
			    buffer = strdup(buffer_array[parts_counter]);
			    

			}else if(strncmp("if",buffer,2)==0){//handle if
				
				sprintf(full_if_command1,"%s", buffer);
				sprintf(full_if_command2,"%s", buffer_array[parts_counter]);
				sprintf(full_if_command3,"%s", buffer_array[parts_counter+1]);
				parts_counter++;
				parts_counter++;

				if(full_if_command1[2]!=' '){printf("Error in if format1"); continue;}
				char *s=strstr(full_if_command1,"[");
				if(s==NULL){printf("Error in if format2"); continue;}
				else{
					s++;
					if(s==NULL){printf("Error in if format3"); continue;}
					else if(*s!=' '){printf("Error in if format4"); continue;}
				}

				char *s2=strstr(full_if_command1,"]");
				if(s2==NULL){printf("Error in if format5"); continue;}
				else{
					s2--;
					if(s2==NULL){printf("Error in if format6"); continue;}
					else if(*s2!=' '){printf("Error in if format7"); continue;}
				}

				*s2=0;
				
				sprintf(full_if_command1,"%s", s);

				int result;
				if(strstr(full_if_command1,"==")){
					result=checkIF("==");
				}else if(strstr(full_if_command1,"!=")){
					result=checkIF("!=");
				}else if(strstr(full_if_command1,">=")){
					result=checkIF(">=");
				}else if(strstr(full_if_command1,"<=")){
					result=checkIF("<=");
				}else if(strstr(full_if_command1,">")){
					result=checkIF(">");
				}else if(strstr(full_if_command1,"<")){
					result=checkIF("<");
				}else {printf("Error in if format8"); continue;}
					
				buffer=&full_if_command2[0];
				while (isspace((unsigned char)*buffer)) buffer++;
				sprintf(full_if_command4,"%s", buffer);

				if(strncmp("then",full_if_command4,4)!=0){printf("Error in if format9"); continue;}

				buffer=&full_if_command4[4];

				s2=strstr(full_if_command3,"fi");
				if(s2==NULL){printf("Error in if format5"); continue;}


				//printf("\n\n[%s][%s][%s]\n",full_if_command1,buffer,full_if_command3);


				if(result==0){
					buffer[0]=0;
					continue;
				}


			}

			buffer = checkAssign(buffer);

			if(assign_flag){
				
				setenv(buffer,assign_r,50);
				buffer[0] = '\0';
				continue;
			}


			buffer_bak = strdup(buffer);

			char *pch;
			pch = strtok (buffer,"|");


			char *many_commands[50];
			unsigned mcoms=0,mcoms_counter=0;;

			while (pch != NULL)
			{
				if(mcoms==50)break;
				many_commands[mcoms++]=strdup(pch);
				pch = strtok (0,"|");
			}

			while(mcoms_counter<mcoms){

				buffer = strdup(many_commands[mcoms_counter++]);


				buffer = checkAppend(buffer);
				buffer = checkWrite(buffer);
				buffer = checkRead(buffer);

				char *pch = strtok (buffer,"\n \t");
				int i=0;
				command = NULL;
				while (pch != NULL)
				{
					if(i == 0){
						command = strdup(pch);				
					}
					params[i] = strdup(pch);
					i++;
					
					pch = strtok (NULL, "\n \t");
				}
				params[i] = NULL;
			
				int i2=1;	
				if((command != NULL) && (strcmp("echo",command)==0)){
			

					echo_function(params, i);
										
				}

				pipe(current_pipe_fd);//create pipe if needed

				pid_t cpid; //pid tis thugatrikis diergasias

				cpid = fork();
				
				if(cpid == 0){//o kwdikas tou paidiou

					if(flag_append){
						dup2(fileno(fp_append), STDOUT_FILENO);
						
					}
					
					if(flag_write){
						dup2(fileno(fp_write), STDOUT_FILENO);
						
					}
					
					if(flag_read){
						dup2(fileno(fp_read), STDIN_FILENO);
						
					}
					
					if(mcoms!=1 && mcoms_counter!=1)
						dup2(previous_pipe_fd[0],0);
					
					
					if(mcoms_counter!=mcoms && mcoms!=1)	
						dup2(current_pipe_fd[1],1);					
					
					if(mcoms!=1 && mcoms_counter!=1)
						close_read_end(previous_pipe_fd);
					

					if(mcoms!=1 && mcoms_counter!=1)
						close_write_end(previous_pipe_fd);


					if (execvp(command, params) != -1)
							exit(EXIT_SUCCESS);
					else
						printf("Command not found\n");

					exit(EXIT_FAILURE);
				
				}else if(cpid < 0 ){//den egine i dimiourgia tis thugatrikis diergasias
				
					perror("fork failed");
				
				}else{	//o kwdikas tou patera

					if(mcoms_counter>1 && mcoms_counter<=mcoms)
						close_read_end(previous_pipe_fd);

					if(mcoms_counter>1 && mcoms_counter<=mcoms)
						close_write_end(previous_pipe_fd);

					save_as_previous_pipe(current_pipe_fd,previous_pipe_fd);

					int status;
					waitpid(-1, &status, WUNTRACED);	//perimenei ola tou ta paidia na teleiwsoun
					
				}
						
			}
			buffer[0] = '\0';
			
		}
	}
}


