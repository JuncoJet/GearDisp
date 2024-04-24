#include "TCanbus.h"
#include "TLeds.h"
TCanbus can;
TLeds leds;
unsigned long b,c,kd;
byte i=0,kc=0,disp=0;
bool bl=false,kb;
void test(){
    bl=!bl;
    digitalWrite(K9,bl);
    if(bl){
      b=c+200;
    }else{
      leds.show(i);
      if(++i>9)i=0;
      b=c+800;
    }
}
void start_ani(){
  for(byte i=3;i>0;i--){
    leds.show(i);
    delay(500);
  }
  leds.show(0);
  digitalWrite(K9,HIGH);
  delay(1000);
}
void setup(){
  Serial.begin(115200);
  pinMode(K1,OUTPUT);
  pinMode(K2,OUTPUT);
  pinMode(K3,OUTPUT);
  pinMode(K4,OUTPUT);
  pinMode(K5,OUTPUT);
  pinMode(K6,OUTPUT);
  pinMode(K7,OUTPUT);
  pinMode(K8,OUTPUT);
  pinMode(K9,OUTPUT);
  pinMode(BOOT,INPUT);
  b=millis();
  start_ani();
  can.init();
  //can.dbgon=true;
  leds.clear();
  Serial.println("init done");
}
void getKey(){
  byte k=digitalRead(BOOT);
  if(kd){
    if(c>kd){
      if(k){//kdown
        if(++kc>10){//长按2秒
          Serial.println("lngClick");
          can.clrErrs();
          kb=1;
          kc=kd=0;
          return;
        }
      }else{//kup 单击
        if(!kb){
          Serial.println("Click");
          disp=!disp;
        }
        kb=kc=kd=0;
        return;
      }
      kd=c+200;
    }
  }else if(k){
    kd=c+200;//200ms去抖动
  }
}
void loop(){
  c=millis();
  getKey();
  if(c>b){
    //test();
    can.getRpm();
    //can.getSpeed();
    if(!disp){
      byte g=can.gear;
      if(!g)g=17;
      else if(g>6)g=10;
      leds.show(g);
    }
    b=c+333;
  }
  can.response();
  digitalWrite(K9,can.rpm>7200);//转速提示
  if(disp)leds.vshow(can.oiltmp);
}
