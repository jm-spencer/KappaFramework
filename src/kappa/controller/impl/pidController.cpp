#include "kappa/controller/impl/pidController.hpp"
#include "kappa/controller/abstractController.hpp"

namespace kappa {

PidController::PidController(Gains igains, const okapi::TimeUtil &itimeUtil, std::unique_ptr<okapi::Filter> iderivativeFilter):
  PidController(igains, -DBL_MAX, DBL_MAX, itimeUtil, std::move(iderivativeFilter)) {}

PidController::PidController(Gains igains, double ioutputMin, double ioutputMax, const okapi::TimeUtil &itimeUtil, std::unique_ptr<okapi::Filter> iderivativeFilter):
  outputMin(ioutputMin), outputMax(ioutputMax), gains(igains), settledUtil(itimeUtil.getSettledUtil()), derivativeFilter(std::move(iderivativeFilter)) {
    reset();
  }

void PidController::setTarget(const double &itarget) {
  target = itarget;
}

void PidController::setOutputLimits(double imin, double imax) {
  outputMin = imin;
  outputMax = imax;
}

double PidController::getMinOutput() const {
  return outputMin;
}

double PidController::getMaxOutput() const {
  return outputMax;
}

double PidController::step(double ireading) {
  if(!disabled){
    error = target - ireading;

    integral += error;

    derivative = derivativeFilter->filter(error - lastError);

    output = (gains.kP * error) + (gains.kI * integral) + (gains.kD * derivative) + gains.kF;

    lastReading = ireading;
    lastError = error;

    settledUtil->isSettled(error);

    return output;
  } else {
    return 0;
  }
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
