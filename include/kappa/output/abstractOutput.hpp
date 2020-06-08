#pragma once

namespace kappa {

template <typename T> class AbstractOutput {
public:
  /**
   * Bounds are implimentation specific
   */
  virtual void set(T itarget) = 0;
};

}
