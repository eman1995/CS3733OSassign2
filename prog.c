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

        if(Head == NULL)
            Head = PCB;

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
        


        //printf("yo %d %d %d %d\n", scancount, PCB->ProcId, PCB->ProcPR, PCB->CPUburst); //debug

    }

    return 0;
    
}
