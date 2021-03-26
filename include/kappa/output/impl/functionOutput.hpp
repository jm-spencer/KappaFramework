#pragma once

#include "kappa/output/abstractOutput.hpp"
#include <functional>


namespace kappa {

template<typename T>
class FunctionOutput : public AbstractOutput<T> {
public:

  /**
   * passes the target value to a function
   *
   * @param ifn function to be run
   * @param istopfn stopping function
   */
  FunctionOutput(std::function<void(const T&)> ifn, std::function<void(void)> istopfn = []{}):
    fn(ifn), stopfn(istopfn){}

  /**
   * runs the function with the target value
   *
   * @param itarget target value
   */
  virtual void set(const T &itarget) override {
    fn(itarget);
  }

  /**
   * Send a stop command to the lowermost level of the output
   * eg. idle the motor, as opposed to trying to hold vel = 0
   */
  virtual void stop() override {
    stopfn();
  }

protected:
  std::function<void(const T&)> fn;
  std::function<void(void)> stopfn;
};

}
