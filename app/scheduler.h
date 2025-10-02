#ifndef SCHEDULER_H
#define SCHEDULER_H

#include "stdint.h"

typedef struct
{
	void(*task_func)(uint32_t dT_ms);	//任务函数指针
//	u16 rate_hz;
	uint32_t interval_ticks;				//任务执行周期（ms）
	uint32_t last_run;					//上次执行任务的时间
}sched_task_t;

uint8_t scheduler_run(void);

#endif
