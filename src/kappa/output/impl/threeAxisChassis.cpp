#include "kappa/output/impl/threeAxisChassis.hpp"
#include <math.h>

namespace kappa {

ThreeAxisChassis::ThreeAxisChassis(std::shared_ptr<AbstractOutput<std::array<double,4>>> ichassis):
  chassis(ichassis), linearScalar(1), angularScalar(1){}

ThreeAxisChassis::ThreeAxisChassis(double iwheelDiameter, double ichassisWidth, std::shared_ptr<AbstractOutput<std::array<double,4>>> ichassis):
  chassis(ichassis), linearScalar((60.0 / M_PI) / iwheelDiameter), angularScalar((30.0 / M_PI) * (ichassisWidth / iwheelDiameter)) {}

void ThreeAxisChassis::set(const std::tuple<double,double,double> &iTarget) {
  double forwardTarget  = linearScalar  * std::get<0>(iTarget);
  double sidewaysTarget = linearScalar  * std::get<1>(iTarget);
  double rotationTarget = angularScalar * std::get<2>(iTarget);

  chassis->set({forwardTarget - sidewaysTarget - rotationTarget,
                forwardTarget + sidewaysTarget - rotationTarget,
                forwardTarget - sidewaysTarget + rotationTarget,
                forwardTarget + sidewaysTarget + rotationTarget});
}

std::shared_ptr<AbstractOutput<std::array<double,4>>> ThreeAxisChassis::getOutput() const {
  return chassis;
}

}
