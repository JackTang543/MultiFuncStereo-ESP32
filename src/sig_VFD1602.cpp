#include "sig_VFD1602.h"


/* sigVFD1602.c
*  这个模块用来驱动EEI的VFD1602(EPC-INBM32V1607UD),注意这是UART通信版本
*  测试平台:FreeRTOS STM32F103VE HAL库
*  用户可以通过写显存,更新显存到屏幕的方式使用
*  
*  By Sightseer. 2023.11.03于HNIP-9607Lab    v1.0
*/

//显存
uint8_t GRAM[16][2];
//亮度百分比
uint8_t BrightnessPercent;

//用于保存屏幕显示小图标的地址坐标,这里的顺序对发送进行了优化
sVFD1602_ICON_Table_t ICON_TABLE[] = {
    {ICON_TONE  ,ICON_EN_OFF,0x00,0x01},{ICON_SDB  ,ICON_EN_OFF,0x00,0x02},{ICON_STOP ,ICON_EN_OFF,0x00,0x04},
    {ICON_ST    ,ICON_EN_OFF,0x01,0x01},{ICON_AUTO ,ICON_EN_OFF,0x01,0x02},{ICON_TUNED,ICON_EN_OFF,0x01,0x04},
    {ICON_RANDOM,ICON_EN_OFF,0x02,0x01},{ICON_TOTAL,ICON_EN_OFF,0x02,0x02},{ICON_MONO ,ICON_EN_OFF,0x02,0x04},
    {ICON_ALL   ,ICON_EN_OFF,0x03,0x01},{ICON_FLD  ,ICON_EN_OFF,0x03,0x02},{ICON_1    ,ICON_EN_OFF,0x03,0x04},
    {ICON_POINT ,ICON_EN_OFF,0x04,0x01},{ICON_CLOCK,ICON_EN_OFF,0x04,0x02},{ICON_SLEEP,ICON_EN_OFF,0x04,0x04},
    {ICON_PLAY  ,ICON_EN_OFF,0x00,0x08},{ICON_CYCLE,ICON_EN_OFF,0x03,0x08}
};


/*@brief  本模块自定义的延时函数,这里可以由用户自行设置
*         本模块全部调用这个延时函数
*           
* @param  无
*
* @return 无
*/
 void sDelayFunc(){
    //延时1ms
    //delay(1);
    vTaskDelay(1 / portTICK_PERIOD_MS);
}

/*@brief  发送一个字节的函数,发送方式可以由用户自定义
*           
* @param  uint8_t byte:要发送的字节
*
* @return 无
*/
void sVFD1602_SendByte(uint8_t byte){
    Serial.printf("%c",byte);
}

/*@brief  发送清屏指令
*           
* @param  无
*
* @return 无
*/
void sVFD1602_ClearDisplay(){
    sVFD1602_SendByte(DISPCLR);
    //给屏幕一点时间
    sDelayFunc();
}

/*@brief  发送电源设置指令
*           
* @param  sVFD1602_PWR_t en: PWR_OFF关闭电源 PWR_ON开启电源
*
* @return 无
*/
void sVFD1602_PowerSet(sVFD1602_PWR_t en){
    //显示屏电源设置
    sVFD1602_SendByte(PWRCTR);
    if(en == PWR_ON){
        sVFD1602_SendByte(0x01);
    }else{
        sVFD1602_SendByte(0x00);
    }
    //给屏幕一点时间
    sDelayFunc();
}

/*@brief  直接发送亮度设置指令
*           
* @param  uint8_t bright_percent:要设置亮度的百分比
*
* @return 无
*/
void sVFD1602_BrightnessSet(uint8_t bright_percent){
    BrightnessPercent = bright_percent;
    //发送设置亮度指令
    sVFD1602_SendByte(DIMMCTR);
    //设置亮度,这里把百分比映射到0~255
    sVFD1602_SendByte((uint8_t)((float)bright_percent * 2.55f));
    //给屏幕一点时间
    sDelayFunc();
}

//*************************************下面是用户的写GRAM的函数********************************

/*@brief  GRAM亮度设置
*           
* @param  uint8_t bright_percent:要设置亮度的百分比
*
* @return 无
*/
void sVFD1602_GRAM_BrightnessSet(uint8_t bright_percent){
    BrightnessPercent = bright_percent;
}

/*@brief  设置一个图标的亮灭
*           
* @param  sVFD1602_Icon_t icon : 要设置的图标名
* @param  sVFD1602_Icon_EN_t en : 亮(ICON_EN_ON)还是灭(ICON_EN_OFF)呢
*
* @return 无
*/
void sVFD1602_GRAM_IconSet(sVFD1602_Icon_t icon,sVFD1602_Icon_EN_t en){
    //遍历小图标地址坐标表,设置它
    for(uint8_t i = 0;i < 17;i++){
        if(ICON_TABLE[i].icon == icon){
            ICON_TABLE[i].en = en;
        }
    }
}

/*@brief  往GRAM写一个字节
*           
* @param  uint8_t x:字节的x坐标
* @param  uint8_t y:字节的y坐标
* @param  uint8_t byte:要写的字节
*
* @return 无
*/
inline void sVFD1602_GRAM_Write(uint8_t x,uint8_t y,uint8_t byte){
    GRAM[x][y] = byte;
}

/*@brief  往GRAM写字符串
*           
* @param  uint8_t x:字符串起始x坐标
* @param  uint8_t y:字符串起始y坐标
* @param  char* str:字符串
*
* @return 无
*/
void sVFD1602_GRAM_WriteString(uint8_t x,uint8_t y,char* str){
    //遍历字符串
    while(*str != '\0'){
        if(x != 16){
            GRAM[x][y] = *str;
            x++;
            str++; 
        }else{
            //已经达到所能显示的最大范围了
            return;
        }
    }
}

/*@brief  清空显存
*           
* @param  无
*
* @return 无
*/
void sVFD1602_GRAM_Clear(){
     //遍历显存
    for(uint8_t y = 0;y < 2;y++){
        for(uint8_t x = 0;x < 16;x++){
            GRAM[x][y] = 0x00;
        }
    }
}

//*************************************写GRAM的函数结束********************************

/*@brief  设置某行的光标使能和是否闪烁(功能不完全)
*           
* @param  uint8_t blink:1:使能并且闪烁,0:不使能也不闪烁
*
* @return 无
*/
void sVFD1602_CursorENandBlinkSet(uint8_t blink){
    sVFD1602_SendByte(CURCFG);
    if(!!blink == 1){
        sVFD1602_SendByte(0x0F);
    }else{
        sVFD1602_SendByte(0x00);
    }
    sDelayFunc();
}

/*@brief  设置光标位置
*           
* @param  uint8_t x:光标x坐标
* @param  uint8_t y:光标y坐标
*
* @return 无
*/
void sVFD1602_CursorSet(uint8_t x,uint8_t y){
    sVFD1602_SendByte(CURPOS);
    sVFD1602_SendByte(y);
    sVFD1602_SendByte(x);
    sDelayFunc();
}

//CGRAM缓存,16个自定义字符,字有2排,一个字有5个byte
//x,y,byte
uint8_t CGRAM_Buffer[16][2][5];

//清空CGRAM
void sVFD1602_CGRAM_Clear(){
    for(uint8_t i = 0;i < 2;i++){
        for(uint8_t j = 0;j < 5;j++){
            for(uint8_t k = 0;k < 16;k++){
                CGRAM_Buffer[k][i][j] = 0x00;
            }
        }
    }
}

void sVFD1602_CGRAM_WriteNumber(uint8_t x,uint8_t y,uint16_t num){
    uint8_t length = (num == 0)? 1 : (uint8_t)(log10(num) + 1);
    
    for(uint8_t i = length;i > 0;i--){
        sVFD1602_CGRAM_WriteUserChar(x + i - 1,y,SymbolFont[num / (uint16_t)powf(10 , length - i) % 10]);
    }
}


//把用户自定义字符写到CGRAM
void sVFD1602_CGRAM_WriteUserChar(uint8_t x,uint8_t y,sCGRAM_Char_t user_char){
    CGRAM_Buffer[x][y][0] = user_char.CharByte0;
    CGRAM_Buffer[x][y][1] = user_char.CharByte1;
    CGRAM_Buffer[x][y][2] = user_char.CharByte2;
    CGRAM_Buffer[x][y][3] = user_char.CharByte3;
    CGRAM_Buffer[x][y][4] = user_char.CharByte4;
}

void sVFD1602_WriteICON(){
    //写小图标
    //table_offset对应的是data_A
    for(uint8_t table_offset = 0;table_offset < 5;table_offset++){
        //判断当前遍历的三个图标只要有一个是被使能的就要写,否则跳过这轮遍历
        if(ICON_TABLE[(table_offset * 3) + 0].en == ICON_EN_ON || ICON_TABLE[(table_offset * 3) + 1].en == ICON_EN_ON || \
           ICON_TABLE[(table_offset * 3) + 2].en == ICON_EN_ON){
            //有需要写的,开写
            sVFD1602_SendByte(ADRAMWR);
            sVFD1602_SendByte(table_offset);
        }else{
            //没有,跳过本轮
            continue;
        }
        //当然,这里的遍历只有当有需要写的时候才会启动,不然就被continue了
        for(uint8_t i = 0;i < 3;i++){
            if(ICON_TABLE[(table_offset * 3) + i].en == ICON_EN_ON){
                sVFD1602_SendByte(ICON_TABLE[(table_offset * 3) + i].Data_D);
            }
        }
        sDelayFunc();
    }
    sDelayFunc();
    //处理剩下的两个图标
    if(ICON_TABLE[15].en == ICON_EN_ON){
        sVFD1602_SendByte(ADRAMWR);
        sVFD1602_SendByte(ICON_TABLE[15].Data_A);
        sVFD1602_SendByte(ICON_TABLE[15].Data_D);
        sDelayFunc();
    }
    if(ICON_TABLE[16].en == ICON_EN_ON){
        sVFD1602_SendByte(ADRAMWR);
        sVFD1602_SendByte(ICON_TABLE[16].Data_A);
        sVFD1602_SendByte(ICON_TABLE[16].Data_D);
        sDelayFunc();
    }
}


void sVFD1602_CGRAM_WriteString(uint8_t x,uint8_t y,char* str,uint8_t reverse){
    //遍历字符串
    while(*str != '\0'){
        if(x != 16){
            if(reverse){
                CGRAM_Buffer[x][y][0] = ~(CharFont[*str].CharByte0);
                CGRAM_Buffer[x][y][1] = ~(CharFont[*str].CharByte1);
                CGRAM_Buffer[x][y][2] = ~(CharFont[*str].CharByte2);
                CGRAM_Buffer[x][y][3] = ~(CharFont[*str].CharByte3);
                CGRAM_Buffer[x][y][4] = ~(CharFont[*str].CharByte4);
            }else{
                CGRAM_Buffer[x][y][0] = CharFont[*str].CharByte0;
                CGRAM_Buffer[x][y][1] = CharFont[*str].CharByte1;
                CGRAM_Buffer[x][y][2] = CharFont[*str].CharByte2;
                CGRAM_Buffer[x][y][3] = CharFont[*str].CharByte3;
                CGRAM_Buffer[x][y][4] = CharFont[*str].CharByte4;
            }
            
            x++;
            str++; 
        }else{
            //已经达到所能显示的最大范围了
            return;
        }
    }
}

void sVFD1602_CGRAM_WriteChar(uint8_t x,uint8_t y,char c){
    CGRAM_Buffer[x][y][0] = (CharFont[c].CharByte0);
    CGRAM_Buffer[x][y][1] = (CharFont[c].CharByte1);
    CGRAM_Buffer[x][y][2] = (CharFont[c].CharByte2);
    CGRAM_Buffer[x][y][3] = (CharFont[c].CharByte3);
    CGRAM_Buffer[x][y][4] = (CharFont[c].CharByte4);
}

//上传CGRAM到屏幕
void sVFD1602_UpdateScreenByCGRAM(){
    //写亮度
    sVFD1602_BrightnessSet(BrightnessPercent);
    for(uint8_t y = 0;y < 2;y++){
        for(uint8_t x = 0;x < 16;x++){
            sVFD1602_SendByte(CGRAMWR);
            sVFD1602_SendByte(y);
            sVFD1602_SendByte(x);
            
            sVFD1602_SendByte(CGRAM_Buffer[x][y][0]);
            sVFD1602_SendByte(CGRAM_Buffer[x][y][1]);
            sVFD1602_SendByte(CGRAM_Buffer[x][y][2]);
            sVFD1602_SendByte(CGRAM_Buffer[x][y][3]);
            sVFD1602_SendByte(CGRAM_Buffer[x][y][4]);
            
            sDelayFunc();
        }
    }
   for(uint8_t i = 0;i < 1;i++){
        sVFD1602_SendByte(DCRAM0WR + i);
        sVFD1602_SendByte(0);
        for(uint8_t j = 0;j < 16;j++){
            sVFD1602_SendByte(j);
        }
        sDelayFunc();
    }
    sDelayFunc();
    sVFD1602_SendByte(DCRAM1WR + 0);
        sVFD1602_SendByte(0);
        for(uint8_t j = 0;j < 16;j++){
            sVFD1602_SendByte(j);
        }
        sDelayFunc();

    sVFD1602_WriteICON();
    sDelayFunc();

    
}


/*@brief  设置
*           
* @param  无
*
* @return 无
*/
void sVFD1602_GRAM_WriteCGRAM(){
    
}

/*@brief  VFD1602初始化
*           
* @param  无
*
* @return 无
*/
void sVFD1602_Init(){
    //遍历显存
    for(uint8_t y = 0;y < 2;y++){
        for(uint8_t x = 0;x < 16;x++){
            GRAM[x][y] = 0x00;
        }
    }
    //清空CGRAM
    sVFD1602_CGRAM_Clear();
    //电源打开
    sVFD1602_PowerSet(PWR_ON);
    //清屏
    sVFD1602_ClearDisplay();
}

/*@brief  用GRAM里的数据更新屏幕
*           
* @param  无
*
* @return 无
*/
void sVFD1602_UpdateScreenByGRAM(){
    //写亮度
    sVFD1602_BrightnessSet(BrightnessPercent);
    //写第一行
    sVFD1602_SendByte(DCRAM0WR);
    sVFD1602_SendByte(0);
    for(uint8_t i = 0;i < 16;i++){
        sVFD1602_SendByte(GRAM[i][0]);
    }
    sDelayFunc();
    //写第二行
    sVFD1602_SendByte(DCRAM1WR);
    sVFD1602_SendByte(0);
    for(uint8_t i = 0;i < 16;i++){
        sVFD1602_SendByte(GRAM[i][1]);
    }
    sDelayFunc();
    
    sVFD1602_WriteICON();
}


