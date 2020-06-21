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
    std::make_shared<kappa::TupleOutputLogger<double,double>>(6, "Tuple Logger ", " | ", "\n",
      std::make_shared<kappa::TwoAxisChassis>(4, 10,
        std::make_shared<kappa::ArrayOutputClamp<double,2>>(-100, 100,
          std::make_shared<kappa::ArrayOutputLogger<double,2>>(6, "Array Logger ", " | ", "\n",
            std::make_shared<kappa::ArrayDistributor<double,2>>(
              kappa::ArrayDistributor<double,2>({
                std::make_shared<kappa::VelocityMotor>(std::make_shared<okapi::Motor>(19)),
                std::make_shared<kappa::OutputLogger<double>>(6, "Output Logger ", "\n\n",
                  std::make_shared<kappa::VelocityMotor>(std::make_shared<okapi::Motor>(20))
                )
              })
            )
          )
        )
      )
    );

  auto input =
    std::make_shared<kappa::InputLogger<double>>(6, "Input Logger ", "\n\n",
      std::make_shared<kappa::OkapiInput>(
        std::make_shared<okapi::ADIEncoder>(3,4)
      )
    );

  auto controller =
    std::make_shared<kappa::PidController>(kappa::PidController::Gains{1,0,0.5,0});

  std::tuple<double,double> target = {50,0};

  while(true) {
    std::get<1>(target) = controller->step(input->get());
    chassis->set(target);

    pros::delay(10);
  }

}
