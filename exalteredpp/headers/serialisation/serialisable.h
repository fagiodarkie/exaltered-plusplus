#pragma once

#include <QJsonObject>

class serialisable
{
public:
  virtual void read(const QJsonObject &json) = 0;
  virtual void write(QJsonObject &json) const = 0;
protected:
  ~serialisable() = default;
};
