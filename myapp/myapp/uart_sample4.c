#include <rtthread.h>


#define SAMPLE_UART4_NAME       "uart4"       /* 需要操作的设备 */

static rt_device_t serial4;                   /* 设备句柄 */
static char str[] = "hello RT-Thread4!\r\n";  /* 需要发送的数据 */

static int uart4_sample(void)
{
    
	rt_err_t ret4 = RT_EOK;
    rt_size_t send_len = 0;

    /* 查找系统中的串口设备 */
 
	serial4 = rt_device_find(SAMPLE_UART4_NAME);

	if (!serial4)
    {
        rt_kprintf("find %s failed!\n", SAMPLE_UART4_NAME);
        return -RT_ERROR;
    }

    /* 以中断接收及轮询发送模式打开串口设备 */
	ret4 = rt_device_open(serial4, RT_DEVICE_FLAG_INT_RX);

	if (ret4 != RT_EOK)
    {
        rt_kprintf("open device4 failed\r\n");
        return -RT_ERROR;
    }
	
    /* 发送字符串 */
	send_len = rt_device_write(serial4, 0, str, (sizeof(str) - 1));
		
    if (send_len != sizeof(str) - 1)
    {
        rt_kprintf("send data failed\r\n");
        return -RT_ERROR;
    }
    /* 关闭设备 */
   
	ret4 = rt_device_close(serial4);

	if (ret4 != RT_EOK)
    {
        rt_kprintf("close device4 failed\r\n");
        return -RT_ERROR;
    }

    rt_kprintf("serial device4 test successful\r\n");

    return RT_EOK;
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(uart4_sample, uart device sample);