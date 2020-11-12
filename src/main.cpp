#include "main.h"
#include "kappa/api.hpp"
#include "okapi/api.hpp"

void initialize() {}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

/*
 * Defining things globally, as that is what I would recommend in a normal project,
 * unless you only use this for auton or something
 */
std::shared_ptr<kappa::TupleOutputLogger<double,double>> chassis;
std::shared_ptr<kappa::InputLogger<double>> input;
std::shared_ptr<kappa::PidController> controller;
std::shared_ptr<kappa::ArrayInputLogger<double,3>> testInput;

void opcontrol() {

  // I personally like these settings, show 6 digits for everything logged,
  // and add zeros if there aren't 6 digits (so everything more or less aligns)
  std::cout.setf(std::ios::fixed);
  std::cout << std::setprecision(6);

  // LVGL stuff. Read up on the docs for more information and customization.
  // Pretty much everything is set to defaults in this project
  auto chart = lv_chart_create(lv_scr_act(), NULL);
  lv_obj_set_pos(chart, 0, 0);
  lv_obj_set_size(chart, 480, 120);
  lv_chart_set_type(chart, LV_CHART_TYPE_LINE);
  lv_chart_set_range(chart, -120, 120);
  lv_chart_set_point_count(chart, 240);
  auto targ1 = lv_chart_add_series(chart, LV_COLOR_BLACK);
  auto read1 = lv_chart_add_series(chart, LV_COLOR_RED);
  auto targ2 = lv_chart_add_series(chart, LV_COLOR_BLUE);
  auto read2 = lv_chart_add_series(chart, LV_COLOR_YELLOW);

  auto gauge = lv_gauge_create(lv_scr_act(), NULL);
  lv_obj_set_size(gauge, 120, 120);
  lv_obj_set_pos(gauge, 0, 120);
  lv_gauge_set_range(gauge, -110, 110);
  lv_gauge_set_critical_value(gauge, 200);
  static lv_color_t ncolor[] = {LV_COLOR_RED};
  lv_gauge_set_needle_count(gauge, 1, ncolor);

  // kappa::AbstractInput<std::tuple<double,double>>
  // the first term is for a linear velocity command, and the second for angular (turing) velocity
  chassis =
    // Log both target values to cout (by default, can be change to any ostream)
    std::make_shared<kappa::TupleOutputLogger<double,double>>(" Tuple Logger ", " | ", "\n",
      // Convert from linear/angular targets to left/right targets using chassis constants
      std::make_shared<kappa::TwoAxisChassis>(4, 10,
        // Ensure targets are within the bounds of the motors while preserving ratio between targets
        std::make_shared<kappa::ArrayOutputClamp<double,2>>(-100, 100,
          // Log both target values to cout (by default)
          std::make_shared<kappa::ArrayOutputLogger<double,2>>(" Array Logger ", " | ", "\n",
            // Split the target values into seperate "control trees"
            std::make_shared<kappa::ArrayDistributor<double,2>>(std::initializer_list<std::shared_ptr<kappa::AbstractOutput<double>>>{
              // Branch 1, left: Log the target velocity to the lvgl chart
              std::make_shared<kappa::OutputChartLogger<double>>(chart, targ1,
                // Velocity PID controller. Takes in the velocity target from above
                std::make_shared<kappa::VPidSubController>(
                  kappa::VPidSubController::Gains{50,0,50,2000}, -12000, 12000,
                  // Feedback for the VPID controller. Log the actual velocity to the lvgl chart
                  std::make_shared<kappa::InputChartLogger<double>>(chart, read1,
                    // Differentiate the encoder values to calculate velocity
                    std::make_shared<kappa::InputDifferentiator<double>>(200.0/3.0,
                      // Wrapper on okapi's ContinuousRotarySensor
                      std::make_shared<kappa::OkapiInput>(std::make_shared<okapi::IntegratedEncoder>(19))
                    )
                  ),
                  // Output for the VPID controller. Logs the voltage command to cout
                  std::make_shared<kappa::OutputLogger<double>>(" M1 ", "\n",
                    // Wrapper on okapi's AbstractMotor
                    std::make_shared<kappa::VoltageMotor>(std::make_shared<okapi::Motor>(19))
                  )
                )
              ),
              // Branch 2, right: Log the target velocity to the lvgl chart
              std::make_shared<kappa::OutputChartLogger<double>>(chart, targ2,
                // Velocity PID controller. Takes in the velocity target from above
                std::make_shared<kappa::VPidSubController>(
                  kappa::VPidSubController::Gains{50,0,50,2000}, -12000, 12000,
                  // Feedback for the VPID controller. Log the actual velocity to the lvgl chart
                  std::make_shared<kappa::InputChartLogger<double>>(chart, read2,
                    // Differentiate the encoder values to calculate velocity
                    std::make_shared<kappa::InputDifferentiator<double>>(200.0/3.0,
                      // Wrapper on okapi's ContinuousRotarySensor
                      std::make_shared<kappa::OkapiInput>(std::make_shared<okapi::IntegratedEncoder>(20))
                    )
                  ),
                  // Output for the VPID controller. Logs the voltage command to cout
                  std::make_shared<kappa::OutputLogger<double>>(" M2 ", "\n",
                  // Wrapper on okapi's AbstractMotor
                    std::make_shared<kappa::VoltageMotor>(std::make_shared<okapi::Motor>(20))
                  )
                )
              )
            })
          )
        )
      )
    );

  // kappa::AbstractInput<double>
  // note: data flows from right to left in inputs
  input =
    // Log the encoder reading to cout
    std::make_shared<kappa::InputLogger<double>>(" Input Logger ", "\n",
      // Log the encoder reading to an lvgl gauge
      std::make_shared<kappa::InputGaugeLogger<double>>(gauge, 0,
        // Wrapper on okapi's ContinuousRotarySensor
        std::make_shared<kappa::OkapiInput>(
          std::make_shared<okapi::ADIEncoder>(3,4)
        )
      )
    );

  // just a simple pid controller
  controller =
    std::make_shared<kappa::PidController>(kappa::PidController::Gains{1,0,0.5,0});


  // a test/demonstration of the ArrayConsolidator, which merges multiple inputs to a
  // single array input. Expect to see this used in odometry in a later release.
  testInput =
    // Log values to cout
    std::make_shared<kappa::ArrayInputLogger<double,3>>(" Test InputArray ", " | ", "\n",
      // Merge three inputs into a single arrayInput
      std::make_shared<kappa::ArrayConsolidator<double,3>>(std::initializer_list<std::shared_ptr<kappa::AbstractInput<double>>>{
        // An encoder
        std::make_shared<kappa::OkapiInput>(std::make_shared<okapi::ADIEncoder>(3,4)),
        // An IMU
        std::make_shared<kappa::ImuInput>(11),
        // Just the system time ¯\_(ツ)_/¯
        std::make_shared<kappa::TimeInput>()
      })
    );

  // wait for the imu to calibrate
  pros::delay(2000);

  std::uint32_t now = pros::millis();
  std::tuple<double,double> target = {50,0};

  // note that this controller doesn't actually do anything useful
  // it is merely a demonstration of functionality
  while (true) {
    std::get<1>(target) = controller->step(input->get());
    chassis->set(target);

    std::cout << "\n";

    testInput->get();

    std::cout << "\n";

    pros::Task::delay_until(&now, 10);
  }

}
