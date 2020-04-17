#include "kappa/strafeChassis.hpp"

namespace kappa {

StrafeChassis::StrafeChassis(std::array<std::shared_ptr<AbstractOutput<double>>,4> imotors):
  motors(std::move(imotors)) {}

void StrafeChassis::set(std::array<double,4> iTarget) {
  motors[0]->set(iTarget[0]);
  motors[1]->set(iTarget[1]);
  motors[2]->set(iTarget[2]);
  motors[3]->set(iTarget[3]);
}

std::array<std::shared_ptr<AbstractOutput<double>>,4> StrafeChassis::getOutput() const {
  return motors;
}

}
