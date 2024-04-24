#include "config.h"
class TLeds{
  static char ios[],segs[];
  byte cur;
  char buf[4];
  unsigned long b;
public:
  TLeds();
  void show(byte v);
  void vshow(int v);
  void clear(bool all=true);
};
