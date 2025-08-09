/* 包含STM32标准外设库头文件 */
#include "stm32f10x.h"
#include "hal_sys_time.h"
#include "hw_config.h"
#include "stm32f10x_rcc.h"
#include "hw_config.h"


/* 宏定义系统时钟参数（需与实际主频一致） */
#define SYSTEM_CLOCK_FREQ 72000000                // 系统时钟72MHz

volatile uint32_t g_sys_tick = 0; // 全局滴答计数器

/**
 * @brief  SysTick初始化函数（配置为1ms周期中断）
 * @param  None
 * @retval 状态：0-成功，1-失败
 */
uint8_t SysTick_Init(void)
{
    /* 使用标准库函数配置SysTick：1ms定时中断 */
    if (SysTick_Config(SystemCoreClock / 1000))
    {
        /* Capture error */ 
        return 1; // 初始化失败
    }

    /* 设置SysTick中断优先级为最高（优先级值0） */
    NVIC_SetPriority(SysTick_IRQn, 0);
    
    return 0; // 初始化成功
}

/**
 * @brief  SysTick中断服务函数（需在stm32f10x_it.c中声明）
 * @note   每1ms自动调用一次，更新全局tick计数器
 */
void SysTick_Handler(void)
{
    g_sys_tick++; // 递增毫秒计数器
}

/**
 * @brief  阻塞式毫秒级延时函数（轮询模式）
 * @param  ms: 延时时长（单位：毫秒）
 * @retval 无
 */
void Delay_ms(uint32_t ms)
{
    uint32_t start_tick;
    uint32_t current_tick;
    uint32_t elapsed_ms;
    
    if (ms == 0) return; // 0ms延时直接返回
    
    /* 获取起始时间戳 */
    start_tick = g_sys_tick;
    
    /* 等待延时完成 */
    do {
        current_tick = g_sys_tick;
        
        /* 处理32位计数器溢出情况 */
        if (current_tick >= start_tick) {
            elapsed_ms = current_tick - start_tick;
        } else {
            /* 发生溢出：计算跨溢出的时间差 */
            elapsed_ms = (0xFFFFFFFF - start_tick) + current_tick + 1;
        }
        
    } while (elapsed_ms < ms);
}

/**
 * @brief  阻塞式微秒级延时函数（轮询模式，不依赖中断）
 * @param  us: 延时时长（单位：微秒）
 * @retval 无
 * @note   基于SysTick计数器实现，精度较高但消耗CPU
 */
void Delay_us(uint32_t us)
{
    uint32_t ticks = us * (SYSTEM_CLOCK_FREQ / 1000000); // 计算需要的时钟周期数
    uint32_t start = SysTick->VAL;                       // 获取当前计数器值
    while ((start - SysTick->VAL) < ticks)
        ; // 等待计数器递减完成
}


/**
 * @brief  获取系统启动以来的毫秒数
 * @param  无
 * @retval 当前系统滴答计数值（单位：毫秒）
 */
uint32_t get_systick_ms(void)
{
    return g_sys_tick;
}
