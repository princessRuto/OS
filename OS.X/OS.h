/* 
 * File:   OS.h
 * Author: Cindy
 *
 * Created on 17 de agosto de 2015, 09:00 PM
 */

#ifndef OS_H
#define	OS_H

#define TASK_LIMIT 10


typedef unsigned char u8;
typedef unsigned int u16;
typedef unsigned long u32;
typedef void (*func_ptr)(void); /*Pointer to the task entry function.*/

typedef struct{
    u8 priority;
    u8 state;
    u8 task_id;
    func_ptr pc_cont;
}task;

/*Task States*/

enum{
  TASK_SUBMIT,
  TASK_READY,
  TASK_RUNNING,
  TASK_ENDED,
  TASK_WAIT
};

/*Global Variables*/

extern volatile task tasks [TASK_LIMIT];

/*Prototypes*/
void add_task(func_ptr funct, u8 args);
void init_tasks(void);
void activate_task(func_ptr ptask);
void delete_task(void);
void scheduler(void);
void run_task(u8 task_id);

#ifdef	__cplusplus
extern "C" {
#endif




#ifdef	__cplusplus
}
#endif

#endif	/* OS_H */

