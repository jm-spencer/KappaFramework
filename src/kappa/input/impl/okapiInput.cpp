#include "kappa/input/impl/okapiInput.hpp"

namespace kappa {

OkapiInput::OkapiInput(std::shared_ptr<okapi::RotarySensor> iinput, double igearRatio):
  input(iinput), gearRatio(igearRatio) {}


std::shared_ptr<okapi::RotarySensor> OkapiInput::getInput() const {
  return input;
}

const double &OkapiInput::get() {
  value = input->controllerGet() * gearRatio;
  return value;
}

const double &OkapiInput::getValue() const {
  return value;
}

}
