#pragma once

#include "abstractInput.hpp"
#include <memory>
#include <ostream>
#include <iostream>
#include <iomanip>
#include <string>

namespace kappa {

template <typename T>
class InputLogger : public AbstractInput<T> {
public:
  InputLogger(std::shared_ptr<AbstractInput<T>> iinput, int iprecision = 6, std::string iprefix = "", std::string ipostfix = "\n", std::ostream &iout = std::cout):
    input(iinput), prefix(iprefix), postfix(ipostfix), out(iout) {

    out << std::setprecision(iprecision);
  }

  virtual T get() const override {
    T value = input->get();
    out << prefix << value << postfix;
    return value;
  }

protected:
  std::shared_ptr<AbstractInput<T>> input{nullptr};

  std::string prefix;
  std::string postfix;

  std::ostream &out;
};

}
