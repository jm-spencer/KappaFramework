#include "twoAxisChassis.hpp"

namespace kappa {

TwoAxisChassis::TwoAxisChassis(std::shared_ptr<AbstractOutput<std::tuple<double,double>>> ichassis, double ichassisWidth):
  chassis(ichassis), chassisWidth(ichassisWidth) {}

void TwoAxisChassis::set(std::tuple<double,double> iTarget) {
  double rotationTarget = chassisWidth * std::get<1>(iTarget);

  chassis->set(std::make_tuple(std::get<0>(iTarget) + rotationTarget,
                               std::get<0>(iTarget) - rotationTarget));
}

std::shared_ptr<AbstractOutput<std::tuple<double,double>>> TwoAxisChassis::getOutput() const {
  return chassis;
}

}
