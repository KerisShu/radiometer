/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-19     shangwang7       the first version
 */
#ifndef MYAPP_MYAPP_LED_H_
#define MYAPP_MYAPP_LED_H_

#define LED3_PIN 11
#define LED4_PIN 12
#define LED5_PIN 13

int led_init(void);  //Initial LEDs
int led_on(void);    //Turn on LEDs
int led_off(void);   //Turn off LEDs
int led_toggle(void);//LEDs toggles

#endif /* APPLICATIONS_MYAPP_LED_H_ */
