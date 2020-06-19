#pragma once

#include "kappa/input/abstractInput.hpp"
#include "kappa/util/tupleLogger.hpp"
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
    input(iinput), prefix(""), seperator(" "), postfix("\n"), out(std::cout) {}

  TupleInputLogger(int iprecision, std::string iprefix, std::string iseperator, std::string ipostfix, std::shared_ptr<AbstractInput<std::tuple<T...>>> iinput):
    input(iinput), prefix(iprefix), seperator(iseperator), postfix(ipostfix), out(std::cout) {

    out << std::setprecision(iprecision);
  }

  TupleInputLogger(int iprecision, std::string iprefix, std::string iseperator, std::string ipostfix, std::ostream &iout, std::shared_ptr<AbstractInput<std::tuple<T...>>> iinput):
    input(iinput), prefix(iprefix), seperator(iseperator), postfix(ipostfix), out(iout) {

    out << std::setprecision(iprecision);
  }

  virtual std::tuple<T...> get() const override {
    std::tuple<T...> values = input->get();

    out << prefix;

    printTuple(values, out, seperator);

    out << postfix;

    return values;
  }

  std::shared_ptr<AbstractInput<std::tuple<T...>>> getInput() const {
    return input;
  }

protected:
  std::shared_ptr<AbstractInput<std::tuple<T...>>> input{nullptr};

  std::string prefix;
  std::string seperator;
  std::string postfix;

  std::ostream &out;
};

}
