#pragma once

// From: https://stackoverflow.com/questions/1198260/how-can-you-iterate-over-the-elements-of-an-stdtuple

#include <tuple>
#include <utility>
#include <ostream>

template<std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I == sizeof...(Tp), void>::type
printTuple(const std::tuple<Tp...> &t, std::ostream &iout, const std::string &seperator) {}

template<std::size_t I = 0, typename... Tp>
inline typename std::enable_if<I < sizeof...(Tp), void>::type
printTuple(const std::tuple<Tp...> &t, std::ostream &iout, const std::string &seperator) {
  iout << std::get<I>(t) << seperator;
  printTuple<I + 1, Tp...>(t, iout, seperator);
}