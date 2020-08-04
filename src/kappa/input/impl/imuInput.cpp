#include "kappa/input/impl/imuInput.hpp"

namespace kappa {

ImuInput::ImuInput(const std::uint8_t port, bool ccw):
  input(std::make_shared<pros::Imu>(port)), coef(ccw ? -1 : 1) {}

std::int32_t ImuInput::calibrate() const {
  return input->reset();
}

std::shared_ptr<pros::Imu> ImuInput::getInput() const {
  return input;
}

const double &ImuInput::get() {
  value = coef * input->get_rotation();
  return value;
}

const double &ImuInput::getValue() const {
  return value;
}

}
