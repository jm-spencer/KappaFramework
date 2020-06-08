#include "kappa/timeInput"
#include "pros/rtos.h"

namespace kappa {

TimeInput::TimeInput() {}

TimeInput::get() const {
  return pros::millis();
}

}
