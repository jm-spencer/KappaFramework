#include "kappa/input/impl/imuInput.hpp"
#include "api.h"

namespace kappa {

ImuInput::ImuInput(const std::uint8_t port, bool ccw):
  input(std::make_shared<pros::Imu>(port)), coef(ccw ? -1 : 1) {
    calibrate();
  }

std::int32_t ImuInput::calibrate() const {
  return input->reset();
}

std::shared_ptr<pros::Imu> ImuInput::getInput() const {
  return input;
}

const double &ImuInput::get() {
  value = coef * input->get_rotation();
  if (value == PROS_ERR_F) value = 0;
  return value;
}

const double &ImuInput::getValue() const {
  return value;
}

}
