// Jose Guillermo Saldana Cardenas A0103988
// Practica 17

#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <unistd.h>

#define NUM_THREADS 100


typedef struct myThread {
    int id;
    int time;
    int * dependents;
    int dependentsSize;
} myThread;

pthread_t threads[NUM_THREADS];

// Constructor
myThread * Thread(int id, int time, int dependents[100], int dependentsSize){
  myThread * t = malloc(sizeof(myThread));
  t->time = time;
  t->id = id;
  t->dependents = dependents;
  t->dependentsSize = dependentsSize;
  return t;
}

// Changes thread Id to int type
int parseThreadId(char * tid){
    int iTid = 0;
    int i = 1;
    while(*tid != '\0'){
        if(isdigit(*tid)){
            iTid += atoi(tid) * i;
            i *= 10;
        }
        tid++;
    }
    return iTid;
}

// Counts lines in file passed on params
int countLinesFromFile(char * file_name){
    int i = 0;
    char tmp[100];
    FILE *f;
    f = fopen(file_name, "r");

    while(fscanf(f, "%s\t%s\t%s\t", tmp, tmp, tmp) != EOF){
        i++;
    }
    fclose(f);
    return i;
}

// Counts amount of dependencies for a single thread
int count_num_elements(char * orig_value){

    // If no dependencies specified, return 0
    if(*orig_value == '-') return 0;

    char * value = malloc(sizeof(orig_value));
    strcpy(value, orig_value);
    int num_elems = 0;
    char *pt;
    // Find if there is more than 1 dependency on string
    pt = strtok (value,",");
    while (pt != NULL) {
        num_elems++;
        pt = strtok (NULL, ",");
    }
    free(value);
    return num_elems;
}

// Returns array of elements representing dependencies
int * separete_elements(char * value, int num_elems){

    int * elems = malloc(num_elems * sizeof(int));
    int i = 0;

    // Split values on array
    char *pt;
    pt = strtok(value,",");
    while(pt != NULL){
        // Parse id to int
        int num = parseThreadId(pt);
				// Add to array and look for next one
        elems[i] = num;
        i++;
        pt = strtok(NULL, ",");
    }

    return elems;
}


//Obetner los threads del archivo
myThread * * readFileForThreads(char * file_name, int iNumberOfLines){
		// To save thread ids
    char tid[10];
		// To save thread dependants
    char dependents[100];
    int tTime, i = 0;
    FILE *f;
		// Array of structs to save all threads 
    myThread * * struct_threads = malloc(iNumberOfLines * sizeof(myThread));
    f = fopen(file_name, "r");

		// Read file and convert all data to create threads
    while(fscanf(f, "%s\t%d\t%s", tid, &tTime, dependents) != EOF){
        int dep_size = count_num_elements(dependents); 
				int * int_dependents = separete_elements(dependents, dep_size);
        int iTid = parseThreadId(tid);
        struct_threads[i++] = Thread(iTid, tTime, int_dependents, dep_size);
    }

    fclose(f);
    return struct_threads;
}

// Main thread function
void *printHello (void *threadid){
    myThread *thread = (struct myThread*)threadid;
    printf("------Hello World! It’s me, thread #%d!------\n\n", thread->id);

    if (thread->dependentsSize > 0) {
      printf("I (thread #%d) depend on threads ", thread->id);
    }
		for(int i = 0; i < thread->dependentsSize; i++){
				if( i < thread->dependentsSize - 1) {
					printf("#%d, ", thread->dependents[i]);
				} else {
					printf("and #%d.\n", thread->dependents[i]);
				}
    }

		for(int i = 0; i < thread->dependentsSize; i++){
				printf("*Thread #%d waiting for dependency #%d.*\n", thread->id, thread->dependents[i]);
        int e = pthread_join(threads[thread->dependents[i]-1],NULL);
				if(e != 0) {
					printf("ERROR: return code from pthread_join() is %d\n", e);
				}
		}

    printf("'''It’s me, thread #%d EXITING!''' \n", thread->id);
    pthread_exit(NULL);
}

int main (int argc, char *argv[]) {
    
    char file_name[25];

    printf("Give me the name of the file with extension: \n");
    scanf("%s", file_name);

    // Numero de lineas del archivo
    int iNumberOfLines = countLinesFromFile(file_name);
    myThread * * thread_list = readFileForThreads(file_name, iNumberOfLines);

    int rc = 0;
    int t = 0;

    for (t = 0; t < iNumberOfLines; t++) {
        printf("From main: creating thread %d\n", thread_list[t]->id);
        rc = pthread_create(threads + t, NULL, printHello, (void *) thread_list[t]);
        if (rc){
            printf("ERROR: return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    pthread_exit(NULL);
}