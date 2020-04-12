#pragma once

#include "abstractInput.hpp"
#include "abstractOutput.hpp"
#include "okapi/api/util/logging.hpp"
#include "okapi/api/control/util/settledUtil.hpp"
#include <memory>


namespace kappa {

template <typename IN, typename TARGET, typename OUT>
class AbstractController : public AbstractOutput<TARGET>{
public:
  virtual void setTarget(TARGET itarget) = 0;

  virtual TARGET getTarget() const {
    return target;
  };

  virtual OUT step(IN ireading) = 0;

  virtual OUT getOutput() const {
    return isDisabled() ? 0 : output;
  };

  virtual void setOutputLimits(OUT imin, OUT imax) {
    outputMin = imin;
    outputMax = imax;
  }

  virtual OUT getMinOutput() const {
    return outputMin;
  }

  virtual OUT getMaxOutput() const {
    return outputMax;
  }

  virtual IN getLastInput() const {
    return lastReading;
  }

  virtual IN getError() const {
    return error;
  }

  virtual bool isSettled() {
    return isDisabled() ? true : settledUtil->isSettled(error);
  };

  virtual void waitUntilSettled(uint32_t timestep = 10) {
    while(!isSettled()){
      pros::delay(timestep);
    }
  }

  virtual void reset() = 0;

  virtual void disable(bool iisDisabled) = 0;

  virtual bool isDisabled() const {
      return disabled;
  }

protected:
  TARGET target;
  IN lastReading;
  IN error;
  IN lastError;

  OUT output;
  OUT outputMax;
  OUT outputMin;

  bool disabled{false};

  std::shared_ptr<okapi::Logger> logger;
  std::unique_ptr<okapi::SettledUtil> settledUtil;
};

}
