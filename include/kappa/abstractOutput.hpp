#pragma once

namespace kappa {

template <typename T> class AbstractOutput {
public:
  /**
   * Accept values in the range [-1,1]
   */
  virtual void set(T itarget) = 0;
};

}
