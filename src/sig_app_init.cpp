#include "sig_app_init.h"



//全局定义触摸按键,id:1,长按单次触发,TTP223空闲时低电平,我要10ms调用你一次
sGBD Btn_TouchCenter(1,sGBD_LP_SGL_TRIG,sGBD_LEVEL_HIGH,10);
sGBD Btn_TouchLeft(2,sGBD_LP_SGL_TRIG,sGBD_LEVEL_HIGH,10);
sGBD Btn_TouchRight(3,sGBD_LP_SGL_TRIG,sGBD_LEVEL_HIGH,10);
//这是编码器的按键,空闲高电平
sGBD Btn_EC1Key(4,sGBD_LP_SGL_TRIG,sGBD_LEVEL_HIGH,10);


//对HAL_GetTick封装,用于传递给sGBD模块
uint32_t sigGet_Tick(void){
    return millis();
}

//初始化所有GPIO
void sigApp_InitAllGPIOs(void){
    //初始化触摸按键和编码器按键
    pinMode(BtnTouchLeftPIN  , INPUT);
    pinMode(BtnTouchRightPIN , INPUT);
    pinMode(BtnTouchCenterPIN, INPUT);
    pinMode(Encoder1keyPIN   , INPUT);
    //初始化旋转编码器外部触发
    pinMode(Encoder1aPIN,INPUT);
    pinMode(Encoder1bPIN,INPUT);
    attachInterrupt(digitalPinToInterrupt(Encoder1aPIN),sEC_1a_falling,FALLING);
    attachInterrupt(digitalPinToInterrupt(Encoder1bPIN),sEC_1b_falling,FALLING);
    //初始化TP5100充电芯片信号输入
    pinMode(TP5100StdbyPIN,INPUT_PULLUP);
    pinMode(TP5100ChrgPIN ,INPUT_PULLUP);
    //初始化I2C总线
    
    //初始化BT401使能
    pinMode(BT401_EN,OUTPUT);
    //初始化BT401的串口
    Serial1.begin(115200,SERIAL_8N1,BT401_RX,BT401_TX);
    //初始化UART0也是VFD1602的串口
    Serial.begin(115200);


}


//初始化所有外设
void sigApp_InitAllPeph(void){
    //*********下面是初始化触摸按键**************
    
    //设置触摸按键触发回调
    Btn_TouchCenter.sGBD_SetButtonTrigCb(sig_app_callBack_Btn);
    Btn_TouchLeft  .sGBD_SetButtonTrigCb(sig_app_callBack_Btn);
    Btn_TouchRight .sGBD_SetButtonTrigCb(sig_app_callBack_Btn);
    Btn_EC1Key     .sGBD_SetButtonTrigCb(sig_app_callBack_Btn);
    //设置按键获取时间的函数
    Btn_TouchCenter.sGBD_SetTickerFunc(sigGet_Tick);
    Btn_TouchLeft  .sGBD_SetTickerFunc(sigGet_Tick);
    Btn_TouchRight .sGBD_SetTickerFunc(sigGet_Tick);
    Btn_EC1Key     .sGBD_SetTickerFunc(sigGet_Tick);

    //*********下面是初始化旋转编码器**************
    
    sEC_Init();
    //设置旋转编码器的触发回调
    sEC_SetECTrigCb(sig_app_callBack_EC);

    //初始化BT401
    sBT401_Init();

    //初始化INA219;
    sINA219_Init();
    

}


//用于给OS模块的任务处理调用
void sigInit_BtnHandler(void){
    Btn_TouchCenter.sGBD_Button_handler(digitalRead(BtnTouchCenterPIN));
    Btn_TouchLeft  .sGBD_Button_handler(digitalRead(BtnTouchLeftPIN));
    Btn_TouchRight .sGBD_Button_handler(digitalRead(BtnTouchRightPIN));
    Btn_EC1Key     .sGBD_Button_handler(digitalRead(Encoder1keyPIN));
}
