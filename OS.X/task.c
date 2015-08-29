/*
 * File:   task.c
 * Author: Cindy
 *
 * Created on 13 de agosto de 2015, 09:25 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include "task.h"


/*
 *
 */
char *STU = (char*)0x00000FFF;
char *STH = (char*)0x00000FFE;
char *STL = (char*)0x00000FFD;
unsigned char SCHEDULER_SWITCH = 0;
unsigned char cont;
unsigned char task_run = 0;
task aux;
//char *STP = (char*)0x00000FFC;
//char *PU  = (char*)0x00000FFB;
//char *PH  = (char*)0x00000FFA;
//char *PL  = (char*)0x00000FF9;
//char *W   = (char*)0x00000FE8;


void huerfano(void)
{
    do
    {
        ClrWdt();
    }
    while(1);
}

void task_init(void)
{
    cont = ARRAY_LENGTH - 1;
    tasks[cont].priority = 0;
    tasks[cont].state = sReady;
    tasks[cont].task_id = cont;
    tasks[cont].actual = huerfano;
    tasks[cont].inicial = huerfano;
}

void scheduler_activate(void)
{
    SCHEDULER_SWITCH = 1;
    asm("MOVLW 0x00");
    asm("MOVWF 0xFB, C");
    asm("MOVLW 0x02");
    asm("MOVWF 0xFA, C");
    asm("MOVLW 0xF8");
    asm("POP");
    asm("MOVWF 0xF9, C");
}

void scheduler_deactivate(void)
{
    SCHEDULER_SWITCH = 0;
}


void scheduler(void)
{
    if(SCHEDULER_SWITCH)
    {
        cont = ARRAY_LENGTH - 1;
        aux = tasks[cont];
        cont--;
        do
        {
            if(tasks[cont].state == sReady && tasks[cont].priority > aux.priority)
            {
                aux = tasks[cont];
            }
        }
        while(cont--);
        tasks[aux.task_id].state = sRunning;
        task_run = aux.task_id;
        INTCONbits.GIE_GIEH = 1; //enable all high priority interrupts
        tasks[aux.task_id].actual();
    }
}


void IcreateTask(unsigned char priority, pFunc_t inicial)
{
    INTCONbits.GIE_GIEH = 0; //disable all high priority interrupts
    cont = ARRAY_LENGTH - 1;
    do
    {
        if(tasks[cont].state == sFree)
        {
            tasks[cont].inicial=inicial;
            tasks[cont].actual = inicial;
            tasks[cont].priority=priority;
            tasks[cont].state = sReady;
            tasks[cont].task_id= cont;
            break;
        }
    }
    while(cont--);

    if(tasks[task_run].state == sRunning)
    {
        asm("POP");
        tasks[task_run].actual  = (pFunc_t)(((unsigned long)*STU << 16) | ((unsigned long)*STH << 8) | (unsigned long)*STL) ;
        tasks[task_run].state = sReady;
    }

    if(SCHEDULER_SWITCH)
    {
         asm("MOVLW 0x00");
         asm("MOVWF 0xFB, C");
         asm("MOVLW 0x02");
         asm("MOVWF 0xFA, C");
         asm("MOVLW 0xF8");
         asm("POP");
         asm("MOVWF 0xF9, C");
    }
}


void createTask(unsigned char priority, pFunc_t inicial)
{
    INTCONbits.GIE_GIEH = 0; //disable all high priority interrupts
    cont = ARRAY_LENGTH - 1;
    do
    {
        if(tasks[cont].state == sFree)
        {
            tasks[cont].inicial=inicial;
            tasks[cont].actual = inicial;
            tasks[cont].priority=priority;
            tasks[cont].state = sReady;
            tasks[cont].task_id= cont;
            break;
        }
    }
    while(cont--);

    if(tasks[task_run].state == sRunning)
    {
        tasks[task_run].actual  = (pFunc_t)(((unsigned long)*STU << 16) | ((unsigned long)*STH << 8) | (unsigned long)*STL) ;
        tasks[task_run].state = sReady;
    }

    if(SCHEDULER_SWITCH)
    {
         asm("MOVLW 0x00");
         asm("MOVWF 0xFB, C");
         asm("MOVLW 0x02");
         asm("MOVWF 0xFA, C");
         asm("MOVLW 0xF8");
         asm("POP");
         asm("MOVWF 0xF9, C");
    }
}


void deleteTask(void)
{
    INTCONbits.GIE_GIEH = 0; //disable all high priority interrupts
    if(tasks[task_run].state == sRunning)
    {
        tasks[task_run].state = sFree;
    }
    if(SCHEDULER_SWITCH)
    {
         asm("MOVLW 0x00");
         asm("MOVWF 0xFB, C");
         asm("MOVLW 0x02");
         asm("MOVWF 0xFA, C");
         asm("MOVLW 0xF8");
         asm("POP");
         asm("MOVWF 0xF9, C");
    }

}

