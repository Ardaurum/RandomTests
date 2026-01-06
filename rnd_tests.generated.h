#pragma once
#include <cstddef>
#include <cstdint>

#include "cpp_lcg_rand.h" 
#include "cpp_mt_rand.h" 
#include "cpp_rand_rand.h" 
#include "identity_rand.h" 
#include "jenkins_rand.h" 
#include "lcg_numeric_rand.h" 
#include "murmur_rand.h" 
#include "park_miller_rand.h" 
#include "pcg_rand.h" 
#include "shader_sin_rand.h" 
#include "splitmix32_rand.h" 
#include "squirrel_rand.h" 
#include "wang_rand.h" 
#include "xorshift128_rand.h" 
#include "xorshift32_rand.h" 
 
static cpp_lcg inst_0; 
static cpp_mt inst_1; 
static cpp_rand inst_2; 
static identity inst_3; 
static jenkins inst_4; 
static lcg_numeric inst_5; 
static murmur inst_6; 
static park_miller inst_7; 
static pcg inst_8; 
static shader_sin inst_9; 
static splitmix32 inst_10; 
static squirrel inst_11; 
static wang inst_12; 
static xorshift128 inst_13; 
static xorshift32 inst_14; 
 
inline size_t GetRndTestCount() {
  return 15;
}

inline char const* GetRndTestName(size_t index) {
  static char const* names[] = {
    "cpp_lcg", 
    "cpp_mt", 
    "cpp_rand", 
    "identity", 
    "jenkins", 
    "lcg_numeric", 
    "murmur", 
    "park_miller", 
    "pcg", 
    "shader_sin", 
    "splitmix32", 
    "squirrel", 
    "wang", 
    "xorshift128", 
    "xorshift32", 
  };
  return index < 15 ? names[index] : "";
}

inline void RunRndTestInit(size_t index, int32_t seed) {
  switch (index) {
    case 0: { inst_0.Init(seed); break; } 
    case 1: { inst_1.Init(seed); break; } 
    case 2: { inst_2.Init(seed); break; } 
    case 3: { inst_3.Init(seed); break; } 
    case 4: { inst_4.Init(seed); break; } 
    case 5: { inst_5.Init(seed); break; } 
    case 6: { inst_6.Init(seed); break; } 
    case 7: { inst_7.Init(seed); break; } 
    case 8: { inst_8.Init(seed); break; } 
    case 9: { inst_9.Init(seed); break; } 
    case 10: { inst_10.Init(seed); break; } 
    case 11: { inst_11.Init(seed); break; } 
    case 12: { inst_12.Init(seed); break; } 
    case 13: { inst_13.Init(seed); break; } 
    case 14: { inst_14.Init(seed); break; } 
    default: break;
  }
}

inline int32_t RunRndTestBody(size_t index) {
  switch (index) {
    case 0: { return inst_0.Run(); } 
    case 1: { return inst_1.Run(); } 
    case 2: { return inst_2.Run(); } 
    case 3: { return inst_3.Run(); } 
    case 4: { return inst_4.Run(); } 
    case 5: { return inst_5.Run(); } 
    case 6: { return inst_6.Run(); } 
    case 7: { return inst_7.Run(); } 
    case 8: { return inst_8.Run(); } 
    case 9: { return inst_9.Run(); } 
    case 10: { return inst_10.Run(); } 
    case 11: { return inst_11.Run(); } 
    case 12: { return inst_12.Run(); } 
    case 13: { return inst_13.Run(); } 
    case 14: { return inst_14.Run(); } 
    default: return 0;
  }
}
