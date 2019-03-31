#pragma once

#include <QException>

namespace exception {
  class invalid_parameter : public QException
  {
  public:
    const char* what() const noexcept (true) override;
    void raise() const override;
    invalid_parameter *clone() const override;
  };

}

