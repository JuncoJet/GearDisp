#include "config.h"
class TLeds{
  static char ios[],segs[];
  byte cur;
  char buf[4];
  unsigned long b;
public:
  byte cv,cb;
  TLeds();
  void show(byte v);
  void vshow(int v);
  void bar(byte on);
  void clear(bool all=true);
};
