#include "stm32f10x.h"                  // Device header
#include "stdio.h"
#include "hal_system_init.h"
#include "hw_config.h"

int main(void)
{

	hal_init();

	while(1)
	{
		LED1_HIGH();
		Delay_ms(500);
		LED1_LOW();
		Delay_ms(500);
		
	}
}
