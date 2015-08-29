/*
 * File:   OS.c
 * Author: Cindy
 *
 * Created on 14 de agosto de 2015, 05:28 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <p18f2550.h>
#include "task.h"
#include "types.h"
#include "configbits.h"

/*
 *
 */

/*Main Prototypes*/
void funcionX(void);
void funcionY(void);
void funcionZ(void);
/*****************/

void interrupt high_priority CSR(void)

{
    if(PIR2bits.CMIF)
    {
        /*Clear comparator flag interrupt*/
        (void) CMCON;
        PIR2bits.CMIF = 0;



        //Call create task;
        IcreateTask(1, funcionX);

    }

}


void comp_init(void)
{
    /*Two independent comparators*/
    CMCONbits.CM2 = 0;
    CMCONbits.CM1 = 1;
    CMCONbits.CM0 = 0;


    /*Setting RA0-RA3 as analog inputs also RA0 and RA3 directions as inputs*/
    ADCON1bits.PCFG3 = 1;
    ADCON1bits.PCFG2 = 0;
    ADCON1bits.PCFG1 = 1;
    ADCON1bits.PCFG0 = 1;
    TRISAbits.RA0 = 1;
    TRISAbits.RA3 = 1;


    /*comparator interrupt enable*/
    PIE2bits.CMIE = 1;


    /*comparator interrupt as high priority*/
    IPR2bits.CMIP = 1;

}

u8 x,y,z;

void funcionZ(void)
{
    z++;
    deleteTask();
}

void funcionY(void)
{
    createTask(3, funcionZ);
    y++;
    deleteTask();
}


void funcionX(void)
{
    createTask(2,funcionY);
    x++;
    deleteTask();
}

/*Queue*/

struct node
{
    u8 info;
    struct node *ptr;
}*front,*rear,*temp,*front1;

u8 frontelement();
void enq(u8 data);
void deq();
void create();
void queuesize();
u8 count = 0;

/* Create an empty queue */
void create()
{
    front = rear = NULL;
}

/* Returns queue size */
void queuesize()
{
    printf("\n Queue size : %d", count);
}

/* Enqueing the queue */
void enq(u8 data)
{
    if (rear == NULL)
    {
        rear = (struct node *)malloc(1*sizeof(struct node));
        rear->ptr = NULL;
        rear->info = data;
        front = rear;
    }
    else
    {
        temp=(struct node *)malloc(1*sizeof(struct node));
        rear->ptr = temp;
        temp->info = data;
        temp->ptr = NULL;

        rear = temp;
    }
    count++;
}

/* Dequeing the queue */
void deq()
{
    front1 = front;

    if (front1 == NULL)
    {
        printf("\n Error: Trying to display elements from empty queue");
        return;
    }
    else
        if (front1->ptr != NULL)
        {
            front1 = front1->ptr;
            printf("\n Dequed value : %d", front->info);
            free(front);
            front = front1;
        }
        else
        {
            printf("\n Dequed value : %d", front->info);
            free(front);
            front = NULL;
            rear = NULL;
        }
        count--;
}

/* Returns the front element of queue */
u8 frontelement()
{
    if ((front != NULL) && (rear != NULL))
        return(front->info);
    else
        return 0;
}
/************************************************************************/




void main(void)
{
    scheduler();
    task_init();
    comp_init();
    createTask(1, funcionX);
    scheduler_activate();
}


