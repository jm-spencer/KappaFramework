#include "kappa/input/impl/timeInput.hpp"
#include "pros/rtos.hpp"

namespace kappa {

TimeInput::TimeInput() {}

double TimeInput::get() const {
  return pros::millis();
}

}
