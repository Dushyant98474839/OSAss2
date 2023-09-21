#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <sys/wait.h>
#include <math.h>
#include <sched.h>


int main(int argc, char const *argv[])
{
    struct timespec time_start, time_end;
    clock_gettime(CLOCK_MONOTONIC, &time_start);
    int rc = fork();
    if (rc == 0)
    {
        struct sched_param s;
        s.sched_priority = 0;
        sched_setscheduler(rc, SCHED_OTHER, &s);
        if (execl("./p1", "p1", NULL)==-1){
            perror("execl");
            exit(1);
        }
    }
    else if (rc < 0)
    {
        perror("fork");
        exit(1);
    }
    int rc2 = fork();
    if (rc2 == 0)
    {
        struct sched_param s;
        sched_setscheduler(rc2, SCHED_RR, &s);
        if (execl("./p2", "p2", NULL)==-1){
            perror("execl");
            exit(1);
        }
    }
    else if (rc2 < 0)
    {
        perror("fork");
        exit(1);
    }
    int rc3 = fork();
    if (rc3 == 0)
    {
        struct sched_param s;
        sched_setscheduler(rc3, SCHED_FIFO, &s);
        if (execl("./p3", "p3", NULL)==-1){
            perror("execl");
            exit(1);
        }
    }
    else if (rc3 < 0)
    {
        perror("fork");
        exit(1);
    }
    int children[3] = {rc, rc2, rc3};
    
    FILE *fptr;
    fptr=fopen("RESULT.txt","w");
    fclose(fptr);
    fptr=fopen("RESULT.txt","a+");

    for (int i = 0; i < 3; i++)
    {
        int status;
        // printf("%d\n",children[2-i]);
        int k=waitpid(children[2-i], &status, 0);
        // printf("s %d\n",k);
        if (k==rc){
            printf("OTHER: ");
        }
        else if(k==rc2){
            printf("RR: ");
        }
        else if(k==rc3){
            printf ("FIFO: ");
        }
        clock_gettime(CLOCK_MONOTONIC, &time_end);
        double elapsed_time = (time_end.tv_sec - time_start.tv_sec) + (time_end.tv_nsec - time_start.tv_nsec) / pow(10, 9);
        printf("%.10f seconds\n", elapsed_time);
        fprintf(fptr,"%.10f\n",elapsed_time);
        
 
    }
    fclose(fptr);
}