#include "unorder.h"

// namespace std {   // 增加complex类型的哈希计算函数  同理也可以增加自定义的数据结构的哈希计算

// template <typename T> struct hash<complex<T>> {
//   size_t operator()(const complex<T> &v) const noexcept {
//     hash<T> h;
//     return h(v.real()) + h(v.imag());
//   }
// };

// } // namespace std

void unorderTest() {
  // 数字分隔符
  int a = 123'456;
  cout << "Number separator :: " << a << endl;

  unordered_set<int> s{1, 1, 2, 3, 5, 8, 13, 21};
  // cout << s << endl;

  unordered_map<complex<double>, double> umc{{{1.0, 1.0}, 1.4142},
                                             {{3.0, 4.0}, 5.0}};
  // cout << umc << endl;
}