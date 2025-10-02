#include "hal_sys_time.h"
#include "hal_system_init.h"
#include "misc.h"
#include "hw_config.h"
#include "stm32f10x.h"

/**
 * @brief  GPIO 快速翻转函数（寄存器实现）
 * @param  GPIOx: GPIO端口
 * @param  GPIO_Pin: 引脚号
 * @retval None
 */
void GPIO_Toggle(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
{
    GPIOx->ODR ^= GPIO_Pin;  // 直接操作输出数据寄存器
}

void hal_gpio_init(void)
{
    GP_EN_RCC();

    GPIO_InitTypeDef GPIO_InitStruct;
    GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStruct.GPIO_Pin = GP_LED1_PIN;
    GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GP_LED1_GPIO,&GPIO_InitStruct);

    LED1_HIGH();
}

void hal_init(void)
{
    

    SysTick_Init();

    hal_gpio_init();
    
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

}
