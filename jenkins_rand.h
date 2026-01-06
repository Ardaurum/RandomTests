#pragma once
#include <stdlib.h>

struct jenkins
{
  uint32_t seed;

  void Init(uint32_t in_seed) { seed = in_seed; }
  uint32_t Run() { 
    static uint32_t pos = 11;

    uint32_t res = (pos++) * (seed + 52354);
    res -= res << 6;
    res ^= res >> 17;
    res -= res << 9;
    res ^= res << 4;
    res -= res << 3;
    res ^= res << 10;
    res ^= res >> 15;
    return res;
  }
};