#pragma once
#include <stdlib.h>

// Squirrel hash used from this great talk: https://www.youtube.com/watch?v=LWFzPP8ZbdU by Squirrel Eiserloh
struct squirrel
{
  uint32_t seed;

  void Init(uint32_t in_seed) { seed = in_seed; }
  uint32_t Run() { 
    constexpr uint32_t BIT_NOISE1 = 0x68E31DA4;
    constexpr uint32_t BIT_NOISE2 = 0xB5297A4D;
    constexpr uint32_t BIT_NOISE3 = 0x1B56C4E9;
    static uint32_t pos = 0;

    uint32_t res = pos++;
    res *= BIT_NOISE1;
    res += seed;
    res ^= (res >> 8);
    res += BIT_NOISE2;
    res ^= (res << 8);
    res *= BIT_NOISE3;
    res ^= (res >> 8);
    return res;
  }
};