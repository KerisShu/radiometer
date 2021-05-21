#include <rtthread.h>


#define SAMPLE_UART2_NAME       "uart2"       /* 需要操作的设备 */

static rt_device_t serial2;                   /* 设备句柄 */
static char str[] = "hello RT-Thread2!\r\n";  /* 需要发送的数据 */

static int uart2_sample(void)
{
    
	rt_err_t ret2 = RT_EOK;
    rt_size_t send_len = 0;

    /* 查找系统中的串口设备 */
 
	serial2 = rt_device_find(SAMPLE_UART2_NAME);

	if (!serial2)
    {
        rt_kprintf("find %s failed!\n", SAMPLE_UART2_NAME);
        return -RT_ERROR;
    }

    /* 以中断接收及轮询发送模式打开串口设备 */
	ret2 = rt_device_open(serial2, RT_DEVICE_FLAG_INT_RX);

	if (ret2 != RT_EOK)
    {
        rt_kprintf("open device2 failed\r\n");
        return -RT_ERROR;
    }
	
    /* 发送字符串 */
	send_len = rt_device_write(serial2, 0, str, (sizeof(str) - 1));
		
    if (send_len != sizeof(str) - 1)
    {
        rt_kprintf("send data failed\r\n");
        return -RT_ERROR;
    }
    /* 关闭设备 */
   
	ret2 = rt_device_close(serial2);

	if (ret2 != RT_EOK)
    {
        rt_kprintf("close device2 failed\r\n");
        return -RT_ERROR;
    }

    rt_kprintf("serial device2 test successful\r\n");

    return RT_EOK;
}
/* 导出到 msh 命令列表中 */
MSH_CMD_EXPORT(uart2_sample, uart device sample);