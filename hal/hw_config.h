#ifndef __HW_CONFIG_H__
#define __HW_CONFIG_H__

#include "stm32f10x_gpio.h"
#include "hal_system_init.h"
#include "hal_sys_time.h"
#include "stm32f10x_rcc.h"

#ifndef STM32F10X_MD
#define STM32F10X_MD
#endif

#if defined(STM32F10X_MD)

#define GP_LED1_GPIO    GPIOC
#define GP_LED1_PIN     GPIO_Pin_13

#define LED1_HIGH()       GPIO_SetBits(GP_LED1_GPIO,GP_LED1_PIN)
#define LED1_LOW()        GPIO_ResetBits(GP_LED1_GPIO,GP_LED1_PIN)
#define LED1_TOGGLE()     GPIO_Toggle(GP_LED1_GPIO,GP_LED1_PIN)

#define GP_EN_RCC()         RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE)

#endif

#endif
