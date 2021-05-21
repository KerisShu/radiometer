/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-20     shangwang7       the first version
 */
#ifndef MYAPP_SENSORS_SENSOR_DALLAS_DS18B20_H_
#define MYAPP_SENSORS_SENSOR_DALLAS_DS18B20_H_


#include <rthw.h>
#include <rtthread.h>
#include <rtdevice.h>
#include "sensor.h"

#define CONNECT_SUCCESS  0
#define CONNECT_FAILED   1

struct ds18b20_device
{
    rt_base_t pin;
    rt_mutex_t lock;
};
typedef struct ds18b20_device *ds18b20_device_t;

uint8_t ds18b20_init(rt_base_t pin);
int32_t ds18b20_get_temperature(rt_base_t pin);
int rt_hw_ds18b20_init(const char *name, struct rt_sensor_config *cfg);




#endif /* APPLICATIONS_SENSORS_SENSOR_DALLAS_DS18B20_H_ */
