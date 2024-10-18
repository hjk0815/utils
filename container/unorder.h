
#pragma once

// #include "output_container.h"
#include <complex>       // std::complex
#include <iostream>      // std::cout/endl
#include <unordered_map> // std::unordered_map
#include <unordered_set> // std::unordered_set

using namespace std;

namespace std {   // 增加complex类型的哈希计算函数  同理也可以增加自定义的数据结构的哈希计算

template <typename T> struct hash<complex<T>> {
  size_t operator()(const complex<T> &v) const noexcept {
    hash<T> h;
    return h(v.real()) + h(v.imag());
  }
};

} // namespace std

void unorderTest();