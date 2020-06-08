#pragma once

#include "kappa/output/abstractOutput.hpp"
#include <memory>
#include <ostream>
#include <iostream>
#include <iomanip>
#include <string>

namespace kappa {

template <typename T>
class OutputLogger : public AbstractOutput<T> {
public:
  OutputLogger(std::shared_ptr<AbstractOutput<T>> ioutput, int iprecision = 6, std::string iprefix = "", std::string ipostfix = "\n", std::ostream &iout = std::cout):
    output(ioutput), prefix(iprefix), postfix(ipostfix), out(iout) {

    out << std::setprecision(iprecision);
  }

  virtual void set(T iTarget) override {
    out << prefix << iTarget << postfix;
    output->set(iTarget);
  }

protected:
  std::shared_ptr<AbstractOutput<T>> output{nullptr};

  std::string prefix;
  std::string postfix;

  std::ostream &out;
};

}
