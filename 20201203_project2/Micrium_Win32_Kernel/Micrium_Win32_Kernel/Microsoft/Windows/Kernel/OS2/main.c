/*
*********************************************************************************************************
*                                            EXAMPLE CODE
*
*               This file is provided as an example on how to use Micrium products.
*
*               Please feel free to use any application code labeled as 'EXAMPLE CODE' in
*               your application products.  Example code may be used as is, in whole or in
*               part, or may be used as a reference only. This file can be modified as
*               required to meet the end-product requirements.
*
*               Please help us continue to provide the Embedded community with the finest
*               software available.  Your honesty is greatly appreciated.
*
*               You can find our product's user manual, API reference, release notes and
*               more information at https://doc.micrium.com.
*               You can contact us at www.micrium.com.
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*
*                                              uC/OS-II
*                                            EXAMPLE CODE
*
* Filename : main.c
*********************************************************************************************************
*/

/*
*********************************************************************************************************
*                                            INCLUDE FILES
*********************************************************************************************************
*/

#include  <cpu.h>
#include  <lib_mem.h>
#include  <os.h>

#include  "app_cfg.h"


/*
*********************************************************************************************************
*                                            LOCAL DEFINES
*********************************************************************************************************
*/

#define TASK_STACKSIZE   2048
#define TASK1_PRIORITY   1      // kevin 設多少都沒差後面會改
#define TASK2_PRIORITY   2      // kevin 設多少都沒差後面會改
#define TASK3_PRIORITY   3      // kevin 設多少都沒差後面會改
#define TASK4_PRIORITY   4      // kevin 設多少都沒差後面會改
#define TASK1_ID         1
#define TASK2_ID         2
#define TASK3_ID         3
#define TASK4_ID         4

/*
*********************************************************************************************************
*                                       LOCAL GLOBAL VARIABLES
*********************************************************************************************************
*/

static  OS_STK  StartupTaskStk[APP_CFG_STARTUP_TASK_STK_SIZE];

static  OS_STK  Task1_STK[TASK_STACKSIZE];
static  OS_STK  Task2_STK[TASK_STACKSIZE];
static  OS_STK  Task3_STK[TASK_STACKSIZE];
static  OS_STK  Task4_STK[TASK_STACKSIZE];

/*
*********************************************************************************************************
*                                         FUNCTION PROTOTYPES
*********************************************************************************************************
*/

static  void  StartupTask (void  *p_arg);

static void task1(void* p_arg);
static void task2(void* p_arg);
static void task3(void* p_arg); // kevin
static void task4(void* p_arg); // kevin

/*
*********************************************************************************************************
*                                                main()
*
* Description : This is the standard entry point for C code.  It is assumed that your code will call
*               main() once you have performed all necessary initialization.
*
* Arguments   : none
*
* Returns     : none
*
* Notes       : none
*********************************************************************************************************
*/

int  main (void)
{
#if OS_TASK_NAME_EN > 0u
    CPU_INT08U  os_err;
#endif


    CPU_IntInit();

    Mem_Init();                                                 /* Initialize Memory Managment Module                   */
    CPU_IntDis();                                               /* Disable all Interrupts                               */
    CPU_Init();                                                 /* Initialize the uC/CPU services                       */

    OSInit();                                                   /* Initialize uC/OS-II                                  */

                                                                /*
    OSTaskCreateExt( StartupTask,                               // Create the startup task                              
                     0,
                    &StartupTaskStk[APP_CFG_STARTUP_TASK_STK_SIZE - 1u],
                     APP_CFG_STARTUP_TASK_PRIO,
                     APP_CFG_STARTUP_TASK_PRIO,
                    &StartupTaskStk[0u],
                     APP_CFG_STARTUP_TASK_STK_SIZE,
                     0u,
                    (OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

#if OS_TASK_NAME_EN > 0u
    OSTaskNameSet(         APP_CFG_STARTUP_TASK_PRIO,
                  (INT8U *)"Startup Task",
                           &os_err);
#endif
*/  
    OSTaskCreateExt(task1,
        0,
        &Task1_STK[TASK_STACKSIZE - 1],
        TASK1_PRIORITY,
        TASK1_ID,
        &Task1_STK[0],
        TASK_STACKSIZE,
        0,
        (OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

    OSTaskCreateExt(task2,
        0,
        &Task2_STK[TASK_STACKSIZE - 1],
        TASK2_PRIORITY,
        TASK2_ID,
        &Task2_STK[0],
        TASK_STACKSIZE,
        0,
        (OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

    if(kevin_task_num >= 3) // kevin
        OSTaskCreateExt(task3,
            0,
            &Task3_STK[TASK_STACKSIZE - 1],
            TASK3_PRIORITY,
            TASK3_ID,
            &Task3_STK[0],
            TASK_STACKSIZE,
            0,
            (OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));
    if(kevin_task_num >= 4) // kevin
        OSTaskCreateExt(task4,
            0,
            &Task4_STK[TASK_STACKSIZE - 1],
            TASK4_PRIORITY,
            TASK4_ID,
            &Task4_STK[0],
            TASK_STACKSIZE,
            0,
            (OS_TASK_OPT_STK_CHK | OS_TASK_OPT_STK_CLR));

    OSTimeSet(0);    // kevin reset time
    OSStart();                                                  /* Start multitasking (i.e. give control to uC/OS-II)   */

    while (DEF_ON) {                                            /* Should Never Get Here.                               */
        ;
    }
}


/*
*********************************************************************************************************
*                                            STARTUP TASK
*
* Description : This is an example of a startup task.  As mentioned in the book's text, you MUST
*               initialize the ticker only once multitasking has started.
*
* Arguments   : p_arg   is the argument passed to 'StartupTask()' by 'OSTaskCreate()'.
*
* Returns     : none
*
* Notes       : 1) The first line of code is used to prevent a compiler warning because 'p_arg' is not
*                  used.  The compiler should not generate any code for this statement.
*********************************************************************************************************
*/

static  void  StartupTask (void *p_arg)
{
   (void)p_arg;

    OS_TRACE_INIT();                                            /* Initialize the uC/OS-II Trace recorder               */

#if OS_CFG_STAT_TASK_EN > 0u
    OSStatTaskCPUUsageInit(&err);                               /* Compute CPU capacity with no task running            */
#endif

#ifdef CPU_CFG_INT_DIS_MEAS_EN
    CPU_IntDisMeasMaxCurReset();
#endif
    
    APP_TRACE_DBG(("uCOS-III is Running...\n\r"));

    while (DEF_TRUE) {                                          /* Task body, always written as an infinite loop.       */
        OSTimeDlyHMSM(0u, 0u, 1u, 0u);
		APP_TRACE_DBG(("Time: %d\n\r", OSTimeGet()));
    }
}

void task1(void* p_arg) {
    (void)p_arg;
    while (1) {
        // printf("Hello from task1\n");
        while (1); // kevin 讓他一直卡在裡面 靠OSintexit來切
    }
}

void task2(void* p_arg) {
    (void)p_arg;
    while (1) {
        // printf("Hello from task2\n");
        while (1); // kevin 讓他一直卡在裡面 靠OSintexit來切
    }
}

void task3(void* p_arg) {
    (void)p_arg;
    while (1) {
        // printf("Hello from task3\n");
        while (1); // kevin 讓他一直卡在裡面 靠OSintexit來切
    }
}

void task4(void* p_arg) {
    (void)p_arg;
    while (1) {
        // printf("Hello from task4\n");
        while (1); // kevin 讓他一直卡在裡面 靠OSintexit來切
    }
}