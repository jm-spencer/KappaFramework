#include "kappa/input/impl/timeInput.hpp"
#include "pros/rtos.hpp"

namespace kappa {

TimeInput::TimeInput() {}

const double &TimeInput::get() {
  value = pros::millis();
  return value;
}

const double &TimeInput::getValue() const {
  return value;
}

}
