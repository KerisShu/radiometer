/*
 * File      : main.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2006 - 2018, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-11     Keris       first implementation
 */

#include "myapp/myapp/led.h"
#include "myapp/mybutton/button.h"
#include "myapp/radiom/radio.h"


#include <rtdevice.h>
#include <rtthread.h>
#include <gd32f30x_rtc.h>// gd32f30x_rtc各种寄存器所需



#define KEY_PIN          15
#define KEY_PRESS_VALUE  0


/* declaration of functions */
void key_cb(struct my_button *button);
void init_peripheral(void);
void ex_fun(void);
/* end of declaration of functions */


int reg_value = 0;
int *reg_value_ptr;


int main(void)
{
    /* password */
    //finsh_set_password("12345678");
    /* end of password */

    static struct my_button key = {0};
    led_init();

    key.press_logic_level = KEY_PRESS_VALUE;
    key.hold_cyc_period = 100;
    key.cb = (my_button_callback)key_cb;
    key.pin = KEY_PIN;

    my_button_register(&key);
    my_button_start();

    /* warning */
    warning_thread();
    /* end of warning */

    /* register test */
    reg_value_ptr = &RTC_CTL;
    rt_kprintf("address:0x%8x\n",reg_value_ptr);
    rt_kprintf("value:0x%x\n",*reg_value_ptr);

    reg_value = RTC_CTL;
    if(*reg_value_ptr == reg_value)
    {
        rt_kprintf("相等");
    }
    else
    {
        rt_kprintf("不相等");
    }

    rt_kprintf("value: 0x%x\n",reg_value);
    /* end of register test */


    return RT_EOK;
}


void key_cb(struct my_button *button)
{
    switch (button->event)
    {
    case BUTTON_EVENT_CLICK_UP:
        led_toggle();
        rt_kprintf("This is click up callback!\n");
        break;
    case BUTTON_EVENT_HOLD_CYC:
        rt_kprintf("This is hold cyc callback!\n");
        break;
    default:
        ;
    }
}


