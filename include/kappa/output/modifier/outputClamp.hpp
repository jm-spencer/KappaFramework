#pragma once

#include "kappa/output/abstractOutput.hpp"
#include <algorithm>
#include <memory>


namespace kappa {

template <typename T>
class OutputClamp : public AbstractOutput<T> {
public:
  OutputClamp(std::shared_ptr<AbstractOutput<T>> ioutput, T imin, T imax):
    output(ioutput), min(imin), max(imax) {}

  virtual void set(T iTarget) override {
    output->set(std::clamp(iTarget, min, max));
  }

  std::shared_ptr<AbstractOutput<T>> getOutput() const {
    return output;
  }

protected:
  std::shared_ptr<AbstractOutput<T>> output{nullptr};
  T min{0};
  T max{0};
};


}
