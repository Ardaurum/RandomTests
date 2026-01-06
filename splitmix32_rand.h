#pragma once
#include <stdlib.h>

struct splitmix32
{
  uint32_t seed;

  void Init(uint32_t in_seed) { seed = in_seed; }
  uint32_t Run() { 
    static uint32_t pos = 11;

    uint32_t res = (pos++) * (seed + 52354);
    res += 0x9e3779b9;
    res = (res ^ (res >> 16)) * 0x85ebca6b;
    res = (res ^ (res >> 13)) * 0xc2b2ae35b;
    return res ^ (res >> 16);
    return res;
  }
};