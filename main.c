#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_memmap.h"
#include "inc/hw_types.h"
#include "driverlib/sysctl.h"
#include "driverlib/rom.h"
#include "driverlib/gpio.h"
#include "driverlib/pwm.h"
#include "driverlib/fpu.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom_map.h"
#include "gpio_pwm.h"
/*
 * PF1,PF2产生PWM波
 * author:RsgoFov
 * attention:使用PINMUX生成引脚使能；
 * 			 配置尽量不适用或运算，否则可能配置失败
 * 2017.1.24
 */
int main(void)
{
	SysCtlClockSet(SYSCTL_SYSDIV_2_5 |SYSCTL_USE_PLL|SYSCTL_OSC_MAIN |SYSCTL_XTAL_16MHZ);
	//设置系统时钟为80MHZ
	PortFunctionInit();
    SysCtlPWMClockSet(SYSCTL_PWMDIV_64);//64不分频
	PWMGenConfigure(PWM1_BASE,PWM_GEN_2,PWM_GEN_MODE_UP_DOWN| PWM_GEN_MODE_NO_SYNC);	//配置PWM发生器模式，加
	//减计数，不同步,定义包含在PWM.H
	PWMGenConfigure(PWM1_BASE,PWM_GEN_3,PWM_GEN_MODE_UP_DOWN| PWM_GEN_MODE_NO_SYNC);

	PWMGenPeriodSet(PWM1_BASE,PWM_GEN_2,5000);		//设置PWM发生器2,3的频率，时钟频率/PWM分频数/n，80M/1/800000=100HZ
	PWMGenPeriodSet(PWM1_BASE,PWM_GEN_3,5000);		//设置PWM发生器2,3的频率，时钟频率/PWM分频数/n，80M/1/800000=100HZ
	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_5,1000);		//设置PWM5,6的占空比
	PWMPulseWidthSet(PWM1_BASE, PWM_OUT_6,1000);

	PWMOutputState(PWM1_BASE,PWM_OUT_5_BIT |PWM_OUT_6_BIT, true);//使能PWM5,6的输出
	PWMGenEnable(PWM1_BASE, PWM_GEN_2);					//使能PWM发生器
	PWMGenEnable(PWM1_BASE, PWM_GEN_3);					//不能使用或运算
	while(1);

}
