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

int main(int argc, char* argv[])
{
    FILE *f;
    char buffer[12];
    f = fopen(argv[1], "r");
    if (f == NULL)
    {
        fprintf(stderr, "Failed to open file: %s\n", argv[1]);
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
        int i;
        for (i = 0; i < (sizeof(PCB->Reg)/sizeof(PCB->Reg[0])); i++)
        {
            PCB->Reg[i] = PCB->ProcId;
            //printf("i = %d\n", PCB->Reg[i]);
        }
        printf("blah %d\n", PCB->ProcPR);
        push(PCB);
        setTail();

        //printf("yo %d %d %d %d\n", scancount, PCB->ProcId, PCB->ProcPR, PCB->CPUburst); //debug

    }
    
    close(f);
    //printf("Tail value %d\n", Tail->ProcPR);
    //printf("Head value %d\n", Head->ProcPR);
    printf("Student Name: Emmanuel Espinosa-Tello\n");
    printf("Input File Name: %s\n", argv[1]);
    printf("CPU Scheduling Alg: %s\n", pe);
    
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
