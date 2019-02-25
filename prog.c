#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct PCB_st 
{
    int ProcId;
    int ProcPR;
    int CPUburst;
    int Reg[8];
    int queueEnterClock, waitingTime;
    //future struct variables
    struct PCB_st *next;
}; 

int CPUreg[8] ={0};
struct PCB_st *Head=NULL;
struct PCB_st *Tail=NULL;
int CLOCK=0;
int Total_waiting_time=0;
int Total_turnaround_time=0;
int Total_job=0;

void HTp(struct PCB_st *p);
void push(struct PCB_st *p);
void setTail();
void FIFO_Scheduling();

int main(int argc, char* argv[])
{
    FILE *f;
    char buffer[12];
    int i;
    char inputf[50], algo[50];

    memset(inputf, '\0', sizeof(inputf));
    memset(algo, '\0', sizeof(algo));

    for (i=0; i< argc; i++)
    {   
        if(strcmp(argv[i], "-input") == 0)
            strcpy(inputf, argv[i+1]);

        if(strcmp(argv[i], "-alg") == 0)
            strcpy(algo, argv[i+1]);
    }


    f = fopen(inputf, "r");
    if (f == NULL)
    {
        fprintf(stderr, "Failed to open file: %s\n", inputf);
        exit(1);
    }

    while (fgets(buffer, 100, f))
    {
        struct PCB_st *PCB = malloc(sizeof(struct PCB_st));

        if(Head == NULL && Tail == NULL)
        {
            HTp(PCB);
        }

        int scancount = sscanf(buffer, "%d %d %d" 
            , &PCB->ProcId
            , &PCB->ProcPR
            , &PCB->CPUburst);

        for (i = 0; i < (sizeof(PCB->Reg)/sizeof(PCB->Reg[0])); i++)
        {
            PCB->Reg[i] = PCB->ProcId;
            //printf("i = %d\n", PCB->Reg[i]);
        }

        PCB->queueEnterClock = 0;
        PCB->waitingTime = 0;
        //printf("blah %d\n", PCB->ProcPR);
        push(PCB);
        setTail();
        //free(PCB);

        //printf("yo %d %d %d %d\n", scancount, PCB->ProcId, PCB->ProcPR, PCB->CPUburst); //debug
    }
    
    close(f);
    //printf("Tail value %d\n", Tail->ProcPR);
    //printf("Head value %d\n", Head->ProcPR);
    printf("Student Name: Emmanuel Espinosa-Tello\n");
    printf("Input File Name: %s\n", inputf);
    printf("CPU Scheduling Alg: %s\n", algo);
    
    FIFO_Scheduling();

    return 0;
    
}
//Head and tail initially set to soemthing
void HTp(struct PCB_st *p)
{
    Head = p;
    Tail = p;
}
//iterates throught list until it gets to the end and sets the tail to that
void setTail()
{
    struct PCB_st *current = Head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    Tail = current;
    //free(current);
}
/*
    Takes the pointer to struct and iterates through the current linked list until
    the current pointer's next pointer is null then it sets the current pointer to the
    pointer passed in
*/
void push(struct PCB_st *p)
{
    if(Head == p)
        return;
    struct PCB_st *current = Head;

    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = p;
    //free(current);
    return;
}

void FIFO_Scheduling()
{
    int i;
    struct PCB_st *PCB = Head;

    while(Head->next != NULL || Head == Tail)
    {
        for(i = 0; i < (sizeof(PCB->Reg)/sizeof(PCB->Reg[0])); i++)
        {
            CPUreg[i] = PCB->Reg[i];
            CPUreg[i]++;
            PCB->Reg[i] = CPUreg[i];
        }
        
        PCB->waitingTime = PCB->waitingTime + CLOCK - PCB->queueEnterClock;
        Total_waiting_time = Total_waiting_time + PCB->waitingTime;
        CLOCK = CLOCK + PCB->CPUburst;
        Total_turnaround_time = Total_turnaround_time + CLOCK;
        Total_job = Total_job + 1;
        
        printf("Process %d is completed at %d ms\n", PCB->ProcId, CLOCK);
        
        if(Head == Tail)
        {
            free(Head);
            break;
        }

        PCB = Head->next;
        free(Head);
        Head = PCB;
        
    }
    
    printf("Average Waiting time = %2.2lf ms\n", ((double)Total_waiting_time/Total_job));
    printf("Average Turnaround time = %2.2lf ms\n", ((double)Total_turnaround_time/Total_job));
    printf("Throughput = %2.2lf jobs per ms\n", ((double)Total_job/CLOCK));
}
