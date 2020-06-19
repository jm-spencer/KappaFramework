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
    output(ioutput), prefix(""), seperator(" "), postfix("\n"), out(std::cout) {}

  TupleOutputLogger(int iprecision, std::string iprefix, std::string iseperator, std::string ipostfix, std::shared_ptr<AbstractOutput<std::tuple<T...>>> ioutput):
    output(ioutput), prefix(iprefix), seperator(iseperator), postfix(ipostfix), out(std::cout) {

    out << std::setprecision(iprecision);
  }

  TupleOutputLogger(int iprecision, std::string iprefix, std::string iseperator, std::string ipostfix, std::ostream &iout, std::shared_ptr<AbstractOutput<std::tuple<T...>>> ioutput):
    output(ioutput), prefix(iprefix), seperator(iseperator), postfix(ipostfix), out(iout) {

    out << std::setprecision(iprecision);
  }

  virtual void set(const std::tuple<T...> &iTarget) override {
    out << prefix;

    printTuple(iTarget, out, seperator);

    out << postfix;

    output->set(iTarget);
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

}
