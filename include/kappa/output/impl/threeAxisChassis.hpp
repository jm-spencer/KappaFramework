#pragma once

#include "kappa/output/abstractOutput.hpp"
#include <tuple>
#include <memory>


namespace kappa {

/**
 *  controller input should be of the format (forward, sideways, angular),
 *  both linear inputs are in the units in/s, and angular in rad/s, and
 *  outputs are assumed to be in rpm
 */
class ThreeAxisChassis : public AbstractOutput<std::tuple<double,double,double>> {
public:
  ThreeAxisChassis(std::shared_ptr<AbstractOutput<std::array<double,4>>> ichassis);

  ThreeAxisChassis(double iwheelDiameter, double ichassisWidth, std::shared_ptr<AbstractOutput<std::array<double,4>>> ichassis);

  virtual void set(const std::tuple<double,double,double> &iTarget) override;

  std::shared_ptr<AbstractOutput<std::array<double,4>>> getOutput() const;

protected:
  std::shared_ptr<AbstractOutput<std::array<double,4>>> chassis{nullptr};
  double linearScalar{0};
  double angularScalar{0};
};

}
