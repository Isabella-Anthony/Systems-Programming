#include<string.h>
#include<stdio.h>
#include<stdlib.h>
#include <pthread.h>
#include <time.h>
#define BUFFER_SIZE 2000000L
//#define THREADS 20
// #define LEN 5
#define MAX_COUNT 3000


pthread_mutex_t bin_search_mutex;
pthread_mutex_t solution_count_mutex;

int initial=8;
int LEN =9;
int sorted=0;
int distinct=0;
int t_time=0;
int solution_count=0;
int THREADS=1;
char* solution_bank[MAX_COUNT];

long total_Binary_Search_Time=0;
char* buffer[20];
int dictionary_size;
char* dict[100000];

static long get_nanos(void) {
    struct timespec ts;
    timespec_get(&ts, TIME_UTC);
	return (long)ts.tv_sec * 1000000000L + ts.tv_nsec;
}

int binsearch(char* dictionary_words[],int list_size,char* keyword){
	int mid, low = 0, high = list_size - 1;
	while (high >= low) {
		mid = low + (high - low) / 2;
		if (strcmp(dictionary_words[mid],keyword) < 0)
			low = mid + 1;
		else if (strcmp(dictionary_words[mid],keyword)>0)
			high = mid - 1;
		else
			return mid;
	} 
	return -1; //not found
}
void swap(char* v[], int i, int j){
    char* temp = v[i];
    v[i] = v[j];
    v[j] = temp;
}
void generic_qsort(char* v[], int left, int right){
    int i, last;
    if(left >= right) return;//base case
    swap(v, left, (left + right)/2);//pivot
    last = left;
    for(i = left + 1; i <= right; i++)
        if(strcmp(v[i], v[left]) < 0)
            swap (v, ++last, i);
    swap(v, left, last);
    generic_qsort(v, left, last - 1);
    generic_qsort(v, last + 1, right);
}

void delete_duplicates(char* v[], int size){
  
    for(int i =0; i < size; i++){
     
        for(int j=i+1; j< size;j++){


            if(v[i] == v[j]){ //dupes found 
                   for(int k=j; k< size;k++){
                     // printf("Dupefound\n");
                     v[k]=v[k+1];
                    // size--;
                  }
             }
        }
    }
 }

int verbose = 0;
void* word_puzzle_solver(void* id){
    char c = 0;
	int i, n = BUFFER_SIZE/THREADS-LEN;
	char* buf = buffer[(int)id];
    
    
    if(verbose){
        fprintf(stdout, "Note: Thread #%d: %s\n", (int) id, "started!");
    }

    for(int len=initial; len<=LEN;len++) {
          n = BUFFER_SIZE/THREADS-LEN;

        for(i = 0; i < n;i++){
            if(c)
                buf[i + len - 1] = c;
            c = buf[i + len];
            buf[i + len] = '\0';

            long start = get_nanos();
            int result = binsearch(dict, dictionary_size, buf+i);

            pthread_mutex_lock(&bin_search_mutex);
            total_Binary_Search_Time += (get_nanos()-start);
            pthread_mutex_unlock(&bin_search_mutex);

            if(result + 1){ //if search is successful !
                if(sorted || distinct){
                    pthread_mutex_lock(&solution_count_mutex);
                    solution_bank[solution_count++] = strdup(buf+i); 
                    pthread_mutex_unlock(&solution_count_mutex);
                }
                else{
                    printf("Thread #%d: %s\n",(int)id, buf + i);
                }
            }
        }    
	  }
    
}
void main(int argc, char* argv[] ){
    //initialize mutex
    	pthread_mutex_init(&bin_search_mutex, NULL);
        pthread_mutex_init(&solution_count_mutex, NULL);

    for(int i=1;i<argc;i++){
        if(strcmp(argv[i],"-len") == 0){
			char cla[10];
			strcpy(cla,argv[i+1]);
			int size_cla = strlen(cla)-1;
			initial = atoi(&cla[0]);
			LEN = atoi(&cla[size_cla]);
			

		}     
         if(strcmp(argv[i], "-nthreads")== 0){
            THREADS = atoi(argv[++i]); 
        }
         if(strcmp(argv[i],"-verbose")== 0){
            verbose=1;
        }
         if(strcmp(argv[i], "-time")== 0){
            t_time=1;
        }
         if(strcmp(argv[i], "-sorted")== 0){
            sorted =1;
        }
         if(strcmp(argv[i], "-distinct")== 0){
            distinct=1;
        }
    }

	long startTime = get_nanos();
	int thread_number, j, size = BUFFER_SIZE/THREADS;
	char temp[100];
	pthread_t threadID[THREADS];
	char line[1000];
	char * pointer;
	FILE* f = fopen("dict.txt", "r");
	dictionary_size = 0;
	while(fgets(line, 1000, f)){
		sscanf(line, "%s\n", temp);
		if(strlen(temp) == 0)
			continue;
		dict[dictionary_size] = (char*) malloc(sizeof(temp)+1);
		strcpy(dict[dictionary_size++], temp);
	}
	fclose(f);
	for(thread_number = 0; thread_number < THREADS;thread_number++){
		buffer[thread_number] = (char*) malloc(size + 1);
		if(!fgets(buffer[thread_number], size + 1, stdin)){
			fprintf(stdout, "Error: can't read the input stream!");
			break;
		}
		while(pthread_create(threadID + thread_number, NULL, word_puzzle_solver, (void *) thread_number)){
			fprintf(stdout, "Error: Too many threads are created!\n");
			break;
		}
	}
	for(j = 0; j < thread_number;j++){
		pthread_join(threadID[j], NULL);
        if(verbose){
		fprintf(stdout, "Note: Thread %d joined!\n", j);
        } 
	}
    if(verbose){
    	fprintf(stdout, "Note: Total time: %ld nanoseconds using %d threads!\n", 
		get_nanos()-startTime, thread_number);
    }

if(sorted){
        generic_qsort(solution_bank,0,solution_count-1);
    }

    if(distinct){
        delete_duplicates(solution_bank, solution_count-1);
    }

     if(distinct || sorted){
         for(int i = 0; i < solution_count; i++){
                fprintf(stdout, "%s \n", solution_bank[i]);

        }
    }
    //print Binary search time 
    if(t_time){
        fprintf(stdout, "Note: Total Binary time: %ld nanoseconds using %d threads!\n", 
		get_nanos()- startTime, thread_number);

    }
} 