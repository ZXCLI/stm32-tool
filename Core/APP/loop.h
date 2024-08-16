#ifndef _LOOP_H
#define _LOOP_H

#include "OLEDUI.h"
#include "IQmathLib.h"
#include "stdbool.h"
#include "string.h"
#include "SEGGER_RTT.h"
#include "menu.h"
#include "encoder.h"
#include "eeprom.h"
//#include "default.h"

//#include "dma.h"
#include "adc.h"
#include "spi.h"
#include "tim.h"
#include "can.h"


void MY_loop(void);
void MY_Init(void);


void CAN_Filter_Config(void); //CAN过滤器配置
void CAN_Start(void); //CAN启动
void CAN_Send(uint32_t id, uint8_t *data, uint8_t len); //CAN发送

#endif