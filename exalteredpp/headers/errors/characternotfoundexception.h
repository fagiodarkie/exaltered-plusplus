#pragma once

#include <QException>

namespace exception {
  class CharacterNotFoundException : public QException
  {
  public:
    void raise() const override;
    CharacterNotFoundException *clone() const override;
  };

}

