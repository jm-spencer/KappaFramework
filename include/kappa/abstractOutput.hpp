#pragma once

namespace kappa {

template <typename T> class AbstractOutput {
public:
  virtual void set(T itarget) = 0;
};

}
