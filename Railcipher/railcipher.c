#include "railcipher.h"


int m;//key length...
static int is_integer(char* arg){
	//Step 1: check if all chars in arg are digits
	int len = strlen(arg);
	for(int i = 0; i < len;i++)
		if(!isdigit(arg[i]))
			return 0;
	//Step 2: convert the arg to int using atoi (ASCII to INTEGER)
	return atoi(arg);
}
static int is_valid_permutation(int* key){
	int* visited = (int*)malloc((m+1) * sizeof(int));
	for(int i = 1; i <= m;i++)
		visited[i] = FALSE;
	for(int i = 0; i < m;i++)
		if(key[i] > m || visited[key[i]])
			return FALSE;
		else
			visited[key[i]] = TRUE;
	return TRUE;
}
int main(int argc, char* argv[]){
	int* key;//array of integers stored in the heap!
	//error("This is a test!", 5);
	if(argc < 3)
		error("Too few args!", 4);
	for(int i = 1; i < argc; i++){
		//argv[i] must be a positive integer
		int val = is_integer(argv[i]);
		if(val < 1)
			error("One of the CLAs is not a positive integer", 1);
		else if(i == 1){//it's the key length
			key = (int*)malloc(val * sizeof(int));
			if(!key)
				error("Low memory in heap!", 2);
			if(argc != val + 2)
				error("key length is not valid!", 3);
			m = val;//m = atoi(argv[1])
		}else//i= 2, 3, 4, ..., m+1
			key[i-2] = val;
	}
	if(!is_valid_permutation(key))
		error("key must be a valid permutation of numbers from 1 to key length!", 5);
	char command[MAX_LEN];
	while(fgets(command, MAX_LEN, stdin)){
		int len = strlen(command);
		if(command[len-1] == '\n')//get rid of new line at the end!
			command[len-1] = '\0';
		if(!strcmp(command, "quit"))
			exit(0);
		if(!strncmp(command, "encrypt ", 8))
			encrypt(strdup(command+8), key);
		else if(!strncmp(command, "decrypt ", 8))
			decrypt(strdup(command+8), key);
		else//illegal command
			printf("Illegal command entered. Use quit, encrypt, or decrypt!\n");
	}
	
	free(key);
	return 0;
}