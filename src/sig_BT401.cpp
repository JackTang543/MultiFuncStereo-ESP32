#include "sig_BT401.h"


//使用Serial1

sBT401_Param_t sBT401_Param;

String ReceiveData;

void sBT401_SendByte(uint8_t byte){
    //用十六进制发送一个字符
    Serial1.printf("%c",byte);
}

//发送命令
void sBT401_SendCommand(char* cmd,int16_t param){
    uint8_t num;
    char send[2] = {0,0};
    if(param >= 0){
        send[0] = (param / 10) + '0';
        send[1] = (param % 10) + '0';

        Serial1.printf("AT+%c%c%c%c\n",cmd[0],cmd[1],send[0],send[1]);
    }else{
        Serial1.printf("AT+%c%c\n",cmd[0],cmd[1]);
    }
    
}

void sBT401_Init(){
    //使能BT401
    digitalWrite(BT401_EN,HIGH);
}

//设置BT401的电源
void sBT401_PowerSet(uint8_t en){
    if(en){
        digitalWrite(BT401_EN,HIGH);
    }else{
        digitalWrite(BT401_EN,LOW);
    }
}


//发送设置音量的命令
void sBT401_TransComm_SetVolume(uint8_t volume){
    //保存一下
    sBT401_Param.Volume = volume;
    sBT401_SendCommand(SIG_BT401_COMM_SET_VOLUME,volume);
}

//发送播放指令
void sBT401_TransComm_Play(){
    sBT401_Param.PlayORstop = !sBT401_Param.PlayORstop;
    sBT401_SendCommand(SIG_BT401_COMM_PLAYORSTOP,-1);
}

//发送下一个工作模式
void sBT401_TransComm_NextWorkMode(){
    sBT401_SendCommand(SIG_BT401_COMM_WORKMODE,0);
}

//下一首
void sBT401_TransComm_NextMusic(){
    sBT401_SendCommand(SIG_BT401_COMM_NextMusic,-1);
}

//上一首
void sBT401_TransComm_PrevMusic(){
    sBT401_SendCommand(SIG_BT401_COMM_PrevMusic,-1);
}
//发送获取已经播放了的时长
void sBT401_TransComm_GetPlayedTime(){
    sBT401_SendCommand(SIG_BT401_COMM_PlayedTime,-1);
}
//发送获取歌曲总时长
void sBT401_TransComm_GetPlayAllTime(){
    sBT401_SendCommand(SIG_BT401_COMM_PlayAllTime,-1);
}
//发送获取工作模式
void sBT401_TransComm_GetWorkMode(){
    sBT401_SendCommand(SIG_BT401_COMM_GetWorkMode,-1);
}
//发送当前播放状态
void sBT401_TransComm_GetCurrStatus(){
    sBT401_SendCommand(SIG_BT401_COMM_GetCurrStatus,-1);
}

//检查是否有收到数据
void sBT401_CheckReceiveData(){
    //如果有数据的话就会接收并保存
    if(Serial1.available() > 0){
        ReceiveData = Serial1.readStringUntil('\n');
        //接收完成开始解析
        sBT401_AnalysisReceiveData();
    }
}

//分析接收到的数据
void sBT401_AnalysisReceiveData(){
    int8_t index = -1;
    String param_str;
    //解析TS+
    if(ReceiveData.indexOf("TS+") != -1){
        index = ReceiveData.indexOf("TS+");
        //截取第3到4的字符串(参数)
        param_str = ReceiveData.substring(index + 3, index + 5);
        sBT401_ARD_BTStatus(param_str.toInt());
    }
    //解析MK+(播放时间信息)
    if(ReceiveData.indexOf("MK+") != -1){
        index = ReceiveData.indexOf("MK+");
        //截取3到10的字符串(播放时间信息)
        param_str = ReceiveData.substring(index + 3, index + 11);
        //把十六进制数转换到10进制数
        sBT401_ARD_PlayedTime(strtol(param_str.c_str(), NULL, 16));
    }
    //解析MT+(当前文件播放的总时间)
    if(ReceiveData.indexOf("MT+") != -1){
        index = ReceiveData.indexOf("MT+");
        param_str = ReceiveData.substring(index + 3, index + 11);
        sBT401_ARD_PlayAllTime(strtol(param_str.c_str(),NULL,16));

    }
    //解析QM+(工作模式)
    if(ReceiveData.indexOf("QM+") != -1){
        index = ReceiveData.indexOf("QM+");
        param_str = ReceiveData.substring(index + 3, index + 5);
        //芯片上电为00,蓝牙:01,U盘:02,TF卡:03,外音输入AUX:05,PC声卡:06,REC录音:08,假关机(空闲):09
        sBT401_ARD_WorkMode(param_str.toInt());
    }
    //解析MP+(工作状态)
    if(ReceiveData.indexOf("MP+") != -1){
        index = ReceiveData.indexOf("MP+");
        param_str = ReceiveData.substring(index + 3, index + 5);
        //1:停止,2:播放,3:暂停
        sBT401_ARD_GetCurrStatus(param_str.toInt());
    }
    //解析MU+(插入拔出)
    if(ReceiveData.indexOf("MU+") != -1){
        index = ReceiveData.indexOf("MU+");
        param_str = ReceiveData.substring(index + 3, index + 5);
        
        sBT401_ARD_GetInOutInfo(param_str.toInt());
    }
    //解析QA+(上电返回音量)
    if(ReceiveData.indexOf("QA+") != -1){
        index = ReceiveData.indexOf("QA+");
        param_str = ReceiveData.substring(index + 3, index + 5);
        
        sigAppMENU_SetVolume(param_str.toInt());
    }

}

//ARD:分析TS+xx类型的数据,也就是蓝牙状态信息
void sBT401_ARD_BTStatus(int8_t param){
    if(param == 0){
        //等待配对中
        sigAppMENU_SetInOutInfo(6);
        sBT401_Param.BTstate = NoLink;
    }else if(param == 1){
        //空闲模式or音乐暂停
        sBT401_Param.BTstate = BTLinkIdle;
    }else if(param == 2){
        //正在放音乐
        sBT401_Param.BTstate = PlayingMusic;
    }
    
    sigAppMENU_SetBtCurrStatus(param);

}
//ARD:分析MK+xxxxxxxx类型的数据,也就是已播放时长
void sBT401_ARD_PlayedTime(uint16_t playedtime_s){
    sigAppMENU_SetPlayedTime(playedtime_s);
}
//ARD:分析MT+xxxxxxxx类型的数据,也就是歌曲总时长
void sBT401_ARD_PlayAllTime(uint16_t playalltime_s){
    sigAppMENU_SetPlayAllTime(playalltime_s);
}
//ARD:分析QM+xx类型数据,也就是工作的模式
void sBT401_ARD_WorkMode(uint8_t work_mode){
    sigAppMENU_SetWorkMode(work_mode);
}
//ARD:分析MP+xx类型数据,是当前播放状态
void sBT401_ARD_GetCurrStatus(uint8_t curr_status){
    sigAppMENU_SetUsbTfCurrStatus(curr_status);
}
//ARD:分析MU+xx类型数据,插入或拔出的信息
void sBT401_ARD_GetInOutInfo(uint8_t info){
    sigAppMENU_SetInOutInfo(info);
}



