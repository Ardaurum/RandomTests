#pragma once
#include <stdlib.h>

struct murmur
{
  uint32_t seed;

  void Init(uint32_t in_seed) { seed = in_seed; }
  uint32_t Run() { 
    static uint32_t pos = 0;

    uint32_t res = (pos++) * (seed + 52354);
    res ^= res >> 16;
    res *= 0x7feb362dU;
    res ^= res >> 15;
    res *= 0x846ca68bU;
    res ^= res >> 16;
    return res;
  }
};