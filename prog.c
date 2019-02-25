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
void SJF_Scheduling();
void PR_Scheduling();
void RR_Scheduling();

int main(int argc, char* argv[])
{
    FILE *f;
    char buffer[12];
    int i;
    char inputf[50], algo[50];
    /*
    char arrays fill with null terminators will make for easy string comparison
    as the strcpy will only overwrite what is needed and the rest is null terminated
    */
    memset(inputf, '\0', sizeof(inputf));
    memset(algo, '\0', sizeof(algo));

    for (i=0; i< argc; i++)
    {   
        if(strcmp(argv[i], "-input") == 0)
            strcpy(inputf, argv[i+1]);

        else if(strcmp(argv[i], "-alg") == 0)
            strcpy(algo, argv[i+1]);
        else
            continue;
    }

    //Opening the file
    f = fopen(inputf, "r");
    if (f == NULL)
    {
        fprintf(stderr, "Failed to open file: %s\n", inputf);
        exit(1);
    }   
    //Using a buffer to read in line per line from the file and setting the appropriate
    //blocks
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
    //strcmp if else statments to decide which algo will be used
    if(strcmp(algo, "FIFO") == 0)
        FIFO_Scheduling(); 
    else if (strcmp(algo, "SJF") == 0)
        SJF_Scheduling();
    else if (strcmp(algo, "PR") == 0)
        PR_Scheduling();
    else if (strcmp(algo, "RR") == 0)
        RR_Scheduling();
    else
    {
        fprintf(stderr, "Failed to provide algorithm: -alg \"algorithm\"\n");
        exit(1);
    }

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
    current = NULL;
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
    current = NULL;
    return;
}

void FIFO_Scheduling()
{
    int i;
    struct PCB_st *PCB = Head;
    //start at the head and process each block one by one until head-> is null and finally terminate
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
        //if head and tail are the same the end has been reached
        if(Head == Tail)
        {
            free(Head);
            Head = NULL;
            Tail = NULL;
            PCB = NULL;
            break;
        }
        //free current top, set new one
        PCB = Head->next;
        free(Head);
        Head = PCB;
        
    }
    
    printf("Average Waiting time = %2.2lf ms\n", ((double)Total_waiting_time/Total_job));
    printf("Average Turnaround time = %2.2lf ms\n", ((double)Total_turnaround_time/Total_job));
    printf("Throughput = %2.2lf jobs per ms\n", ((double)Total_job/CLOCK));
}

void SJF_Scheduling()
{
    return;
}

void PR_Scheduling()
{
    printf("Part not complete\n");
}

void RR_Scheduling()
{
    printf("Part not complete\n");
}
