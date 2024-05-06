#include "TLeds.h"
extern unsigned long c;
char TLeds::segs[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71,0x40,0},
  TLeds::ios[]={K1,K2,K3,K4,K5,K6,K7,K8,K9};
TLeds::TLeds(){
  clear();
}
void TLeds::show(byte v){
  if(v==cv)return;
  char c=segs[v];
  for(byte i=0;i<8;i++){
    digitalWrite(ios[i],c>>i&1);
  }
  cv=v;
}
void TLeds::vshow(int v){
  if(c>b){
    sprintf(buf,"%d",v);
    bool bl=(buf[1+cur]=='\0');
    byte o=buf[cur]-'0';
    digitalWrite(K8,bl);
    //digitalWrite(K9,bl);
    bar(bl);
    show(o);
    if(bl)cur=0;
    else cur++;
    b=c+500;
  }
}
void TLeds::bar(byte on){
  if(on==cb)return;
  digitalWrite(K9,on);
  cb=on;
}
void TLeds::clear(bool all){
  for(byte i=0;i<(all?sizeof(ios):8);i++){
    digitalWrite(ios[i],LOW);
  }
}
