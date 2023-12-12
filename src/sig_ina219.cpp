#include "sig_ina219.h"

Adafruit_INA219 ina219;

//压降
float shuntvoltage = 0;
//总线电压
float busvoltage = 0;
//电流
float current_mA = 0;
//负载电压
float loadvoltage = 0;
//功率
float power_mW = 0;


void sINA219_Init(){
    if(!ina219.begin()){
        Serial.println("INA219 ERROR: 01 ");
        return;
    }
    ina219.setCalibration_32V_2A();
}

float sINA219_GetRshunt_mV(){
    shuntvoltage = ina219.getShuntVoltage_mV();
    return shuntvoltage;
}
float sINA219_GetBatVolt_mV(){
    busvoltage = ina219.getBusVoltage_V();
    return busvoltage * 1000;
}
float sINA219_GetCurr_mA(){
    current_mA = ina219.getCurrent_mA();
    return current_mA;
}
float sINA219_GetPower_mW(){
    power_mW = ina219.getPower_mW();
    return power_mW;
}
float sINA219_GetLoadVolt_mV(){
    busvoltage = ina219.getBusVoltage_V();
    shuntvoltage = ina219.getShuntVoltage_mV();
    loadvoltage = busvoltage + (shuntvoltage / 1000);
    return loadvoltage * 1000;
}