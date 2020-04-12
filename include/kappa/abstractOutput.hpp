#pragma once

namespace kappa {

template <typename T> class AbstractOutput {
public:
  virtual T set() const = 0;
};

}
