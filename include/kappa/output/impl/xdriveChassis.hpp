#pragma once

#include "kappa/output/abstractOutput.hpp"
#include <tuple>
#include <memory>


namespace kappa {

class XDriveChassis : public AbstractOutput<std::tuple<double,double,double>> {
public:

  /**
   * Chassis object for a chassis with 3 degrees of freedom (holonomic)
   * Converts an target signal of (forward, left, ccw)
   * to an signal of (frontLeft, backLeft, backRight, frontRight)
   * for an X-drive chassis
   *
   * @param ichassis array of motors in format (frontLeft, backLeft, backRight, frontRight)
   */
  XDriveChassis(std::shared_ptr<AbstractOutput<std::array<double,4>>> ichassis);

  /**
   * Chassis object for a chassis with 3 degrees of freedom (holonomic)
   * Converts an target signal of (forward, left, ccw) in units of (in/s, in/s, rad/s)
   * to an signal of (frontLeft, backLeft, backRight, frontRight) in units of rpm
   * for an X-drive chassis
   *
   * @param iwheelDiameter diameter of wheel in inches
   * @param ichassisWidth distance between opposite corner wheels in inches
   * @param ichassis array of motors in format (frontLeft, backLeft, backRight, frontRight)
   */

  XDriveChassis(double iwheelDiameter, double ichassisWidth, std::shared_ptr<AbstractOutput<std::array<double,4>>> ichassis);

  /**
   * Calculates target values for each motor and sets their respective targets
   *
   * @param itarget target values
   */
  virtual void set(const std::tuple<double,double,double> &itarget) override;

  /**
   * Using a polar target signal of (velocity, direction, rotation),
   * calculates target values for each motor and sets their respective targets
   *
   * @param itarget target values
   */
  void setPolar(const std::tuple<double,double,double> &itarget);


  /**
   * Gets output
   *
   * @return output
   */
  std::shared_ptr<AbstractOutput<std::array<double,4>>> getOutput() const;

protected:
  std::shared_ptr<AbstractOutput<std::array<double,4>>> chassis{nullptr};
  double linearScalar{0};
  double angularScalar{0};
};

}
