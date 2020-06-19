#include "main.h"
#include "kappa/api.hpp"
#include "okapi/api.hpp"

void initialize() {
  okapi::Logger::setDefaultLogger(std::make_shared<okapi::Logger>(std::make_unique<okapi::Timer>(), "/ser/sout", okapi::Logger::LogLevel::debug));
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

void opcontrol() {

  auto chassis =
    std::make_shared<kappa::TupleOutputLogger<double,double>>(
      std::make_shared<kappa::TwoAxisChassis>(4, 10,
        std::make_shared<kappa::ArrayOutputClamp<double,2>>(-100, 100,
          std::make_shared<kappa::ArrayOutputLogger<double,2>>(
            std::make_shared<kappa::ArrayDistributor<double,2>>(
              kappa::ArrayDistributor<double,2>({
                std::make_shared<kappa::VelocityMotor>(std::make_shared<okapi::Motor>(1)),
                std::make_shared<kappa::VelocityMotor>(std::make_shared<okapi::Motor>(2))
              })
            )
          )
        )
      )
    );

  std::tuple<double,double> target = {1,0};

  while(true) {
    chassis->set(target);
    pros::delay(10);
  }

}
