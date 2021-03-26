#pragma once

#include "kappa/output/abstractOutput.hpp"
#include <memory>


namespace kappa {

template <typename T>
class OutputScalar : public AbstractOutput<T> {
public:

  /**
   * Scales control signal by a preset scalar
   * Requires definition of operator*(double,T)
   *
   * @param iscalar scalar
   * @param ioutput output for data
   */
  OutputScalar(double iscalar, std::shared_ptr<AbstractOutput<T>> ioutput):
    output(ioutput), scalar(iscalar) {}

  /**
   * Calculates the scaled target signal and sets it to the output
   *
   * @param itarget target
   */
  virtual void set(const T &itarget) override {
    target = scalar * itarget;
    output->set(target);
  }

  /**
   * Send a stop command to the lowermost level of the output
   * eg. idle the motor, as opposed to trying to hold vel = 0
   */
  virtual void stop() override {
    output->stop();
  }

  /**
   * Gets output
   *
   * @return output
   */
  std::shared_ptr<AbstractOutput<T>> getOutput() const {
    return output;
  }

protected:
  std::shared_ptr<AbstractOutput<T>> output{nullptr};
  T target{0};
  double scalar{0};
};

extern template class OutputScalar<double>;

}
