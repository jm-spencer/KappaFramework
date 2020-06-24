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
  OutputLogger(std::shared_ptr<AbstractOutput<T>> ioutput):
    output(ioutput), prefix(""), postfix("\n"), out(std::cout) {}

  OutputLogger(int iprecision, std::string iprefix, std::string ipostfix, std::shared_ptr<AbstractOutput<T>> ioutput):
    output(ioutput), prefix(iprefix), postfix(ipostfix), out(std::cout) {

    out << std::setprecision(iprecision);
  }

  OutputLogger(int iprecision, std::string iprefix, std::string ipostfix, std::ostream &iout, std::shared_ptr<AbstractOutput<T>> ioutput):
    output(ioutput), prefix(iprefix), postfix(ipostfix), out(iout) {

    out << std::setprecision(iprecision);
  }

  virtual void set(const T &iTarget) override {
    out << prefix << iTarget << postfix;
    output->set(iTarget);
  }

  std::shared_ptr<AbstractOutput<T>> getOutput() const {
    return output;
  };

protected:
  std::shared_ptr<AbstractOutput<T>> output{nullptr};

  std::string prefix;
  std::string postfix;

  std::ostream &out;
};

extern template class OutputLogger<double>;

}
