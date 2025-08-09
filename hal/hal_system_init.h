#ifndef __HAL_SYSTEM_INIT_H__
#define __HAL_SYSTEM_INIT_H__

#include "hw_config.h"

void GPIO_Toggle(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin);
void hal_init(void);

#endif
