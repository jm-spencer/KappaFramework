#include "main.h"
#include "kappa/api.hpp"
#include "okapi/api.hpp"

void initialize() {
  okapi::Logger::setDefaultLogger(std::make_shared<okapi::Logger>(std::make_unique<okapi::Timer>(), "/ser/sout", okapi::Logger::LogLevel::debug));
}

void disabled() {}

void competition_initialize() {}

void autonomous() {}

std::shared_ptr<kappa::TupleOutputLogger<double,double>> chassis;
std::shared_ptr<kappa::InputLogger<double>> input;
std::shared_ptr<kappa::PidController> controller;

void opcontrol() {
  auto chart = lv_chart_create(lv_scr_act(), NULL);
  lv_obj_set_pos(chart, 0, 0);
  lv_obj_set_size(chart, 480, 120);
  lv_chart_set_type(chart, LV_CHART_TYPE_LINE);
  lv_chart_set_range(chart, -12000, 12000);
  lv_chart_set_point_count(chart, 240);
  auto ser1 = lv_chart_add_series(chart, LV_COLOR_RED);
  auto ser2 = lv_chart_add_series(chart, LV_COLOR_BLUE);

  auto gauge = lv_gauge_create(lv_scr_act(), NULL);
  lv_obj_set_size(gauge, 120, 120);
  lv_obj_set_pos(gauge, 0, 120);
  lv_gauge_set_range(gauge, -110, 110);
  lv_gauge_set_critical_value(gauge, 200);
  static lv_color_t ncolor[] = {LV_COLOR_RED};
  lv_gauge_set_needle_count(gauge, 1, ncolor);

  chassis =
    std::make_shared<kappa::TupleOutputLogger<double,double>>(6, " Tuple Logger ", " | ", "\n",
      std::make_shared<kappa::TwoAxisChassis>(4, 10,
        std::make_shared<kappa::ArrayOutputClamp<double,2>>(-100, 100,
          std::make_shared<kappa::ArrayOutputLogger<double,2>>(6, " Array Logger ", " | ", "\n",
            std::make_shared<kappa::ArrayDistributor<double,2>>(
              kappa::ArrayDistributor<double,2>({
                std::make_shared<kappa::VPidSubController>(
                  kappa::VPidSubController::Gains{50,0,50,2000}, -12000, 12000,
                  std::make_shared<kappa::InputDifferentiator<double>>(20.0/3.0,
                    std::make_shared<kappa::OkapiInput>(std::make_shared<okapi::IntegratedEncoder>(19))
                  ),
                  std::make_shared<kappa::OutputChartLogger<double>>(chart, ser1,
                    std::make_shared<kappa::OutputLogger<double>>(6, " M1 ", "\n",
                      std::make_shared<kappa::VoltageMotor>(std::make_shared<okapi::Motor>(19))
                    )
                  )
                ),
                std::make_shared<kappa::VPidSubController>(
                  kappa::VPidSubController::Gains{50,0,50,2000}, -12000, 12000,
                  std::make_shared<kappa::InputDifferentiator<double>>(20.0/3.0,
                    std::make_shared<kappa::OkapiInput>(std::make_shared<okapi::IntegratedEncoder>(20))
                  ),
                  std::make_shared<kappa::OutputChartLogger<double>>(chart, ser2,
                    std::make_shared<kappa::OutputLogger<double>>(6, " M2 ", "\n",
                      std::make_shared<kappa::VoltageMotor>(std::make_shared<okapi::Motor>(20))
                    )
                  )
                ),
              })
            )
          )
        )
      )
    );

  input =
    std::make_shared<kappa::InputLogger<double>>(6, " Input Logger ", "\n",
      std::make_shared<kappa::InputGaugeLogger<double>>(gauge, 0,
        std::make_shared<kappa::OkapiInput>(
          std::make_shared<okapi::ADIEncoder>(3,4)
        )
      )
    );

  controller =
    std::make_shared<kappa::PidController>(kappa::PidController::Gains{1,0,0.5,0});


  pros::Task testController([&] {
    std::uint32_t now = pros::millis();
    std::tuple<double,double> target = {50,0};

    while (true) {
      std::get<1>(target) = controller->step(input->get());
      chassis->set(target);

      std::cout << "\n";

      pros::Task::delay_until(&now, 10);
    }

  }, "Test Controller");

  while(true) {
    pros::delay(10);
  }

}
