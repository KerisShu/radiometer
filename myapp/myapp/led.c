/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-19     shangwang7       the first version
 */
#include <rtdevice.h>
#include "myapp/myapp/led.h"

/*
 * i/o parameters: NONE
 * fun: initial LEDs PIN
 */
int led_init(void)
{
    /* �趨 LED ����Ϊ�������ģʽ */
    rt_pin_mode(LED3_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED4_PIN, PIN_MODE_OUTPUT);
    rt_pin_mode(LED5_PIN, PIN_MODE_OUTPUT);

    return 0;
}

/*
 * i/o parameters: NONE
 * fun: turn on LEDs
 */
int led_on(void)
{
    /* ���� API ����͵�ƽ */
    rt_pin_write(LED3_PIN, PIN_LOW);
    rt_pin_write(LED4_PIN, PIN_LOW);
    rt_pin_write(LED5_PIN, PIN_LOW);

    return 0;
}

/*
 * i/o parameters: NONE
 * fun: turn off LEDs
 */
int led_off(void)
{
    /* ���� API ����͵�ƽ */
    rt_pin_write(LED3_PIN, PIN_LOW);
    rt_pin_write(LED4_PIN, PIN_LOW);
    rt_pin_write(LED5_PIN, PIN_LOW);

    return 0;
}


/*
 * i/o parameters: NONE
 * fun: LEDs toggle
 */
int led_toggle(void)
{
    /* ���� API ������ǰ��ƽ��Ȼ������෴��ƽ */
    rt_pin_write(LED3_PIN, !rt_pin_read(LED3_PIN));
    rt_pin_write(LED4_PIN, !rt_pin_read(LED4_PIN));
    rt_pin_write(LED5_PIN, !rt_pin_read(LED5_PIN));

    return 0;
}



