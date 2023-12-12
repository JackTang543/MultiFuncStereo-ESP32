#include "sig_Font.h"

const sCGRAM_Char_t SymbolFont[] = {
    //0
    {0x7F,
     0x41,
     0x41,
     0x41,
     0x7F},
    //1
    {0x00,
     0x02,
     0xFF,
     0x00,
     0x00},
    //2
    {0x79,
     0x49,
     0x49,
     0x49,
     0x4F},
    //3
    {0x49,
     0x49,
     0x49,
     0x49,
     0x7F},
    //4
    {0x0F,
     0x08,
     0x08,
     0x08,
     0x7F},
    //5
    {0x4F,
     0x49,
     0x49,
     0x49,
     0x79},
    //6
    {0x7F,
     0x49,
     0x49,
     0x49,
     0x79},
    //7
    {0x01,
     0x01,
     0x01,
     0x01,
     0x7F},
    //8
    {0x7F,
     0x49,
     0x49,
     0x49,
     0x7F},
    //9
    {0x4F,
     0x49,
     0x49,
     0x49,
     0x7F},
    //:(10)
    {0x00,
     0x00,
     0x36,
     0x00,
     0x00},
    //.(11)
    {0x00,
     0x40,
     0x00,
     0x00,
     0x00},
    //'(12)
    {0x00,
     0x07,
     0x00,
     0x00,
     0x00},
    //-(13)
    {0x08,
     0x08,
     0x08,
     0x08,
     0x08}
};

const IRAM_ATTR sCGRAM_Char_t CharFont[] = {
        //0 null
        {0x00,
         0x00,
         0x00,
         0x00,
         0x00},
        //1 SOH
        {0x00,
         0x00,
         0x00,
         0x00,
         0x00},
         //2 STX
        {0x00,
         0x00,
         0x00,
         0x00,
         0x00},
         //3 ETX
        {0x00,
         0x00,
         0x00,
         0x00,
         0x00},
         //4 EOT
        {0x00,
         0x00,
         0x00,
         0x00,
         0x00},
         //5 ENQ
        {0x00,
         0x00,
         0x00,
         0x00,
         0x00},
         //6 ACK
        {0x00,
         0x00,
         0x00,
         0x00,
         0x00},
         //7 BEL
        {0x00,
         0x00,
         0x00,
         0x00,
         0x00},
         //8 BS
        {0x00,
         0x00,
         0x00,
         0x00,
         0x00},
         //9 HT
        {0x00,
         0x00,
         0x00,
         0x00,
         0x00},
         //10 LF
        {0x00,
         0x00,
         0x00,
         0x00,
         0x00},
         //11 VT
        {0x00,
         0x00,
         0x00,
         0x00,
         0x00},
         //12 FF
        {0x00,
         0x00,
         0x00,
         0x00,
         0x00},
         //13 CR
        {0x00,
         0x00,
         0x00,
         0x00,
         0x00},
         //14 SO
        {0x00,
         0x00,
         0x00,
         0x00,
         0x00},
         //15 SI
        {0x00,
         0x00,
         0x00,
         0x00,
         0x00},
         //16 DLE
        {0x00,
         0x00,
         0x00,
         0x00,
         0x00},
         //17 DC1
        {0x00,
         0x00,
         0x00,
         0x00,
         0x00},
         //18 DC2
        {0x00,
         0x00,
         0x00,
         0x00,
         0x00},
         //19 DC3
        {0x00,
         0x00,
         0x00,
         0x00,
         0x00},
         //20 DC4
        {0x00,
         0x00,
         0x00,
         0x00,
         0x00},
         //21 NAK
         {0x00,
         0x00,
         0x00,
         0x00,
         0x00},
         //22 SYN
         { 0x00,
         0x00,
         0x00,
         0x00,
         0x00 },
         //23 ETB
         { 0x00,
         0x00,
         0x00,
         0x00,
         0x00 },
         //24 CAN
         { 0x00,
         0x00,
         0x00,
         0x00,
         0x00 },
         //25 EM
         { 0x00,
         0x00,
         0x00,
         0x00,
         0x00 },
         //26 SUB
         { 0x00,
         0x00,
         0x00,
         0x00,
         0x00 },
         //27 ESC
         { 0x00,
         0x00,
         0x00,
         0x00,
         0x00 },
         //28 FS
         { 0x00,
         0x00,
         0x00,
         0x00,
         0x00 },
         //29 GS
         { 0x00,
         0x00,
         0x00,
         0x00,
         0x00 },
         //30 RS
         { 0x00,
         0x00,
         0x00,
         0x00,
         0x00 },
         //31 US
         { 0x00,
         0x00,
         0x00,
         0x00,
         0x00 },
         //32 SPACE
         { 0x00,
             0x00,
             0x00,
             0x00,
             0x00 },
             //33 !
         { 0x00,
             0x00,
             0x00,
             0x00,
             0x00 },
             //34 "
         { 0x00,
         0x00,
         0x00,
         0x00,
         0x00 },
         //35 #
         { 0x00,
         0x00,
         0x00,
         0x00,
         0x00 },
         //36 $
         { 0x00,
         0x00,
         0x00,
         0x00,
         0x00 },
         //37 %
         { 0x00,
         0x00,
         0x00,
         0x00,
         0x00 },
         //38 &
         { 0x00,
         0x00,
         0x00,
         0x00,
         0x00 },
         //39 '
         {0x00,
          0x00,
          0x00,
          0x00,
          0x00},
         //40 (
         { 0x00,
         0x00,
         0x00,
         0x00,
         0x00 },
         //41 )
         { 0x00,
         0x00,
         0x00,
         0x00,
         0x00 },
         //42 *
         { 0x00,
         0x00,
         0x00,
         0x00,
         0x00 },
         // 43 +
         { 0x08,
          0x08,
          0x3E,
          0x08,
          0x08 },
          //44 ,
         { 0x00,
          0x50,
          0x30,
          0x00,
          0x00 },
          //45 -
         { 0X08,
          0X08,
          0X08,
          0X08,
          0X08 },
          //46 .
         { 0x00,
          0x60,
          0x60,
          0x00,
          0x00 },
          //47 /
         { 0x20,
         0x10,
         0x08,
         0x04,
         0x02 },
         //48 0
         { 0x3E,
         0X51,
         0X49,
         0X45,
         0X3E },
         //49 1
         { 0X00,
         0X42,
         0X7F,
         0X40,
         0X00},
         //50 2
         {0X42,
         0X61,
         0X51,
         0X49,
         0X46},
         //51 3
         {0X21,
         0X41,
         0X45,
         0X4B,
         0X31},
         // 52 4
         {0X18,
         0X14,
         0X12,
         0X7F,
         0X10},
         //53 5
         {0X27,
         0X45,
         0X45,
         0X45,
         0X39},
         //54 6
         {0X3C,
         0X4A,
         0X49,
         0X49,
         0X30},
         //55 7
         {0X01,
         0X71,
         0X09,
         0X05,
         0X03},
         //56 8
         {0X36,
          0X49,
          0X49,
          0X49,
          0X36},
          //57 9
          {0X06,
          0X49,
          0X49,
          0X29,
          0X1E},
          //58 :
          { 0x00,
          0x00,
          0x00,
          0x00,
          0x00 },
          //59 ;
          { 0x00,
          0x00,
          0x00,
          0x00,
          0x00 },
          //60 <
          {0x00,
           0x00,
           0x00,
           0x00,
           0x00},
           //61  =
           {0X14,
           0X14,
           0X14,
           0X14,
           0X14},
           //62 >
           { 0x00,
          0x00,
          0x00,
          0x00,
          0x00 },
          //63 ?
          { 0x00,
          0x00,
          0x00,
          0x00,
          0x00 },
          //64 @
          { 0x00,
          0x00,
          0x00,
          0x00,
          0x00 },
          //65 A
          {0X7E,
          0X11,
          0X11,
          0X11,
          0X7E},
          //66 B
          {0X7F,
          0X49,
          0X49,
          0X49,
          0X36},
          //67 C
          {0X3E,
          0X41,
          0X41,
          0X41,
          0X22},
          //68 D
          {0X7F,
          0X41,
          0X41,
          0X22,
          0X1C},
          //69 E
          {0X7F,
          0X49,
          0X49,
          0X49,
          0X41},
          //70 F
          {0X7F,
          0X09,
          0X09,
          0X01,
          0X01},
          //71 G
          {0X3E,
          0X41,
          0X41,
          0X51,
          0X32},
          //72 H
          {0X7F,
          0X08,
          0X08,
          0X08,
          0X7F},
          //73 I
          { 0X00,
           0X41,
           0X7F,
           0X41,
          0X00},
          //74 J
          {0X20,
          0X40,
          0X41,
          0X3F,
          0X01},
          //75 K
          {0X7F,
          0X08,
          0X14,
          0X22,
          0X41},
          //76 L
          {0X7F,
          0X40,
          0X40,
          0X40,
          0X40},
          //77M
          { 0X7F,
          0X02,
          0X04,
          0X02,
          0X7F},
          //78 N
          {0X7F,
          0X04,
          0X08,
          0X10,
          0X7F},
          //79 O
          { 0X3E,
           0X41,
           0X41,
           0X41,
           0X3E},
           //80 P
           {0X7F,
           0X09,
           0X09,
           0X09,
           0X06},
           //81 Q
           {0X3E,
           0X41,
           0X51,
           0X21,
           0X5E},
           //82 R
           {0X7F,
           0X09,
           0X19,
           0X29,
           0X46},
           //83 S
           {0X46,
           0X49,
           0X49,
           0X49,
           0X31},
           //84 T
           {0X01,
           0X01,
           0X7F,
           0X01,
           0X01},
           //85 U
           { 0X3F,
           0X40,
           0X40,
           0X40,
           0X3F},
           //86 V
           {0X1F,
           0X20,
           0X40,
           0X20,
           0X1F},
           //87 W
           { 0X7F,
           0X20,
           0X18,
           0X20,
           0X7F},
           //88 X
           {0X63,
           0X14,
           0X08,
           0X14,
           0X63},
           //89 Y
           {0X03,
           0X04,
           0X78,
           0X04,
           0X03},
           //90 Z
           {0X61,
            0X51,
            0X49,
            0X45,
            0X43 },
            //91 [
            {0x00,
             0x00,
             0x00,
             0x00,
             0x00},
             //92   "\"
            {0x00,
            0x00,
            0x00,
            0x00,
            0x00},
            //93 ]
            { 0x00,
             0x00,
             0x00,
             0x00,
             0x00 },
             //94 ^
             {0x00,
             0x00,
             0x00,
             0x00,
             0x00},
             //95 _
             { 0x00,
             0x00,
             0x00,
             0x00,
             0x00 },
             //96 `
             { 0x00,
             0x00,
             0x00,
             0x00,
             0x00 },
             //97 a
             {0X20,
             0X54,
             0X54,
             0X54,
             0X78},
             //98 b
             {0X7F,
             0X48,
             0X44,
             0X44,
             0X38},
             //99 C
             {0X38,
             0X44,
             0X44,
             0X44,
             0X20},
             //100 d
             {0X38,
             0X44,
             0X44,
             0X48,
             0X7F},
             //101 e
             {0X38,
             0X54,
             0X54,
             0X54,
             0X18},
             //102 f
             {0X08,
             0X7E,
             0X09,
             0X01,
             0X02},
             //103 g
             {0X08,
             0X14,
             0X54,
             0X54,
             0X3C},
             //104 h
             {0x7F,
             0X08,
             0X04,
             0X04,
             0X78},
             //105 i
             {0X00,
             0X44,
             0X7D,
             0X40,
             0X00},
             //106 j
             {0x20,
             0x40,
             0x44,
             0x3D,
             0x00},
             //107 k
             {0X00,
             0X7F,
             0X10,
             0X28,
             0X44},
             //108 l 
             {0X00,
             0X41,
             0X7F,
             0X40,
             0X00},
             //109 m
             {0X7C,
             0X04,
             0X18,
             0X04,
             0X78},
             //110 n
             {0X7C,
             0X08,
             0X04,
             0X04,
             0X78 },
             //111 o
            {0X38,
            0X44,
            0X44,
            0X44,
            0X38 },
            //112 p
            {0X7C,
            0X14,
            0X14,
            0X14,
            0X08},
            //113 q
            {0X08,
            0X14,
            0X14,
            0X18,
            0X7C},
            //114 r
            {0X7C,
            0X08,
            0X04,
            0X04,
            0X08},
            //115 s
            {0X48,
            0X54,
            0X54,
            0X54,
            0X20},
            //116 t
            {0X04,
            0X3F,
            0X44,
            0X40,
            0X20},
            //117 u
            {0X3C,
             0X40,
             0X40,
             0X20,
             0X7C},
            //118 v
            {0X1C,
             0X20,
             0X40,
             0X20,
             0X1C},
             //119 w
            {0X3C,
             0X40,
             0X3C,
             0X40,
             0X3C},
             //120 x
            {0X44,
             0X28,
             0X10,
             0X28,
             0X44},
             //121 y
            {0X00,
             0X0C,
             0X50,
             0X50,
             0X3C},
             //122 z
            {0X44,
             0X64,
             0X54,
             0X4C,
             0X44},
             //123 {
             {0x00,
              0x00,
              0x00,
              0x00,
              0x00},
              //124 |
              {0x00,
               0x00,
               0x00,
               0x00,
               0x00},
               //125 }
              {0x00,
               0x00,
               0x00,
               0x00,
               0x00},
               //126 ~
              {0x00,
               0x00,
               0x00,
               0x00,
               0x00},
               //127 DEL
               {0x00,
               0x00,
               0x00,
               0x00,
               0x00}
};
