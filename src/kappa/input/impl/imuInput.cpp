#include "kappa/input/impl/imuInput.hpp"

namespace kappa {

ImuInput::ImuInput(const std::uint8_t port):
  input(std::make_shared<pros::Imu>(port)) {}

std::int32_t ImuInput::calibrate() const {
  return input->reset();
}

std::shared_ptr<pros::Imu> ImuInput::getInput() const {
  return input;
}

const double &ImuInput::get() {
  value = input->get_rotation();
  return value;
}

const double &ImuInput::getValue() const {
  return value;
}

}
