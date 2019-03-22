#pragma once

#include "serialisable.h"
#include <QMap>

namespace model {
  class character_list : public serialisable
  {
  public:
    character_list();

    // serialisable interface
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

    virtual ~character_list() = default;

  private:
    QMap<QString, QString> characters;
  };
}

