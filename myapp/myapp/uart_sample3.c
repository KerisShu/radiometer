#include <rtthread.h>


#define SAMPLE_UART3_NAME       "uart3"       /* 需要操作的设备 */

static rt_device_t serial3;                   /* 设备句柄 */
static char str[] = "hello RT-Thread3!\r\n";  /* 需要发送的数据 */

static int uart3_sample(void)
{
    
	rt_err_t ret3 = RT_EOK;
    rt_size_t send_len = 0;

    /* 查找系统中的串口设备 */
 
	serial3 = rt_device_find(SAMPLE_UART3_NAME);

	if (!serial3)
    {
        rt_kprintf("find %s failed!\n", SAMPLE_UART3_NAME);
        return -RT_ERROR;
    }

    /* 以中断接收及轮询发送模式打开串口设备 */
	ret3 = rt_device_open(serial3, RT_DEVICE_FLAG_INT_RX);

	if (ret3 != RT_EOK)
    {
        rt_kprintf("open device3 failed\r\n");
        return -RT_ERROR;
    }
	
    /* 发送字符串 */
	send_len = rt_device_write(serial3, 0, str, (sizeof(str) - 1));
		
    if (send_len != sizeof(str) - 1)
    {
        rt_kprintf("send data failed\r\n");
        return -RT_ERROR;
    }
    /* 关闭设备 */
   
	ret3 = rt_device_close(serial3);

	if (ret3 != RT_EOK)
    {
        rt_kprintf("close device3 failed\r\n");
        return -RT_ERROR;
    }

    rt_kprintf("serial device3 test successful\r\n");

    return RT_EOK;
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(uart3_sample, uart device sample);