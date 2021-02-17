#include "kappa/output/impl/mechanumChassis.hpp"
#include <math.h>

/**
 * Kinematic equations modified from https://research.ijcaonline.org/volume113/number3/pxc3901586.pdf
 */

namespace kappa {

MechanumChassis::MechanumChassis(std::shared_ptr<AbstractOutput<std::array<double,4>>> ichassis):
  chassis(ichassis), linearScalar(1), angularScalar(1){}

MechanumChassis::MechanumChassis(double iwheelDiameter, double iwheelDistance, std::shared_ptr<AbstractOutput<std::array<double,4>>> ichassis):
  chassis(ichassis), linearScalar((60.0 / M_PI) / iwheelDiameter), angularScalar((60.0 / M_PI) * (iwheelDistance / iwheelDiameter)) {}

void MechanumChassis::set(const std::tuple<double,double,double> &iTarget) {
  double forwardTarget  = linearScalar  * std::get<0>(iTarget);
  double sidewaysTarget = linearScalar  * std::get<1>(iTarget);
  double rotationTarget = angularScalar * std::get<2>(iTarget);

  chassis->set({forwardTarget - sidewaysTarget - rotationTarget,
                forwardTarget + sidewaysTarget - rotationTarget,
                forwardTarget - sidewaysTarget + rotationTarget,
                forwardTarget + sidewaysTarget + rotationTarget});
}

std::shared_ptr<AbstractOutput<std::array<double,4>>> MechanumChassis::getOutput() const {
  return chassis;
}

}
