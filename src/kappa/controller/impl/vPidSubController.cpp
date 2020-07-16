#include "kappa/controller/impl/vPidSubController.hpp"
#include "okapi/api/filter/passthroughFilter.hpp"

namespace kappa {

static inline double sgn(double val) {
    return val > 0 ? 1 : val < 0 ? -1 : 0;
}

VPidSubController::VPidSubController(Gains igains,
                                     std::shared_ptr<AbstractInput<double>> iinput,
                                     std::shared_ptr<AbstractOutput<double>> ioutput):
                                     VPidSubController(igains, std::make_unique<okapi::PassthroughFilter>(), std::make_unique<okapi::PassthroughFilter>(), iinput, ioutput) {}

VPidSubController::VPidSubController(Gains igains,
                                     std::unique_ptr<okapi::Filter> ivelocityFilter,
                                     std::unique_ptr<okapi::Filter> iderivativeFilter,
                                     std::shared_ptr<AbstractInput<double>> iinput,
                                     std::shared_ptr<AbstractOutput<double>> ioutput):
                                     gains(igains), velocityFilter(std::move(ivelocityFilter)), derivativeFilter(std::move(iderivativeFilter)) {
    input = iinput;
    outputDevice = ioutput;
    reset();
}

void VPidSubController::set(const double &itarget) {
    currentReading = input->get();
    currentVelocity = velocityFilter->filter(currentReading - lastReading);
    lastReading = currentReading;

    error = target - currentVelocity;
    derivative = derivativeFilter->filter(error - lastError);
    lastError = error;

    target = itarget;

    closedLoopSignal = std::clamp(error * gains.kP + derivative * gains.kD, outputMin, outputMax);

    output = std::clamp(closedLoopSignal + target * gains.kF + sgn(target) * gains.kSF, outputMin, outputMax);

    outputDevice->set(output);
}

void VPidSubController::reset() {
    target = 0;
    lastReading = input->get();
    error = 0;
    output = 0;
    currentReading = 0;
    currentVelocity = 0;
    lastError = 0;
    derivative = 0;
    closedLoopSignal = 0;
}

}