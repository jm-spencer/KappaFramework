#pragma once

namespace kappa {

template <typename T> class AbstractOutput {
public:
  /**
   * Bounds are implimentation specific
   */
  virtual void set(const T &itarget) = 0;

  /**
   * Send a stop command to the lowermost level of the output
   * eg. idle the motor, as opposed to trying to hold vel = 0
   */
  virtual void stop() = 0;
};

}
