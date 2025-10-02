#include "scheduler.h"
#include "hal_sys_time.h"
#include "hw_config.h"

void Loop_Task_1ms(uint32_t dT_ms)
{
    //1ms任务

}

void Loop_Task_5ms(uint32_t dT_ms)
{
    //5ms任务

}

void Loop_Task_10ms(uint32_t dT_ms)
{
    //10ms任务

}

void Loop_Task_1s(uint32_t dT_ms)
{
    //1s任务
    static uint8_t led_status = 0;
    if(led_status)
    {
        LED1_HIGH();
        led_status = 0;
    }
    else
    {
        LED1_LOW();
        led_status = 1;
    }
}



//系统任务配置，创建不同执行频率的“线程”
static sched_task_t sched_tasks[] = 
{
 	//任务n,        周期ms, 上次时间
	{Loop_Task_1ms ,  1,  0 },
	{Loop_Task_5ms ,  5,  0 },
	{Loop_Task_10ms ,  10, 0 },	
    {Loop_Task_1s ,  1000,  0 },
};

//根据数组长度，判断线程数量
#define TASK_NUM (sizeof(sched_tasks)/sizeof(sched_task_t))

//Main_Task在main.c的while循环中轮询
uint8_t scheduler_run(void)
{
	uint8_t index = 0;
	//循环判断其他所有线程任务，是否应该执行
	uint32_t time_now;
	for(index=0;index < TASK_NUM;index++)
	{
		//获取系统当前时间，单位MS
		 time_now = get_systick_ms();
		//进行判断，如果当前时间减去上一次执行的时间，大于等于该线程的执行周期，则执行线程
		if(time_now - sched_tasks[index].last_run >= sched_tasks[index].interval_ticks)
		{
			//更新线程的执行时间，用于下一次判断
			sched_tasks[index].last_run = time_now;
			//执行线程函数，使用的是函数指针,传入的参数是该线程的周期，用来实现非阻塞式延时
			sched_tasks[index].task_func(sched_tasks[index].interval_ticks);
		}	 
	}
	
	return 0;
}
