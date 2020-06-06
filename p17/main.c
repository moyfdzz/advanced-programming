/*
 Autor: Santiago Castaño Moreno
 Fecha: 19/05/2020
 Matricula: A01193760
 */
#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdbool.h>
#include <string.h>

struct Task {
    char id[3];
    int time;
    char deps[5][4];
    int nDependencies;
};

struct Task tasks[5];
bool currentlyRunning[5];

void *excecuteThread (void *threadID){
    long tID;
    tID=(long)threadID;
    currentlyRunning[tID] = true;
    bool didPause = false;
    int count = 0;
    for(int x = 0; x < tasks[tID].nDependencies; x++) {
        int dependencyID = tasks[tID].deps[count++][1] - '0' - 1;
        if (currentlyRunning[dependencyID]) {
            printf("STOP\t %s, waiting for dependency\n", tasks[tID].id);
            didPause = true;
            while(currentlyRunning[dependencyID]) { }
            printf("RESUMED\t %s\n", tasks[tID].id);
        }
    }
    
    sleep(tasks[tID].time);
    
    currentlyRunning[tID] = false;
    
    printf("FINISHED\t %s\n", tasks[tID].id);
    pthread_exit(NULL);
}

bool noDependencies(char* str) {
    int len = strlen(str);
    for (int x = 0; x < len; x++) {
        if (str[x] == '-'){
            return true;
        }
    }
    return false;
}
void getThreadData(char* archivo, int *threads) {
    FILE *file;
    file = fopen(archivo, "r");
    if (!file) {
        printf("ERROR, File not found.\n");
    }
    
    *threads = 0;
    
    char line[30];
    fgets(line, sizeof line, file);
    while (fgets(line, sizeof line, file) != NULL) {
        struct Task current;
        
        int end = strlen(line);
        line[end] = '\0';
        char *token, *token2, *aux = line;
        
        token = strtok_r(aux, "\t", &aux);
        strcpy(current.id, token);
        
        token = strtok_r(aux, "\t", &aux);
        current.time = atoi(token);
        
        token = strtok_r(aux, "\t", &aux);
        char *aux2 = token;
        
        current.nDependencies = 0;
        while (token2 = strtok_r(aux2, ", ", &aux2)) {
            if (noDependencies(token2)) break;
            strcpy(current.deps[current.nDependencies++], token2);
        }
        tasks[(*threads)++] = current;
    }
    fclose (file);
}

int main() {
    
    struct Task tareas[5];
    int threadsCount;
    
    getThreadData("test.txt", &threadsCount);
    
    pthread_t threads[threadsCount];
    int rc = 0;
    long t = 0;
    
    for (t = 0; t < threadsCount; t++) {
        rc = pthread_create(threads + t, NULL, excecuteThread, (void *) t);
        printf("CREATED\t\t t%ld\n", t+1);
        if (rc) {
            printf("ERROR; return code from pthread_create() is %d\n", rc);
            exit(-1);
        }
    }
    pthread_exit(NULL);
}
