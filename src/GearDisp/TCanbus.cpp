#include "TCanbus.h"
int TCanbus::canid=0x7df,TCanbus::filter=0x7e8,TCanbus::busspeed=500E3;
bool TCanbus::dbgon=false;
int TCanbus::rpm,TCanbus::speed,TCanbus::oiltmp,TCanbus::gear;
void TCanbus::init(){
  CAN.setClockFrequency(QUARTZ_MHZ * 1E6);
  CAN.setSPIFrequency(SPI_MHZ * 1E6);
  CAN.setPins(CS,IRQ);//不设置，使用默认端口
  //start the CAN bus at 500 kbps
  if(!CAN.begin(busspeed)){
    Serial.println("Starting CAN failed!");
    while(1);
  }
  //add filter to only receive the CAN bus ID's we care about
  //CAN.filter(filter);
  //CAN.onReceive(onReceive);//有BUG未修复，弃用
}
void TCanbus::init(int busspeed,int filter){
  this->busspeed=busspeed;
  if(filter)this->filter=filter;
  init();
}
void TCanbus::getRpm(){
  CAN.beginPacket(canid,8);
  CAN.write(0x2);
  CAN.write(0x1);
  CAN.write(0xC);
  CAN.endPacket();
}
byte TCanbus::getGear(){
  byte gear;
  if(rpm&&speed){
    gear=rpm/speed;
  }else{
    gear=17;
  }
  return gear;
}
void TCanbus::getSpeed(){
  CAN.beginPacket(canid,8);
  CAN.write(0x2);
  CAN.write(0x1);
  CAN.write(0xD);
  CAN.endPacket();
}
void TCanbus::clrErrs(){
  CAN.beginPacket(canid,8);
  CAN.write(0x1);
  CAN.write(0x4);
  CAN.endPacket();
}
void TCanbus::response(){
  //wait for response
  int packet_size = CAN.parsePacket();
  if (packet_size <= 0) {
    return;
  }
  if (CAN.packetRtr()) {
    // Ignore RTRs.
    return;
  }
  int pid=CAN.packetId();
  if(pid==filter){
    char buf[3];
    for(byte i=0;i<sizeof(buf);i++){
      buf[i]=CAN.read();
    }
    if(buf[1]==0x41){
      if(buf[2]==0xC){//RPM
        float r=((CAN.read()*256.0)+CAN.read())/4.0;
        if(dbgon){
          Serial.print("Engine RPM = ");
          Serial.println(r);
        }
        rpm=(int)r;
      }else if(buf[2]==0xD){//Speed
        speed=CAN.read();
        if(dbgon){
          Serial.print("Speed = ");
          Serial.println(speed);
        }
      }
    }
  }else if(pid==0x360){
    CAN.read();
    CAN.read();
    byte c=CAN.read();
    oiltmp=c-40;
  }else if(pid==0x361){
    gear=CAN.read()&0xF;
  }
}
void TCanbus::onReceive(int packetSize){
  int pid=CAN.packetId();
  if(pid==filter){
    char buf[3];
    for(byte i=0;i<sizeof(buf);i++){
      buf[i]=CAN.read();
    }
    if(buf[1]==0x41){
      if(buf[2]==0xC){//RPM
        float r=((CAN.read()*256.0)+CAN.read())/4.0;
        if(dbgon){
          Serial.print("Engine RPM = ");
          Serial.println(r);
        }
        rpm=(int)r;
      }else if(buf[2]==0xD){//Speed
        speed=CAN.read();
        if(dbgon){
          Serial.print("Speed = ");
          Serial.println(speed);
        }
      }
    }
    /*while(CAN.available()){
      Serial.print((char)CAN.read());
    }*/
  }else if(pid==0x360){
    CAN.read();
    CAN.read();
    byte c=CAN.read();
    oiltmp=c-40;
  }else if(pid==0x361){
    gear=CAN.read()&0x7;
  }
}
