/*
 * Copyright (c) 2006-2021, RT-Thread Development Team
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Change Logs:
 * Date           Author       Notes
 * 2021-05-20     shangwang7       the first version
 */
#include <rtthread.h>
#include <dfs_posix.h> /* ����Ҫʹ���ļ�����ʱ����Ҫ�������ͷ�ļ� */

static void mkdir_sample(void)
{
    int ret;

    /* ����Ŀ¼ */
    ret = mkdir("/dir_test", 0x777);
    if (ret < 0)
    {
        /* ����Ŀ¼ʧ�� */
        rt_kprintf("dir error!\n");
    }
    else
    {
        /* ����Ŀ¼�ɹ� */
        rt_kprintf("mkdir ok!\n");
    }
}
/* ������ msh �����б��� */
MSH_CMD_EXPORT(mkdir_sample, mkdir sample);
