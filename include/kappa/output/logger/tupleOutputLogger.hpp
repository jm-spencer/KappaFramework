#pragma once

#include "abstractOutput.hpp"
#include <memory>
#include <tuple>
#include <ostream>
#include <iostream>
#include <iomanip>
#include <string>

namespace kappa {

template <typename... T>
class TupleOutputLogger : public AbstractOutput<std::tuple<T...>> {
public:
  TupleOutputLogger(std::shared_ptr<AbstractOutput<std::tuple<T...>>> ioutput, int iprecision = 6, std::string iprefix = "", std::string iseperator = " ", std::string ipostfix = "\n", std::ostream &iout = std::cout):
    output(ioutput), prefix(iprefix), seperator(iseperator), postfix(ipostfix), out(iout) {

    out << std::setprecision(iprecision);
  }

  virtual void set(std::tuple<T...> iTarget) override {
    out << prefix;

    for(auto &i : iTarget){
      out << i << seperator;
    }

    out << postfix;

    output->set(iTarget);
  }

protected:
  std::shared_ptr<AbstractOutput<std::tuple<T...>>> output{nullptr};

  std::string prefix;
  std::string seperator;
  std::string postfix;

  std::ostream &out;
};

}