#pragma once
#include <stdlib.h>
#include <cmath>
#include <limits>

struct shader_sin
{
  uint32_t seed;
  void Init(uint32_t in_seed) { seed = in_seed; }

  uint32_t Run() { 
    static uint32_t pos = 11;
    double res = (sin(double(pos++) * (seed + 23.424)) * 43758.5453);
    res = res - floor(res);
    return uint32_t(res * std::numeric_limits<uint32_t>::max());
  }
};