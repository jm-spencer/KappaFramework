#pragma once

#include "abstractOutput.hpp"
#include "tankChassis.hpp"
#include "okapi/api/util/logging.hpp"

namespace kappa {

/**
 *  controller input should be of the format (linear, angular),
 *  given angular is a target in CW rad/s and linear is in the units of chassisWidth/s
 */

class TwoAxisChassis : public AbstractOutput<std::tuple<double,double>> {
public:
  TwoAxisChassis(std::shared_ptr<AbstractOutput<std::tuple<double,double>>> ichassis, double ichassisWidth, const std::shared_ptr<okapi::Logger> &ilogger = okapi::Logger::getDefaultLogger());

  virtual void set(std::tuple<double,double> iTarget) override;

  std::shared_ptr<AbstractOutput<std::tuple<double,double>>> getOutput() const;

protected:
  std::shared_ptr<AbstractOutput<std::tuple<double,double>>> chassis;
  double chassisWidth{0};

  std::shared_ptr<okapi::Logger> logger;
};

}
