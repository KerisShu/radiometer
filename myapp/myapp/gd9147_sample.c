/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-18     shangwang7       the first version
 * 显示屏设备
 */
#include <rtthread.h>
#include <board.h>
#include <rtdevice.h>
#include <rtdef.h>

#define THREAD_STACK_SIZE   1024
#define THREAD_PRIORITY     30
#define THREAD_TIMESLICE    50

#define  RT_TOUCH_CTRL_GET_ID            (0)   /* 读设备ID */
#define  RT_TOUCH_CTRL_GET_INFO          (1)   /* 获取设备信息 */
#define  RT_TOUCH_CTRL_SET_MODE          (2)   /* 设置工作模式 */
#define  RT_TOUCH_CTRL_SET_X_RANGE       (3)   /* 设置 X 轴分辨率  */
#define  RT_TOUCH_CTRL_SET_Y_RANGE       (4)   /* 设置 Y 轴分辨率 */
#define  RT_TOUCH_CTRL_SET_X_TO_Y        (5)   /* 交换 X、Y 轴坐标 */
#define  RT_TOUCH_CTRL_DISABLE_INT       (6)   /* 使能中断 */
#define  RT_TOUCH_CTRL_ENABLE_INT        (7)   /* 失能中断 */
#define  RT_TOUCH_EVENT_DOWN              1
#define  RT_TOUCH_EVENT_MOVE              1

static rt_thread_t  gt9147_thread = RT_NULL;
static rt_sem_t     gt9147_sem = RT_NULL;
static rt_device_t  dev = RT_NULL;
static struct       rt_touch_data *read_data;

struct rt_touch_data
{
    rt_uint8_t          event;
    rt_uint8_t          track_id;
    rt_uint8_t          width;
    rt_uint16_t         x_coordinate;
    rt_uint16_t         y_coordinate;
    rt_tick_t           timestamp;
};


/* 读取数据线程入口函数 */
static void gt9147_entry(void *parameter)
{
    struct rt_touch_data *read_data;
    read_data = (struct rt_touch_data *)rt_malloc(sizeof(struct rt_touch_data) * 5);

    while (1)
    {
        /* 请求信号量 */
        (gt9147_sem, RT_WAITING_FOREVER);
        /* 读取五个点的触摸信息 */
        if (rt_device_read(dev, 0, read_data, 5) == 5)
        {
            for (rt_uint8_t i = 0; i < 5; i++)
            {
                if (read_data[i].event == RT_TOUCH_EVENT_DOWN || read_data[i].event == RT_TOUCH_EVENT_MOVE)
                {
                    rt_kprintf("%d %d %d %d %d\n",
                                read_data[i].track_id,
                                read_data[i].x_coordinate,
                                read_data[i].y_coordinate,
                                read_data[i].timestamp,
                                read_data[i].width);
                }
            }
        }
        /* 打开中断 */
        rt_device_control(dev, RT_TOUCH_CTRL_ENABLE_INT, RT_NULL);
    }
}

/* 接收回调函数 */
static rt_err_t rx_callback(rt_device_t dev, rt_size_t size)
{
    /* 关闭中断 */
    rt_device_control(dev, RT_TOUCH_CTRL_DISABLE_INT, RT_NULL);
    /* 释放信号量 */
    rt_sem_release(gt9147_sem);
    return 0;
}

static int gt9147_sample(void)
{
    /* 查找 Touch 设备 */
    dev = rt_device_find("gd25q");

    if (dev == RT_NULL)
    {
        rt_kprintf("can't find device:%s\n", "touch");
        return -1;
    }
    /* 以中断的方式打开设备 */
    if (rt_device_open(dev, RT_DEVICE_FLAG_INT_RX) != RT_EOK)
    {
        rt_kprintf("open device failed!");
        return -1;
    }
    /* 设置接收回调 */
    rt_device_set_rx_indicate(dev, rx_callback);
    /* 创建信号量 */
    gt9147_sem = rt_sem_create("dsem", 0, RT_IPC_FLAG_FIFO);

    if (gt9147_sem == RT_NULL)
    {
        rt_kprintf("create dynamic semaphore failed.\n");
        return -1;
    }
    /* 创建读取数据线程 */
    gt9147_thread = rt_thread_create("thread1",
                                     gt9147_entry,
                                     RT_NULL,
                                     THREAD_STACK_SIZE,
                                     THREAD_PRIORITY,
                                     THREAD_TIMESLICE);
    /* 启动线程 */
    if (gt9147_thread != RT_NULL)
        rt_thread_startup(gt9147_thread);

    return 0;
}

MSH_CMD_EXPORT(gt9147_sample, gt9147 sample);
