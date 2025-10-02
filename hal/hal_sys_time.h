#ifndef __HAL_SYS_TIME_H__
#define __HAL_SYS_TIME_H__

#include "stdint.h"

uint8_t SysTick_Init(void);
void Delay_ms(uint32_t ms);
void Delay_us(uint32_t us);
uint32_t get_systick_ms(void);
uint64_t get_time_us(void);

#endif
