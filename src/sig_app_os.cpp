#include "sig_app_os.h"

//此文件用来管理所有FreeRTOS任务



TimerHandle_t BtnTimer;
TimerHandle_t ECTimer;
TimerHandle_t BTRxCheck;
TimerHandle_t BT_0S5_Tx;
TimerHandle_t VFD_Update;

//由定时器调用的按键检查函数
void sigOS_BtnTimerCallback(TimerHandle_t xTimer){
    sigInit_BtnHandler();
}

void sigOS_ECTimerCallback(TimerHandle_t xTimer){
    sEC_TrigDetectHandler();
}

void sigOS_BTRxCheckCallback(TimerHandle_t xTimer){
    sBT401_CheckReceiveData();
}

void sigOS_BT_0S5_TxCallback(TimerHandle_t xTimer){
    sBT401_TransComm_GetCurrStatus();
    vTaskDelay(10 / portTICK_PERIOD_MS);
    sBT401_TransComm_GetPlayedTime();
    //sBT401_TransComm_GetPlayAllTime();
    //sBT401_TransComm_GetWorkMode();
    
}

void sigOS_VFD_UpdateCallback(TimerHandle_t xTimer){
    
}

void sigOS_VFD_Task(void *pvParameters){
    while(1){
        sigAppMENU_Handler();
    }
}

void sigOS_Create_AllTask(void){
    //*********************创建按键定时器**************************
     BtnTimer = xTimerCreate("ButtonHandler",              //定时器名称
                             pdMS_TO_TICKS(10),            //定时器周期
                             pdTRUE,                       //自动重载
                             (void*)0,                     //定时器ID
                             sigOS_BtnTimerCallback);      //定时器回调

    //*********************创建编码器定时器*************************
     ECTimer  = xTimerCreate("EncoderHandler",             //定时器名称
                             pdMS_TO_TICKS(20),            //定时器周期
                             pdTRUE,                       //自动重载
                             (void*)1,                     //定时器ID
                             sigOS_ECTimerCallback);       //定时器回调

    //*********************检查蓝牙返回信息的定时器*************************
     BTRxCheck= xTimerCreate("BTRxCheck",                  //定时器名称
                             pdMS_TO_TICKS(50),            //定时器周期
                             pdTRUE,                       //自动重载
                             (void*)2,                     //定时器ID
                             sigOS_BTRxCheckCallback);     //定时器回调

    BT_0S5_Tx=xTimerCreate("BT_0S5_Tx",                //定时器名称
                             pdMS_TO_TICKS(500),           //定时器周期
                             pdTRUE,                       //自动重载
                             (void*)3,                     //定时器ID
                             sigOS_BT_0S5_TxCallback);   //定时器回调

    VFD_Update = xTimerCreate("VFD_Update",                //定时器名称
                             pdMS_TO_TICKS(100),           //定时器周期
                             pdTRUE,                       //自动重载
                             (void*)4,                     //定时器ID
                             sigOS_VFD_UpdateCallback);   //定时器回调

    xTaskCreate(sigOS_VFD_Task,          // 任务函数
                "sigOS_VFD_Task",        // 任务名称
                8192,             // 任务堆栈大小（字节）
                NULL,            // 传递给任务函数的参数
                configMAX_PRIORITIES - 1 ,               // 任务优先级
                NULL);           // 任务句柄

    //**********************下面是启动任务*************************
    //启动定时器
    xTimerStart(BtnTimer,0);
    xTimerStart(ECTimer ,0);
    xTimerStart(BTRxCheck ,0);
    xTimerStart(BT_0S5_Tx ,0);
    //xTimerStart(VFD_Update ,0);
                                          
}



