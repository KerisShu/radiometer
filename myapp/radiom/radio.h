/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-20     shangwang7       the first version
 */
#ifndef MYAPP_RADIOM_RADIO_H_
#define MYAPP_RADIOM_RADIO_H_

/* pins */
#ifndef LED_WARN_PIN
    #define     LED_WARN_PIN    10  //F0
#endif

#define BUZZER_PIN      56    // G0

#ifndef KEY_BUZZER_PIN
    #define KEY_BUZZER_PIN         14  //F4
#endif
/* end of pins */


/* funtions */
int warning_thread(void);
/* end of functions */


#endif /* APPLICATIONS_RADIOM_RADIO_H_ */
