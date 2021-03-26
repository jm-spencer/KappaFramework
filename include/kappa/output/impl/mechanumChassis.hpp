#pragma once

#include "kappa/output/abstractOutput.hpp"
#include <tuple>
#include <memory>


namespace kappa {

class MechanumChassis : public AbstractOutput<std::tuple<double,double,double>> {
public:

  /**
   * Chassis object for a chassis with 3 degrees of freedom (holonomic)
   * Converts an target signal of (forward, left, ccw)
   * to an signal of (frontLeft, backLeft, backRight, frontRight)
   * for an mechanum wheeled chassis
   *
   * @param ichassis array of motors in format (frontLeft, backLeft, backRight, frontRight)
   */
  MechanumChassis(std::shared_ptr<AbstractOutput<std::array<double,4>>> ichassis);

  /**
   * Chassis object for a chassis with 3 degrees of freedom (holonomic)
   * Converts an target signal of (forward, left, ccw) in units of (in/s, in/s, rad/s)
   * to an signal of (frontLeft, backLeft, backRight, frontRight) in units of rpm
   * for an X-drive like chassis
   *
   * @param iwheelDiameter diameter of wheel in inches
   * @param iwheelDistance distance from center of robot to a wheel in inches
   *    calculate with sqrt( (chassisWidth/2)^2 + (chassisLength/2)^2 )
   *    higher values makes robot react more sensitive to turning commands
   * @param ichassis array of motors in format (frontLeft, backLeft, backRight, frontRight)
   */

  MechanumChassis(double iwheelDiameter, double iwheelDistance, std::shared_ptr<AbstractOutput<std::array<double,4>>> ichassis);

  /**
   * Calculates target values for each motor and sets their respective targets
   *
   * @param itarget target values
   */
  virtual void set(const std::tuple<double,double,double> &itarget) override;

  /**
   * Send a stop command to the lowermost level of the output
   * eg. idle the motor, as opposed to trying to hold vel = 0
   */
  virtual void stop() override;

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
