#ifndef _ENCODER_H
#define _ENCODER_H

#include "main.h"
#include "stdbool.h"

#define KEY_NUM 5       //按键数量，默认编码器按键为第一个顺延下去
#define ENCODER_NUM 0   //编码器数量，默认一个

typedef enum
{
  UP = ENCODER_NUM,
  DOWN,
  LEFT,
  RIGHT,
  ENTER,
}KEY_NAME;

typedef enum
{
  ENCODER_1 = 0,
}ENCODER_NAME;

typedef struct
{
    bool left;  //左旋标志位
    bool right; //右旋标志位

    //负责计数的变量
    uint32_t left_timeout;  //左旋超时计数
    uint32_t right_timeout; //右旋超时计数

    //负责记录状态的变量
    uint8_t state;       //当前状态
    uint8_t last_state;  //上一次状态

}ENCODER;

typedef struct
{
    GPIO_TypeDef* GPIO_left_part;
    GPIO_TypeDef* GPIO_right_part;
    uint16_t GPIO_left_pin;
    uint16_t GPIO_right_pin;

}ENCODER_GPIO;

typedef struct
{
    bool KeyPressed;    //按键按下标志位
    bool shortPress;    //短按标志位
    bool longPress;     //长按标志位

    //负责计数的变量
    uint32_t press_count;   //按下时间计数

    //及时清除未被读取的标志位的计数变量：
    uint32_t short_timeout; //短按超时计数                   
    uint32_t long_timeout;  //长按超时计数

    //负责记录状态的变量
    uint8_t state;       //当前状态
    uint8_t last_state;  //上一次状态

}KEY;

typedef struct
{
    GPIO_TypeDef* GPIO_part;
    uint16_t GPIO_pin;

}KEY_GPIO;

extern KEY KeyEvent[KEY_NUM];
extern ENCODER EncoderEvent[ENCODER_NUM];

extern ENCODER_GPIO EncoderEvent_GPIO[ENCODER_NUM];
extern KEY_GPIO KeyEvent_GPIO[KEY_NUM];

uint8_t encoder_read(uint8_t snack);
void encoder_poll(void);

void key_init();
uint8_t key_read(uint8_t snack);
void key_poll();

void timeout(uint32_t* TimeCount,bool* State);

#endif