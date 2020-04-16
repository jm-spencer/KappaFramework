#pragma once

#include "abstractOutput.hpp"
#include "tankChassis.hpp"
namespace kappa {

/**
 *  controller input should be of the format (linear, angular),
 *  given angular is a target in CW rad/s and linear is in the units of chassisWidth/s
 */

class TwoAxisChassis : public AbstractOutput<std::tuple<double,double>> {
public:
  TwoAxisChassis(std::shared_ptr<AbstractOutput<std::tuple<double,double>>> ichassis, double ichassisWidth);

  virtual void set(std::tuple<double,double> iTarget) override;

  std::shared_ptr<AbstractOutput<std::tuple<double,double>>> getOutput() const;

protected:
  std::shared_ptr<AbstractOutput<std::tuple<double,double>>> chassis;
  double chassisWidth{0};
};

}
