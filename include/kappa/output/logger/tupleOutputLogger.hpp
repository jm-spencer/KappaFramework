#pragma once

#include "kappa/output/abstractOutput.hpp"
#include "kappa/util/tupleLogger.hpp"
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
  TupleOutputLogger(std::shared_ptr<AbstractOutput<std::tuple<T...>>> ioutput):
    TupleOutputLogger(6, "", " ", "\n", std::cout, ioutput) {}

  TupleOutputLogger(int iprecision, std::string iprefix, std::string iseperator, std::string ipostfix, std::shared_ptr<AbstractOutput<std::tuple<T...>>> ioutput):
    TupleOutputLogger(iprecision, iprefix, iseperator, ipostfix, std::cout, ioutput) {}

  TupleOutputLogger(int iprecision, std::string iprefix, std::string iseperator, std::string ipostfix, std::ostream &iout, std::shared_ptr<AbstractOutput<std::tuple<T...>>> ioutput):
    output(ioutput), prefix(iprefix), seperator(iseperator), postfix(ipostfix), out(iout) {

    out << std::setprecision(iprecision);
  }

  virtual void set(const std::tuple<T...> &itarget) override {
    out << pros::millis() << prefix;

    printTuple(itarget, out, seperator);

    out << postfix;

    output->set(itarget);
  }

  std::shared_ptr<AbstractOutput<std::tuple<T...>>> getOutput() const {
    return output;
  };

protected:
  std::shared_ptr<AbstractOutput<std::tuple<T...>>> output{nullptr};

  std::string prefix;
  std::string seperator;
  std::string postfix;

  std::ostream &out;
};

extern template class TupleOutputLogger<double,double>;
extern template class TupleOutputLogger<double,double,double>;

}
