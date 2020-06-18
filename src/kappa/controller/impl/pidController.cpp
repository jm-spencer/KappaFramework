#include "kappa/controller/impl/pidController.hpp"
#include "kappa/controller/abstractController.hpp"

namespace kappa {

PidController::PidController(Gains igains, std::unique_ptr<okapi::SettledUtil> isettledUtil, std::unique_ptr<okapi::Filter> iderivativeFilter):
  gains(igains), settledUtil(std::move(isettledUtil)), derivativeFilter(std::move(iderivativeFilter)) {
    reset();
  }

void PidController::setTarget(const double &itarget) {
  target = itarget;
}

double PidController::step(double ireading) {
  error = target - ireading;

  integral += error;

  derivative = derivativeFilter->filter(error - lastError);

  output = (gains.kP * error) + (gains.kI * integral) + (gains.kD * derivative) + gains.kF;

  lastReading = ireading;
  lastError = error;

  settledUtil->isSettled(error);

  return output;
}

bool PidController::isSettled() {
   return isDisabled() ? true : settledUtil->isSettled(error);
}

void PidController::reset() {
  target = 0;
  lastReading = 0;
  error = 0;
  lastError = 0;
  output = 0;
  integral = 0;
  derivative = 0;
}

void PidController::disable(bool iisDisabled) {
  disabled = iisDisabled;
}

PidController::Gains PidController::getGains() const {
  return gains;
}

void PidController::setGains(Gains igains) {
  gains = igains;
}

}
