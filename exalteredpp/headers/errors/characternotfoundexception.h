#pragma once

#include <QException>

namespace exception {
  class character_not_found_exception : public QException
  {
  public:

    const char* what() const override;
    void raise() const override;
    character_not_found_exception *clone() const override;
  };

}

