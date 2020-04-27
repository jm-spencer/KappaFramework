#pragma once

#include "abstractInput.hpp"
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
  TupleInputLogger(std::shared_ptr<AbstractInput<std::tuple<T...>>> iInput, int iprecision = 6, std::string iprefix = "", std::string iseperator = " ", std::string ipostfix = "\n", std::ostream &iout = std::cout):
    Input(iInput), prefix(iprefix), seperator(iseperator), postfix(ipostfix), out(iout) {

    out << std::setprecision(iprecision);
  }

  virtual std::tuple<T...> get() override {
    std::tuple<T...> values = Input->get();

    out << prefix;

    for(auto &i : values){
      out << i << seperator;
    }

    out << postfix;

    return values;
  }

protected:
  std::shared_ptr<AbstractInput<std::tuple<T...>>> Input{nullptr};

  std::string prefix;
  std::string seperator;
  std::string postfix;

  std::ostream &out;
};

}
