#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define error(m,c) do{fprintf(stdout,"%s\n", m); exit(c);}while(0)
#define MAX_LEN 1024
struct node{
	char* string;
	struct node* next;
};
typedef struct node node;//shorten the data type identifier
typedef struct{
	char* min_word;
	node* head;
} bucket;
int main(int argc, char* argv[]){
	if(argc < 2)
		error("bucketsort: Too few arguments!", 1);
	//array of buckets...
	int no_buckets = argc;
	//store the array in the heap!
	bucket* buckets = (bucket*) malloc(no_buckets*(sizeof(bucket)));
	//initialize every bucket and its variables based on CLAs
	for(int index = 0; index < no_buckets;index++){
		if(index == 0){
			//(buckets + index)->min_word = "";
			buckets[index].min_word = "";
		}else{
			buckets[index].min_word = argv[index];
			if(strcasecmp(buckets[index].min_word, 
				buckets[index-1].min_word) <= 0)
				error("bucketsort: CLAs must be sorted increasingly!", 2);
		}
		buckets[index].head = NULL;
	}
	char line[MAX_LEN];
	while(fgets(line, MAX_LEN, stdin)){
		char* word = strtok(line, " ");
		while(word){
			node* current = (node*) malloc(sizeof(node));
			//current->string = (char*)malloc(strlen(word) + 1);
			//strcpy(current->string, word);
			current->string = strdup(word);
			//1. find the appropriate bucket for word....

            for(int i =0;i<no_buckets;i++)
            {
                if(strcasecmp(buckets[i].min_word, current -> string)<1 && i == no_buckets-1) 
                {//if head of bucket is empty 
                    if(buckets[i].head == NULL ){
                       buckets[i].head = current;
                       buckets[i].head->next = NULL;
                    }
                    else {
                        //if head of bucket is not empty 
                        node* temper =  malloc(sizeof(node));
                        node* storage =  malloc(sizeof(node));
                        node* new =  malloc(sizeof(node));
                        temper= buckets[i].head;
                        while(temper -> next != NULL) {
                            if(strcasecmp(temper->string, current -> string) < 1 && strcasecmp(temper->next->string, current -> string)>0)
                            {
                                storage = temper->next;
                                new -> string= current ->string;
                                temper->next = new;
                                new -> next = storage;


                            }
                            temper = temper -> next;

                        }
                        if(temper->next == NULL){
                            if(strcasecmp(temper->string, current -> string)>0) {
                                if(buckets[i].head == temper)
                                {
                                    new -> string= current ->string;
                                    new -> next = temper;      
                                    buckets[i].head = new;
                                }
                            }
                            else {
                            new -> string= current ->string;
                            new -> next = NULL;      
                            temper-> next = new;
                            }
                        }
                    
                    }
                }

                else if(strcasecmp(buckets[i].min_word, current -> string) < 1 && strcasecmp(buckets[i+1].min_word, current -> string)>0) 
                {//if head of bucket is empty 
                    if(buckets[i].head == NULL ){
                       buckets[i].head = current;
                       buckets[i].head->next = NULL;
                    }
                    else {
                        //if head of bucket is not empty 
                        node* temper =  malloc(sizeof(node));
                        node* storage =  malloc(sizeof(node));
                        node* new =  malloc(sizeof(node));
                        temper= buckets[i].head;
                        while(temper -> next != NULL) {
                            if(strcasecmp(temper->string, current -> string) < 1 && strcasecmp(temper->next->string, current -> string)>0)
                            {
                                storage = temper->next;
                                new -> string= current ->string;
                                temper->next = new;
                                new -> next = storage;


                            }
                            temper = temper -> next;

                        }
                        if(temper->next == NULL){
                            if(strcasecmp(temper->string, current -> string)>0) {
                                if(buckets[i].head == temper)
                                {
                                    new -> string= current ->string;
                                    new -> next = temper;      
                                    buckets[i].head = new;
                                }
                            }
                            else {
                                new -> string= current ->string;
                                new -> next = NULL;      
                                temper-> next = new;
                            }
                        }
                    
                    }
                }
            }





			//2. insert the node current in the appropriate bucket
			word = strtok(NULL, " ");
		}
	}
	for(int index = 0; index < no_buckets;index++){
		if(buckets[index].head){
			printf("bucket %d:", index);
			node* temp = buckets[index].head;
			while(temp!= NULL){
				printf(" %s", temp->string);
				temp = temp->next;
			}
			printf("\n");
		}
	}	
}