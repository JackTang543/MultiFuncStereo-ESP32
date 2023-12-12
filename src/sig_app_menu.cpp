#include "sig_app_menu.h"

#include "sig_VFD1602.h"


typedef void (*menu_operation_cb_f)(void);


//菜单当前索引值
uint8_t menu_curr_index;
//主菜单模式,FM/MUSIC
MENU_MAIN_FUNC_t main_menu_func;
//如果有事件这个标志位就会非0
InstantEventFlag_t InstantEventFlag;

typedef struct {
    uint8_t isCycleMode; //是否是循环一首模式
    uint8_t playmode;    //芯片上电为00,蓝牙:01,U盘:02,TF卡:03,外音输入AUX:05,PC声卡:06,REC录音:08,假关机(空闲):09
    uint8_t playstatus_usbtf;  //0:停止,1:播放,2:暂停
    uint8_t playstatus_bt;     //0:等待配对,1:暂停,2:播放,
    uint16_t playedtime; //放了多久了:sec
    uint16_t alltime;    //音乐总时长:sec
    uint8_t volume;
    uint8_t brightness;
}menu_main_music_info_t;

menu_main_music_info_t menu_main_music_info;

void MenuShow_MainMusic(){
    //处在TF卡/U盘模式下时
    if(menu_main_music_info.playmode == 2 || menu_main_music_info.playmode == 3){
            //显示已播放时间
        uint8_t x1 = 0; //这是显示的起始位置
        sVFD1602_CGRAM_WriteNumber(x1 + 0,0,menu_main_music_info.playedtime / 60);
        sVFD1602_CGRAM_WriteUserChar(x1 + 1,0,SymbolFont[10]);
        if((menu_main_music_info.playedtime % 60) < 10){
            sVFD1602_CGRAM_WriteNumber(x1 + 2,0,0);
            sVFD1602_CGRAM_WriteNumber(x1 + 3,0,menu_main_music_info.playedtime % 60);
        }else{
           sVFD1602_CGRAM_WriteNumber(x1 + 2,0,menu_main_music_info.playedtime % 60);
        }
        //显示总时长
        uint8_t x2 = 7; //这是显示的起始位置
        sVFD1602_CGRAM_WriteNumber(x2 + 0,0,menu_main_music_info.alltime / 60);
        sVFD1602_CGRAM_WriteUserChar(x2 + 1,0,SymbolFont[10]);
        if((menu_main_music_info.alltime % 60) < 10){
            sVFD1602_CGRAM_WriteNumber(x2 + 2,0,0);
            sVFD1602_CGRAM_WriteNumber(x2 + 3,0,menu_main_music_info.alltime % 60);
        }else{
            sVFD1602_CGRAM_WriteNumber(x2 + 2,0,menu_main_music_info.alltime % 60);
        }
        //显示工作模式
        uint8_t x3 = 13;
        if(menu_main_music_info.playmode == 1){
            sVFD1602_CGRAM_WriteString(x3 + 0,0,(char*)" BT",0);
        }else if(menu_main_music_info.playmode == 2){
            sVFD1602_CGRAM_WriteString(x3 + 0,0,(char*)"USB",0);
        }else if(menu_main_music_info.playmode == 3){
            sVFD1602_CGRAM_WriteString(x3 + 0,0,(char*)" TF",0);
        }else if(menu_main_music_info.playmode == 5){
            sVFD1602_CGRAM_WriteString(x3 + 0,0,(char*)"AUX",0);
        }else if(menu_main_music_info.playmode == 6){
            sVFD1602_CGRAM_WriteString(x3 + 0,0,(char*)" PC",0);
        }else if(menu_main_music_info.playmode == 8){
            sVFD1602_CGRAM_WriteString(x3 + 0,0,(char*)"REC",0);
        }else if(menu_main_music_info.playmode == 0){
            sVFD1602_CGRAM_WriteString(x3 + 0,0,(char*)"NUL",0);
        }
    }
    //蓝牙模式
    else if(menu_main_music_info.playmode == 1){
        sVFD1602_CGRAM_WriteString(0,0,(char*)"BlueTooth Mode",0);
    }
    //AUX
    else if(menu_main_music_info.playmode == 5){
        sVFD1602_CGRAM_WriteString(0,0,(char*)"External Audio",0);
    }
    else if(menu_main_music_info.playmode == 6){
        sVFD1602_CGRAM_WriteString(0,0,(char*)"SoundCard Mode",0);
    }
    
    //这是显示小图标
    //如果处于播放模式
    //sVFD1602_GRAM_IconSet(ICON_CLOCK,ICON_EN_ON);
    if(menu_main_music_info.playstatus_usbtf == 1 || menu_main_music_info.playstatus_bt == 2){
        sVFD1602_GRAM_IconSet(ICON_PLAY,ICON_EN_ON);
    }else{
        sVFD1602_GRAM_IconSet(ICON_PLAY,ICON_EN_OFF);
    }
    //暂停模式
    if(menu_main_music_info.playstatus_usbtf == 2 || menu_main_music_info.playstatus_bt == 1){
        sVFD1602_GRAM_IconSet(ICON_STOP,ICON_EN_ON);
    }else{
        sVFD1602_GRAM_IconSet(ICON_STOP,ICON_EN_OFF);
    }
    //清空标志位
    menu_main_music_info.playstatus_bt = 0;
    menu_main_music_info.playstatus_usbtf = 0;

    //sVFD1602_CGRAM_WriteNumber(10,0,menu_main_music_info.alltime %);

}


//获取已播放时间
void sigAppMENU_SetPlayedTime(uint16_t _playedtime){
    menu_main_music_info.playedtime = _playedtime;
}
void sigAppMENU_SetPlayAllTime(uint16_t _playalltime){
    menu_main_music_info.alltime = _playalltime;
}
//获取工作模式
void sigAppMENU_SetWorkMode(uint8_t _workmode){
    menu_main_music_info.playmode = _workmode;
}
//获取当前TF/USB是播放还是暂停
void sigAppMENU_SetUsbTfCurrStatus(uint8_t _currstatus){
    menu_main_music_info.playstatus_usbtf = _currstatus;
}

//获取当前蓝牙是播放还是暂停
void sigAppMENU_SetBtCurrStatus(uint8_t _currstatus){
    menu_main_music_info.playstatus_bt = _currstatus;
}
//获取插入拔出的信息
void sigAppMENU_SetInOutInfo(uint8_t _info){
    InstantEventFlag = (InstantEventFlag_t)_info;
}
//改变音量
void sigAppMENU_SetVolume(uint8_t _volume){

    menu_main_music_info.volume = _volume;
    InstantEventFlag = InstantEventFlag_ChangeVol;
}
//改变亮度
void sigAppMENU_SetBrightness(uint8_t _brightness){

    menu_main_music_info.brightness = _brightness;
    InstantEventFlag = InstantEventFlag_ChangeBrightness;
}

//up:1,down 0
void sigAppMENU_UpdownVolume(uint8_t updown){
    //up
    if(updown){
        menu_main_music_info.volume >= 30?menu_main_music_info.volume = 30:menu_main_music_info.volume++;
    }else{
        menu_main_music_info.volume <= 0?menu_main_music_info.volume = 0:menu_main_music_info.volume--;
    }
    sigAppMENU_SetVolume(menu_main_music_info.volume);
    sBT401_TransComm_SetVolume(menu_main_music_info.volume);
}

void sigAppMENU_UpdownBrightness(uint8_t updown){
    //up
    if(updown){
        menu_main_music_info.brightness >= 100?menu_main_music_info.brightness = 100:menu_main_music_info.brightness+=10;
    }else{
        menu_main_music_info.brightness <= 10?menu_main_music_info.brightness = 10:menu_main_music_info.brightness-=10;
    }
    sigAppMENU_SetBrightness(menu_main_music_info.brightness);
    sVFD1602_BrightnessSet(menu_main_music_info.brightness);
}

void sigAppMENU_Init(){

}

uint8_t sigAppMENU_InstantEventHandler(){
    static uint32_t instant_event_begin_s, instant_event_end_s;
    
    //有即时事件来了
    if(InstantEventFlag != InstantEventFlag_Null){
        sVFD1602_CGRAM_Clear();
        instant_event_begin_s = millis();
        instant_event_end_s = instant_event_begin_s + 1000;
    }
    
    
    //处理事件TF卡插入
    if(InstantEventFlag == InstantEventFlag_TFcardIn){
        sVFD1602_CGRAM_WriteString(0,0,(char*)"Detect TFcard",0);
        sVFD1602_CGRAM_WriteString(8,1,(char*)"INSERTED",0);
    }
    //处理事件TF卡拔出
    else if(InstantEventFlag == InstantEventFlag_TFcardOut){
        sVFD1602_CGRAM_WriteString(0,0,(char*)"Detect TFcard",0);
        sVFD1602_CGRAM_WriteString(9,1,(char*)"REMOVED",0);
    }
    //处理事件U盘插入
    if(InstantEventFlag == InstantEventFlag_USBIn){
        sVFD1602_CGRAM_WriteString(0,0,(char*)"Detect  Udisk",0);
        sVFD1602_CGRAM_WriteString(8,1,(char*)"INSERTED",0);

    }
    //处理事件U盘拔出
    else if(InstantEventFlag == InstantEventFlag_USBOut){
        sVFD1602_CGRAM_WriteString(0,0,(char*)"Detect  Udisk",0);
        sVFD1602_CGRAM_WriteString(9,1,(char*)"REMOVED",0);
    }
    if(InstantEventFlag == InstantEventFlag_ChangeVol){
        sVFD1602_CGRAM_WriteString(0,0,(char*)"Volume:",0);
        sVFD1602_CGRAM_WriteNumber(12,1,menu_main_music_info.volume);
        sVFD1602_CGRAM_WriteString(15,1,(char*)"%",0);
    }
    if(InstantEventFlag == InstantEventFlag_ChangeBrightness){
        sVFD1602_CGRAM_WriteString(0,0,(char*)"Brightness:",0);
        sVFD1602_CGRAM_WriteNumber(12,1,menu_main_music_info.brightness);
        sVFD1602_CGRAM_WriteString(15,1,(char*)"%",0);
    }
    
    if(InstantEventFlag != InstantEventFlag_Null){
        //上传屏幕
        sVFD1602_UpdateScreenByCGRAM();
    }
    InstantEventFlag = InstantEventFlag_Null;
    

    
    //显示1000ms
    if(millis() <= instant_event_end_s){
        return 1;
    }else{
        return 0;
    }

}

void sigAppMENU_Handler(){
    if(sigAppMENU_InstantEventHandler() == 0){
        //清空缓冲区
        //sVFD1602_CGRAM_Clear();
        MenuShow_MainMusic();
        //上传屏幕
        sVFD1602_UpdateScreenByCGRAM();
        //清空缓冲区
        sVFD1602_CGRAM_Clear();
    }
    vTaskDelay(20 / portTICK_PERIOD_MS);
    
}


void sigAppMENU(uint8_t page){
    //sVFD1602_ClearDisplay();
    sVFD1602_CGRAM_Clear();
    // switch (page)
    // {
    // case 1:
    //     sVFD1602_CGRAM_WriteString(0,0,(char*)"PAGE 1");
    //     sVFD1602_CGRAM_WriteString(0,1,(char*)"main menu music");
    //     break;
    // case 2:
    //     sVFD1602_CGRAM_WriteString(0,0,(char*)"PAGE 2");
    //     sVFD1602_CGRAM_WriteString(0,1,(char*)"settings 1");
    //     break;
    // case 3:
    //     sVFD1602_CGRAM_WriteString(0,0,(char*)"PAGE 3");
    //     sVFD1602_CGRAM_WriteString(0,1,(char*)"settings 2");
    //     break;
    // case 4:
    //     sVFD1602_CGRAM_WriteString(0,0,(char*)"PAGE 4");
    //     sVFD1602_CGRAM_WriteString(0,1,(char*)"mode switch");
    //     break;
    // case 5:
    //     sVFD1602_CGRAM_WriteString(0,0,(char*)"PAGE 5");
    //     sVFD1602_CGRAM_WriteString(0,1,(char*)"infomation");
    //     break;
    // default:
    //     break;
    // }

    sVFD1602_UpdateScreenByCGRAM();
}
