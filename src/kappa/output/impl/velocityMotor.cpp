#include "kappa/output/impl/velocityMotor.hpp"

namespace kappa {

VelocityMotor::VelocityMotor(std::shared_ptr<okapi::AbstractMotor> imotor):
  motor(imotor) {}

void VelocityMotor::set(const double &iTarget) {
  motor->moveVelocity(iTarget);
}

std::shared_ptr<okapi::AbstractMotor> VelocityMotor::getMotor() const {
  return motor;
}

}
