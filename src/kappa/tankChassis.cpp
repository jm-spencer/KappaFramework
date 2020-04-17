#include "kappa/tankChassis.hpp"

namespace kappa {

TankChassis::TankChassis(std::array<std::shared_ptr<AbstractOutput<double>>,2> imotors):
  motors(std::move(imotors)) {}

void TankChassis::set(std::array<double,2> iTarget) {
  motors[0]->set(iTarget[0]);
  motors[1]->set(iTarget[1]);
}

std::array<std::shared_ptr<AbstractOutput<double>>,2> TankChassis::getOutput() const {
  return motors;
}

}
