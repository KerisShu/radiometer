/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-20     shangwang7       the first version
 */

#include "myapp/radiom/radio.h"
#include <rtthread.h>
#include <rtdevice.h>

#include <board.h>


/* warning thread parameters*/
#define THREAD_STACK_SIZE 512
#define WARNING_THREAD_PRIORITY   30
#define WARNING_TIMESLICE  50


static rt_thread_t ledwarning = RT_NULL;
static rt_thread_t buzzerwarning = RT_NULL;
int key_status;


/* led warning thread entry function */
static void led_warning(void *param)
{
    rt_pin_mode(LED_WARN_PIN , PIN_MODE_OUTPUT);
    while(1)
    {
        rt_pin_write(LED_WARN_PIN, PIN_HIGH);
        rt_thread_mdelay(2000);
        rt_pin_write(LED_WARN_PIN, PIN_LOW);
        rt_thread_mdelay(2000);
    }
}

/* buzzer warning thread entry function */
static void buzzer_warning(void *param)
{
    rt_pin_mode(BUZZER_PIN , PIN_MODE_OUTPUT);
    rt_pin_write(BUZZER_PIN, PIN_LOW);

    rt_pin_mode(KEY_BUZZER_PIN , PIN_MODE_INPUT);
    int status;
    rt_uint16_t anti_shake = 0; // count variable

    while(1)
    {
        key_status = rt_pin_read(KEY_BUZZER_PIN);
        //rt_kprintf("KEY: %x",key_status);


        if (key_status == PIN_LOW) // press button: 0
        {
            rt_thread_mdelay(10);// anti shake
            anti_shake++;

            //rt_kprintf("KEY: %x",key_status);
            if (anti_shake == 200) // 2 seconds
            {
                rt_pin_write(BUZZER_PIN, PIN_HIGH);
                status = rt_pin_read(rt_pin_read(BUZZER_PIN));
                rt_kprintf("BUZZER_HIGH: %x\n",status);
            }
        }
        else if(key_status != PIN_LOW)
        {
            anti_shake = 0;
        }
    }
}

/* warning thread */
int warning_thread(void)
{
    /* led warning thread */
    ledwarning = rt_thread_create("led_w_t",
                            led_warning, RT_NULL,
                            THREAD_STACK_SIZE,
                            WARNING_THREAD_PRIORITY, WARNING_TIMESLICE);
    if (ledwarning != RT_NULL)
        rt_thread_startup(ledwarning);
    else
        rt_kprintf("Failed: led warning start ");

    /* buzzer warning thread */
    buzzerwarning = rt_thread_create("buzzer_w_t",
                            buzzer_warning, RT_NULL,
                            THREAD_STACK_SIZE,
                            WARNING_THREAD_PRIORITY, WARNING_TIMESLICE);
    if (buzzerwarning != RT_NULL)
        rt_thread_startup(buzzerwarning);
    else
          rt_kprintf("Failed: buzzer warning start ");

    return 0;
}
