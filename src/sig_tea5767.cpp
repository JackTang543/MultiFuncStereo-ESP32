#include "sig_tea5767.h"

//sig_tea5767.cpp
//此文件用于驱动TEA5767
//By SIGHTSEER. 2023.12.12


/*@brief  TEA5767的初始化函数
*         
* @param  无
*
* @return 无
*/
void sTEA5767_Init(){
    tea.init();
    //默认设置
    tea.setBandFrequency(SIG_TEA5767_WORLD_BAND,fm_freq);
    //默认音量:1
    tea.setVolume(1);
    //立体声接收模式
    tea.setMono(false);
}
/*@brief  TEA5767调频
*         
* @param  uint16_t freq:传入9170,即用91.7的频率接收
*
* @return 无
*/
void sTEA5767_SetFreq(uint16_t freq){
    tea.setFrequency(freq);
}
/*@brief  TEA5767获取调频信息
*         
* @param  无
*
* @return 无
*/
void getInfo(){
    tea.getRadioInfo(&tea_info);
}
/*@brief  TEA5767获取RSSI信息
*         
* @param  无
*
* @return RSSI
*/
uint8_t sTEA5767_GetRSSI(){
    getInfo();
    return tea_info.rssi;
}
/*@brief  TEA5767获取SNR信息
*         
* @param  无
*
* @return SNR
*/
uint8_t sTEA5767_GetSNR(){
    getInfo();
    return tea_info.snr;
}
/*@brief  TEA5767获取调频频率信息
*         
* @param  无
*
* @return 频率:eg:9170:91.70MHz
*/
uint16_t sTEA5767_GetFreq(){
    return fm_freq;
}
