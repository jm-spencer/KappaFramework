#include "kappa/output/impl/xdriveChassis.hpp"
#include <math.h>

namespace kappa {

XDriveChassis::XDriveChassis(std::shared_ptr<AbstractOutput<std::array<double,4>>> ichassis):
  chassis(ichassis), linearScalar(1), angularScalar(1){}

XDriveChassis::XDriveChassis(double iwheelDiameter, double ichassisWidth, std::shared_ptr<AbstractOutput<std::array<double,4>>> ichassis):
  chassis(ichassis), linearScalar(M_SQRT2 * (30.0 / M_PI) / iwheelDiameter), angularScalar((30.0 / M_PI) * (ichassisWidth / iwheelDiameter)) {}

void XDriveChassis::set(const std::tuple<double,double,double> &iTarget) {
  double forwardTarget  = linearScalar  * std::get<0>(iTarget);
  double sidewaysTarget = linearScalar  * std::get<1>(iTarget);
  double rotationTarget = angularScalar * std::get<2>(iTarget);

  chassis->set({forwardTarget - sidewaysTarget - rotationTarget,
                forwardTarget + sidewaysTarget - rotationTarget,
                forwardTarget - sidewaysTarget + rotationTarget,
                forwardTarget + sidewaysTarget + rotationTarget});
}

void XDriveChassis::setPolar(const std::tuple<double,double,double> &iTarget) {
  set({std::get<0>(iTarget) * cos(std::get<1>(iTarget)), std::get<0>(iTarget) * sin(std::get<1>(iTarget)), std::get<2>(iTarget)});
}

std::shared_ptr<AbstractOutput<std::array<double,4>>> XDriveChassis::getOutput() const {
  return chassis;
}

}
