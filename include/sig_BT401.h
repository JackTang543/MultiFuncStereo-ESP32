#ifndef __SIG_BT401_H__
#define __SIG_BT401_H__

#include <Arduino.h>
#include <string.h>
#include "define.h"
#include "sig_app_menu.h"

//蓝牙连接状态(TS+xx)
typedef enum{
    NoLink = 0,     //无连接
    BTLinkIdle,     //空闲模式or音乐暂停
    PlayingMusic    //正在放音乐
}sBT401_BTState_t;
    
//用于保存芯片的一些状态
typedef struct{
    uint8_t Volume;     //音量
    uint8_t PlayORstop; //播放:1,暂停:0
    uint8_t Mode;       //模式
    uint8_t Mute;       //是否静音
    uint8_t DAC_State;  //DAC是否输出(输出or高阻)
    uint8_t AutoTrans;  //自动回传参数
    uint8_t Note_Audio; //是否播放提示音
    uint8_t Audio_EQ;   //音频EQ
    uint8_t Btn_Func;   //设置按键关闭
    uint8_t BT_ReLink;  //设置蓝牙上电回连
    
    sBT401_BTState_t BTstate;   //蓝牙状态
}sBT401_Param_t;

//函数返回值
typedef enum{
    sBT401_RET_OK = 0,  //返回OK,也是芯片返回OK
    sBT401_RET_ERR1,    //数据帧错误
    sBT401_RET_ERR2,    //命令不存在
    sBT401_RET_ERR3,    //录音时设备不在线或者其他错误
    sBT401_RET_ERR4,    //指令超出范围
    sBT401_RET_ERR5,    //指定设备时设备不在线或者异常
    sBT401_RET_ERR6     //指定的路径时,路径不存在
}sBT401_RET_t;

#define SIG_BT401_COMM_SET_VOLUME    ((char*)("CA"))
#define SIG_BT401_COMM_PLAYORSTOP    ((char*)("CB"))
#define SIG_BT401_COMM_WORKMODE      ((char*)("CM"))
#define SIG_BT401_COMM_NextMusic     ((char*)("CC"))
#define SIG_BT401_COMM_PrevMusic     ((char*)("CD"))
#define SIG_BT401_COMM_PlayedTime    ((char*)("MK"))
#define SIG_BT401_COMM_PlayAllTime   ((char*)("MT"))
#define SIG_BT401_COMM_GetWorkMode   ((char*)("QM"))
#define SIG_BT401_COMM_GetCurrStatus ((char*)("MP"))



void sBT401_Init();
void sBT401_PowerSet(uint8_t en);
void sBT401_SendByte(uint8_t byte);
void sBT401_SendCommand(char* cmd,int16_t param);

void sBT401_TransComm_SetVolume(uint8_t volume);
void sBT401_TransComm_Play();
void sBT401_TransComm_NextWorkMode();
void sBT401_TransComm_NextMusic();
void sBT401_TransComm_PrevMusic();
void sBT401_TransComm_GetPlayedTime();
void sBT401_TransComm_GetPlayAllTime();
void sBT401_TransComm_GetWorkMode();
void sBT401_TransComm_GetCurrStatus();

void sBT401_CheckReceiveData(void);
void sBT401_AnalysisReceiveData(void);

void sBT401_ARD_BTStatus(int8_t param);
void sBT401_ARD_PlayedTime(uint16_t playedtime_s);
void sBT401_ARD_PlayAllTime(uint16_t playalltime_s);
void sBT401_ARD_WorkMode(uint8_t work_mode);
void sBT401_ARD_GetCurrStatus(uint8_t curr_status);
void sBT401_ARD_GetInOutInfo(uint8_t info);



#endif
