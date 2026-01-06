#pragma once
#include <stdlib.h>
#include <cmath>
#include <limits>

struct wang
{
  uint32_t seed;
  void Init(uint32_t in_seed) { seed = in_seed; }

  uint32_t Run() { 
    static uint32_t pos = 11;
    uint32_t res = (pos++) * (seed + 52354);
    res = (res ^ 61) ^ (res >> 16);
    res *= 9;
    res = res & (res >> 4);
    res *= 0x27d4eb2d;
    return res ^ (res >> 15);
  }
};