#include "kappa/velocityMotor.hpp"

namespace kappa {

VelocityMotor::VelocityMotor(std::shared_ptr<okapi::AbstractMotor> imotor):
  motor(imotor){

  maxVelocity = static_cast<std::underlying_type_t<okapi::AbstractMotor::gearset>>(motor->getGearing());
}

void VelocityMotor::set(double iTarget) {
  motor->moveVelocity(iTarget * maxVelocity);
}

std::shared_ptr<okapi::AbstractMotor> VelocityMotor::getMotor() const {
  return motor;
}

}
