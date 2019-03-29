#pragma once

#include <QException>

namespace exception {
  class ability_not_found_exception : public QException
  {
  public:
    const char* what() const noexcept (true) override;
    void raise() const override;
    ability_not_found_exception *clone() const override;
  };
}

