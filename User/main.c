#include "stm32f10x.h"                  // Device header
#include "stdio.h"
#include "hal_system_init.h"
#include "hw_config.h"
#include "scheduler.h"

int main(void)
{

	hal_init();

	while(1)
	{
		scheduler_run();
	}
}
