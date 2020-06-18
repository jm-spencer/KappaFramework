#pragma once

#include "kappa/input/abstractInput.hpp"
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
  TupleInputLogger(std::shared_ptr<AbstractInput<std::tuple<T...>>> iinput, int iprecision = 6, std::string iprefix = "", std::string iseperator = " ", std::string ipostfix = "\n", std::ostream &iout = std::cout):
    input(iinput), prefix(iprefix), seperator(iseperator), postfix(ipostfix), out(iout) {

    out << std::setprecision(iprecision);
  }

  virtual std::tuple<T...> get() const override {
    std::tuple<T...> values = input->get();

    out << prefix;

    for(auto &i : values){
      out << i << seperator;
    }

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
