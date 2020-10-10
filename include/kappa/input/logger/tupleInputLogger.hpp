#pragma once

#include "kappa/input/abstractInput.hpp"
#include "kappa/util/tupleLogger.hpp"
#include "pros/rtos.hpp"
#include <memory>
#include <tuple>
#include <ostream>
#include <iostream>
#include <iomanip>
#include <string>

namespace kappa {

template <typename... T>
class TupleInputLogger : public AbstractInput<std::tuple<T...>> {
public:
  TupleInputLogger(std::shared_ptr<AbstractInput<std::tuple<T...>>> iinput):
    TupleInputLogger(", ", ", ", "\n", std::cout, iinput) {}

  TupleInputLogger(std::string iprefix, std::string iseparator, std::string ipostfix, std::shared_ptr<AbstractInput<std::tuple<T...>>> iinput):
    TupleInputLogger(prefix, iseparator, ipostfix, std::cout, iinput) {}

  TupleInputLogger(std::string iprefix, std::string iseparator, std::string ipostfix, std::ostream &iout, std::shared_ptr<AbstractInput<std::tuple<T...>>> iinput):
    input(iinput), prefix(iprefix), separator(iseparator), postfix(ipostfix), out(iout) {}

  virtual const std::tuple<T...> &get() override {
    const std::tuple<T...> &values = input->get();

    out << pros::millis() << prefix;

    printTuple(values, out, separator);

    out << postfix;

    return values;
  }

  std::shared_ptr<AbstractInput<std::tuple<T...>>> getInput() const {
    return input;
  }

protected:
  std::shared_ptr<AbstractInput<std::tuple<T...>>> input{nullptr};

  std::string prefix;
  std::string separator;
  std::string postfix;

  std::ostream &out;
};

}
