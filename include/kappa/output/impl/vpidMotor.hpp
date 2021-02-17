#pragma once
#include "kappa/controller/impl/vPidSubController.hpp"
#include "kappa/input/impl/okapiInput.hpp"
#include "kappa/input/modifier/inputDifferentiator.hpp"
#include "kappa/output/impl/voltageMotor.hpp"
#include "okapi/impl/device/motor/motor.hpp"
#include "okapi/impl/device/rotarysensor/integratedEncoder.hpp"

#define KAPPA_RED_CONV    100.0/3.0
#define KAPPA_GREEN_CONV  200.0/3.0
#define KAPPA_BLUE_CONV   200.0

namespace kappa {

/**
 * Kind of like a factory for a VPidSubController controlling a motor using
 * the motor's IME. Allows users to not be so verbose for this common setup.
 *
 * @param iport The port number to use. A negative port number will reverse the motor
 * @param igains gains for the controller
 * @param iconversion unit conversion factor
 *  (# of milliseconds in target time unit) / (# of encoder ticks in target distance unit)
 * @param ioutputMin minimum value for controller output
 * @param ioutputMax maximum value for controller output
 * @param isensorFilter filter for calculating the motor velocity
 * @param icontrollerFilter filter for the derivative of the controller error
 */

kappa::VPidSubController makeVPIDMotor(
  std::int8_t iport,
  kappa::VPidSubController::Gains igains,
  double iconversion = KAPPA_GREEN_CONV,
  double ioutputMin = -12000,
  double ioutputMax =  12000,
  std::unique_ptr<okapi::Filter> isensorFilter = std::make_unique<okapi::PassthroughFilter>(),
  std::unique_ptr<okapi::Filter> icontrollerFilter = std::make_unique<okapi::PassthroughFilter>()
);

/*
 * @param imotor The Okapi Motor or MotorGroup to use
 * @param igains gains for the controller
 * @param iconversion unit conversion factor
 *  (# of milliseconds in target time unit) / (# of encoder ticks in target distance unit)
 * @param ioutputMin minimum value for controller output
 * @param ioutputMax maximum value for controller output
 * @param isensorFilter filter for calculating the motor velocity
 * @param icontrollerFilter filter for the derivative of the controller error
 */

kappa::VPidSubController makeVPIDMotor(
  std::shared_ptr<okapi::AbstractMotor> imotor,
  kappa::VPidSubController::Gains igains,
  double iconversion = KAPPA_GREEN_CONV,
  double ioutputMin = -12000,
  double ioutputMax =  12000,
  std::unique_ptr<okapi::Filter> isensorFilter = std::make_unique<okapi::PassthroughFilter>(),
  std::unique_ptr<okapi::Filter> icontrollerFilter = std::make_unique<okapi::PassthroughFilter>()
);

/*
 * @param imotor The Kappa VoltageMotor to use
 * @param igains gains for the controller
 * @param iconversion unit conversion factor
 *  (# of milliseconds in target time unit) / (# of encoder ticks in target distance unit)
 * @param ioutputMin minimum value for controller output
 * @param ioutputMax maximum value for controller output
 * @param isensorFilter filter for calculating the motor velocity
 * @param icontrollerFilter filter for the derivative of the controller error
 */

kappa::VPidSubController makeVPIDMotor(
  std::shared_ptr<kappa::VoltageMotor> imotor,
  kappa::VPidSubController::Gains igains,
  double iconversion = KAPPA_GREEN_CONV,
  double ioutputMin = -12000,
  double ioutputMax =  12000,
  std::unique_ptr<okapi::Filter> isensorFilter = std::make_unique<okapi::PassthroughFilter>(),
  std::unique_ptr<okapi::Filter> icontrollerFilter = std::make_unique<okapi::PassthroughFilter>()
);

}
