#include "kappa/okapiInput.hpp"

namespace kappa {

OkapiInput::OkapiInput(std::shared_ptr<okapi::RotarySensor> iinput, double igearRatio):
  input(iinput), gearRatio(igearRatio) {}

double OkapiInput::get() const {
  return input->controllerGet() * gearRatio;
}

std::shared_ptr<okapi::RotarySensor> OkapiInput::getInput() const {
  return input;
}


}
