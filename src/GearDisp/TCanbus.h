#include "config.h"
#include <CAN.h>
class TCanbus{
  bool useStdAddr;
  static int canid,filter,busspeed;
public:
  static bool dbgon;
  static int rpm,speed,oiltmp,gear;
  void init();
  void init(int busspeed,int filter=0);
  void getRpm();
  byte getGear();
  void getSpeed();
  void response();
  static void onReceive(int packetSize);
  void clrErrs();
};
