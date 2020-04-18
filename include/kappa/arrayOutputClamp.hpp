#pragma once

#include "abstractOutput.hpp"
#include <array>
#include <algorithm>
#include <memory>

namespace kappa {

/**
 * Note: requires definition of the operators < > / and *=
 * for T values
 */

template <typename T, std::size_t N>
class ArrayOutputClamp : public AbstractOutput<std::array<T,N>> {
public:
  ArrayOutputClamp(std::shared_ptr<AbstractOutput<std::array<T,N>>> ioutput, T imin, T imax):
    output(ioutput), min(imin), max(imax) {}

  virtual void set(std::array<T,N> iTarget) override {
    T maxVal = std::max(iTarget);
    T minVal = std::min(iTarget);

    if(max < maxVal) {
      if(min > minVal) {
        output->set(scaleArray(iTarget, (max / maxVal) < (min / minVal) ? (max / maxVal) : (min / minVal)));
      } else {
        output->set(scaleArray(iTarget, max / maxVal));
      }
    } else {
      if(min > minVal) {
        output->set(scaleArray(iTarget, min / minVal));
      } else {
        output->set(iTarget);
      }
    }
  }

  std::shared_ptr<AbstractOutput<std::array<T,N>>> getOutput() const {
    return output;
  }

protected:
  std::shared_ptr<AbstractOutput<std::array<T,N>>> output{nullptr};
  T min{0};
  T max{0};

  static std::array<T,N> &scaleArray(std::array<T,N> &arr, T scalar) {
    for(T &i : arr){
      i *= scalar;
    }

    return arr;
  }
};


}
