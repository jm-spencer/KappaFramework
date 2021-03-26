#include "kappa/output/impl/velocityMotor.hpp"

namespace kappa {

VelocityMotor::VelocityMotor(std::shared_ptr<okapi::AbstractMotor> imotor):
  motor(imotor) {}

void VelocityMotor::set(const double &iTarget) {
  motor->moveVelocity(iTarget);
}

void VelocityMotor::stop() {
  motor->moveVelocity(0);
}

std::shared_ptr<okapi::AbstractMotor> VelocityMotor::getMotor() const {
  return motor;
}

}
