#include "kappa/output/impl/voltageMotor.hpp"

namespace kappa {

VoltageMotor::VoltageMotor(std::shared_ptr<okapi::AbstractMotor> imotor):
  motor(imotor){}

void VoltageMotor::set(const double &iTarget) {
  motor->moveVoltage(iTarget);
}

std::shared_ptr<okapi::AbstractMotor> VoltageMotor::getMotor() const {
  return motor;
}

}
