#pragma once

#include "kappa/controller/abstractSubController.hpp"
#include "okapi/api/control/util/settledUtil.hpp"
#include "okapi/api/filter/filter.hpp"
#include "okapi/impl/util/timeUtilFactory.hpp"

namespace kappa {

class VPidSubController : public AbstractSubController<double, double, double> {
public:

  struct Gains {
    double kP;
    double kD;
    double kF;
    double kSF;
  };

  /**
   * A standard implementation of a Velocity PID controller
   * Runs as a subcontroller, meaning it can be part of another controller's output
   *
   * @param igains gains for the controller
   * @param iinput input for the measured velocity of the system
   * @param ioutput output for the control signal
   */
  VPidSubController(Gains igains,
                    std::shared_ptr<AbstractInput<double>> iinput,
                    std::shared_ptr<AbstractOutput<double>> ioutput);
  /**
   * @param igains gains for the controller
   * @param iderivativeFilter filter for the derivative of the error
   * @param iinput input for the measured velocity of the system
   * @param ioutput output for the control signal
   */
  VPidSubController(Gains igains,
                    std::unique_ptr<okapi::Filter> iderivativeFilter,
                    std::shared_ptr<AbstractInput<double>> iinput,
                    std::shared_ptr<AbstractOutput<double>> ioutput);

  /**
   * @param igains gains for the controller
   * @param ioutputMin minimum value for controller output
   * @param ioutputMax maximum value for controller output
   * @param iinput input for the measured velocity of the system
   * @param ioutput output for the control signal
   */
  VPidSubController(Gains igains,
                    double ioutputMin,
                    double ioutputMax,
                    std::shared_ptr<AbstractInput<double>> iinput,
                    std::shared_ptr<AbstractOutput<double>> ioutput);

  /**
   * @param igains gains for the controller
   * @param ioutputMin minimum value for controller output
   * @param ioutputMax maximum value for controller output
   * @param iderivativeFilter filter for the derivative of the error
   * @param iinput input for the measured velocity of the system
   * @param ioutput output for the control signal
   */
  VPidSubController(Gains igains,
                    double ioutputMin,
                    double ioutputMax,
                    std::unique_ptr<okapi::Filter> iderivativeFilter,
                    std::shared_ptr<AbstractInput<double>> iinput,
                    std::shared_ptr<AbstractOutput<double>> ioutput);

  /**
   * Sets the target value of the controller
   *
   * @param itarget the new target
   */
  virtual void set(const double &itarget) override;

  /**
   * Resets the controller to behavior immediately after construction
   * (like reseting "last iteration" values)
   */
  virtual void reset() override;

protected:
  Gains gains;
  std::unique_ptr<okapi::Filter> derivativeFilter{nullptr};

  double currentVelocity{0};

  double lastError{0};
  double derivative{0};

  double closedLoopSignal{0};
};

}
