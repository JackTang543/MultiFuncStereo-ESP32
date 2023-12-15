
#include "sig_tp5100.h"

SIG_TP5100_STATUS_t sTP5100_GetStatus(){
    if(!digitalRead(TP5100ChrgPIN)){
        return SIG_TP5100_CHRG;
    }
    else if(!digitalRead(TP5100StdbyPIN)){
        return SIG_TP5100_STDBY;
    }
}
