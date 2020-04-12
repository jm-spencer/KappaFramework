#include "kappa/velocityMotor.hpp"

namespace kappa {

VelocityMotor::VelocityMotor(std::shared_ptr<okapi::AbstractMotor> imotor):
  motor(imotor){}

void VelocityMotor::set(double iTarget) {
  motor->moveVelocity(iTarget);
}

std::shared_ptr<okapi::AbstractMotor> VelocityMotor::getMotor() const {
  return motor;
}

}
