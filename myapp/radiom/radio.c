/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-20     shangwang7       the first version
 */

#include "radio.h"
#include <rtthread.h>
#include <rtdevice.h>

#include <board.h>


/* warning thread parameters*/
#define THREAD_STACK_SIZE 512
#define WARNING_THREAD_PRIORITY   30
#define WARNING_TIMESLICE  50
/* warning thread parameters*/


static rt_thread_t warning = RT_NULL;
static rt_thread_t radio_acce = RT_NULL;


static uint32_t thresh_val = 100; // 报警阈值
static uint32_t current_val= 0;  // 当前辐射值



/* led warning thread entry function */
static void warning_func(void *param)
{
    rt_pin_mode(LED_WARN_PIN, PIN_MODE_OUTPUT);
    int status;

    while(1)
    {
        if (current_val >= thresh_val )
        {
            rt_pin_write(BUZZER_PIN, PIN_HIGH);
            status = rt_pin_read(rt_pin_read(BUZZER_PIN));
            rt_kprintf("BUZZER_HIGH: %x\n",status);
            rt_kprintf("\\  ||  /\n");
            rt_kprintf(" -----\n");
            rt_kprintf(" \\   /\n");
            rt_kprintf("  \\ /\n");
            rt_kprintf("   -\n");

            rt_pin_write(LED_WARN_PIN, PIN_HIGH);

            rt_thread_mdelay(500);

            rt_pin_write(BUZZER_PIN, PIN_LOW);
            status = rt_pin_read(rt_pin_read(BUZZER_PIN));
            rt_kprintf("BUZZER_HIGH: %x\n",status);
            rt_pin_write(LED_WARN_PIN, PIN_LOW);

            rt_thread_mdelay(500);
        }
    }
}

/* buzzer warning thread entry function */
static void radio_acce_f(void *param)
{
    rt_pin_mode(KEY_RADIO_PIN , PIN_MODE_INPUT);// 模拟达到报警阈值

    int key_status;
    key_status = rt_pin_read(KEY_RADIO_PIN);
    rt_kprintf("KEY: %x\n",key_status);

    while(1)
    {
        key_status = rt_pin_read(KEY_RADIO_PIN);
        //rt_kprintf("KEY: %x",key_status);

        if (key_status == PIN_LOW) // press button: 0
        {
            rt_thread_mdelay(100);// anti shake
            current_val = current_val + 10;
            key_status = rt_pin_read(KEY_RADIO_PIN);
            rt_kprintf("KEY: %x,%d\n",key_status,current_val/10);
        }
        else if(key_status != PIN_LOW)
        {
            //current_val = 0;
        }
    }
}


/* warning thread */
int warning_thread(void)
{
    /* led warning thread */
    warning = rt_thread_create("warning_thread",
                            warning_func, RT_NULL,
                            THREAD_STACK_SIZE,
                            WARNING_THREAD_PRIORITY, WARNING_TIMESLICE);
    if (warning != RT_NULL)
        rt_thread_startup(warning);
    else
        rt_kprintf("Failed: warning start ");

    /* buzzer warning thread */
    radio_acce = rt_thread_create("radio_acce",
                            radio_acce_f, RT_NULL,
                            THREAD_STACK_SIZE,
                            WARNING_THREAD_PRIORITY, WARNING_TIMESLICE);
    if (radio_acce != RT_NULL)
        rt_thread_startup(radio_acce);
    else
          rt_kprintf("Failed: radio_acce start ");

    return 0;
}
