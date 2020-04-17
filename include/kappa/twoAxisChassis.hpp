#pragma once

#include "abstractOutput.hpp"
#include "tankChassis.hpp"
#include "okapi/api/util/logging.hpp"

namespace kappa {

/**
 *  controller input should be of the format (linear, angular),
 *  linear is in the units in/s, and angular in rad/s, and
 *  assumes outputs are in rpm
 */

class TwoAxisChassis : public AbstractOutput<std::tuple<double,double>> {
public:
  TwoAxisChassis(std::shared_ptr<AbstractOutput<std::tuple<double,double>>> ichassis, double iwheelDiameter, double ichassisWidth);

  virtual void set(std::tuple<double,double> iTarget) override;

  std::shared_ptr<AbstractOutput<std::tuple<double,double>>> getOutput() const;

protected:
  std::shared_ptr<AbstractOutput<std::tuple<double,double>>> chassis;
  double linearScalar{0};
  double angularScalar{0};
};

}
