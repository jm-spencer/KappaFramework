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

  VPidSubController(Gains igains,
                    double iconversion, // (# of controller iterations in target time unit) * (# of encoder ticks in target distance unit)
                    std::shared_ptr<AbstractInput<double>> iinput,
                    std::shared_ptr<AbstractOutput<double>> ioutput);

  VPidSubController(Gains igains,
                    double iconversion, // (# of controller iterations in target time unit) * (# of encoder ticks in target distance unit)
                    std::unique_ptr<okapi::Filter> ivelocityFilter,
                    std::unique_ptr<okapi::Filter> iderivativeFilter,
                    std::shared_ptr<AbstractInput<double>> iinput,
                    std::shared_ptr<AbstractOutput<double>> ioutput);

  virtual void set(const double &itarget) override;

  virtual void reset() override;

protected:
  Gains gains;
  std::unique_ptr<okapi::Filter> velocityFilter{nullptr};
  std::unique_ptr<okapi::Filter> derivativeFilter{nullptr};
  double conversion{0};

  double currentReading{0};

  double currentVelocity{0};

  double lastError{0};
  double derivative{0};

  double closedLoopSignal{0};
};

}
