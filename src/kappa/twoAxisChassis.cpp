#include "twoAxisChassis.hpp"
#include <math.h>

namespace kappa {

TwoAxisChassis::TwoAxisChassis(std::shared_ptr<AbstractOutput<std::tuple<double,double>>> ichassis, double iwheelDiameter, double ichassisWidth):
  chassis(ichassis), linearScalar((30.0 / M_PI) / iwheelDiameter), angularScalar((30.0 / M_PI) * (ichassisWidth / iwheelDiameter)) {}

void TwoAxisChassis::set(std::tuple<double,double> iTarget) {
  double linearTarget   = linearScalar  * std::get<0>(iTarget);
  double rotationTarget = angularScalar * std::get<1>(iTarget);

  chassis->set(std::make_tuple(linearTarget + rotationTarget,
                               linearTarget - rotationTarget));
}

std::shared_ptr<AbstractOutput<std::tuple<double,double>>> TwoAxisChassis::getOutput() const {
  return chassis;
}

}
