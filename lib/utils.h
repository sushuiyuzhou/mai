//
// Created by suhuiyuzhou on 28/05/2020.
//

#ifndef MAI_UTILS_H
#define MAI_UTILS_H

#include <iostream>
#include <string>

namespace mai {

namespace {// print methods

template<typename T>
std::ostream &operator<<(std::ostream &os, std::vector<T> const &ctn) {
  for (auto const &e : ctn) {
    os << e << "\n";
  }
  return os;
}

template<typename T>
std::istream &operator>>(std::istream &is, std::vector<T> &ctn) {
  T tmp;
  while (is >> tmp) {
    ctn.push_back(tmp);
  }
  return is;
}

template<typename T, size_t N>
std::ostream &operator<<(std::ostream &os, std::array<T, N> const &ctn) {
  for (auto const &e : ctn) {
    os << e << "\n";
  }
  return os;
}

template<typename T, size_t N>
std::istream &operator>>(std::istream &is, std::array<T, N> &ctn) {
  for (std::size_t i{0}; i < N; i++) {
    is >> ctn[i];
  }
  return is;
}

}// namespace

}// namespace mai

#endif//MAI_UTILS_H
