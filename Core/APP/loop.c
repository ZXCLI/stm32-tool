#include "loop.h"


CAN_TxHeaderTypeDef TXHeader;
CAN_RxHeaderTypeDef RXHeader;
uint8_t CAN_RXmessage[8];

// /*
//  *各种初始化
//  */
void MY_Init(void)
{
    
    __HAL_SPI_ENABLE(&hspi2);                                           	// 开启SPI
    OLED_Init();                                                        	// 初始化OLED

    HAL_TIM_PWM_Start_IT(&htim15, TIM_CHANNEL_1);                       	// 启动定时器

    CAN_Filter_Config();
    CAN_Start();

    key_init();
}

void CAN_Filter_Config(void)
{
    CAN_FilterTypeDef canFilterConfig;
    
    canFilterConfig.FilterBank = 0;//过滤器组0
    canFilterConfig.FilterMode = CAN_FILTERMODE_IDMASK;//掩码模式
    canFilterConfig.FilterScale = CAN_FILTERSCALE_32BIT;//32位过滤器
    canFilterConfig.FilterIdHigh = 0x0000;//32位过滤器验证码的高16位
    canFilterConfig.FilterIdLow = 0x0000;//32位过滤器验证码的低16位
    canFilterConfig.FilterMaskIdHigh = 0x0000;//32位过滤器屏蔽码的高16位
    canFilterConfig.FilterMaskIdLow = 0x0000;//32位过滤器屏蔽码的低16位
    canFilterConfig.FilterFIFOAssignment = CAN_RX_FIFO0;//过滤器0关联到FIFO0
    canFilterConfig.FilterActivation = ENABLE;
    canFilterConfig.SlaveStartFilterBank = 14;
    
    if (HAL_CAN_ConfigFilter(&hcan, &canFilterConfig) != HAL_OK)
    {
        Error_Handler();
    }
}

void CAN_Start(void)
{
    HAL_CAN_Start(&hcan);
    HAL_CAN_ActivateNotification(&hcan, CAN_IT_RX_FIFO0_MSG_PENDING); // 开启FIFO0的接收中断
}

void CAN_Send(uint32_t id, uint8_t *data, uint8_t len)
{
    CAN_TxHeaderTypeDef txHeader;
    uint32_t txMailbox;

    txHeader.DLC = len;//要发送的字节数
    txHeader.ExtId = id;//扩展帧ID
    txHeader.IDE = CAN_ID_EXT;//IDE为扩展帧格式
    txHeader.RTR = CAN_RTR_DATA;//表示此帧为数据帧
    txHeader.TransmitGlobalTime = DISABLE;

    HAL_CAN_AddTxMessage(&hcan, &txHeader, data, &txMailbox);
}


void HAL_CAN_RxFifo0MsgPendingCallback(CAN_HandleTypeDef *hcan)//接受邮箱0挂起中断回调函数
{
	HAL_CAN_GetRxMessage(hcan,CAN_FILTER_FIFO0,&RXHeader,CAN_RXmessage);//获取数据
}


void HAL_TIM_OC_DelayElapsedCallback(TIM_HandleTypeDef *htim)
{
    key_poll();
}


