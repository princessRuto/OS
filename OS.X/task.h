/*
 * File:   task.h
 * Author: Cindy
 *
 * Created on 11 de agosto de 2015, 08:27 PM
 */

#include <p18F2550.h>
#include "types.h"

#ifndef TASK_H
#define	TASK_H
#define ARRAY_LENGTH 10

typedef struct{
    unsigned char priority;
    unsigned char state;
    unsigned char task_id;
    pFunc_t actual;
    pFunc_t inicial;
}task;

enum
{
    sFree = 0,
    sReady,
    sRunning,
    sWait,
    sSuspend,
};

task tasks [ARRAY_LENGTH];
void task_init(void);
void scheduler_activate(void);
void scheduler_deactivate(void);
void scheduler(void);
void createTask(unsigned char priority, pFunc_t inicial);
void IcreateTask(unsigned char priority, pFunc_t inicial);
void deleteTask(void);


#ifdef	__cplusplus
extern "C" {
#endif

#ifdef	__cplusplus
}
#endif

#endif	/* TASK_H */