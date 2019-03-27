#pragma once

#include <QJsonObject>

class serialisable
{
public:
  virtual void read_from_json(const QJsonObject &json) = 0;
  virtual void write_to_json(QJsonObject &json) const = 0;
protected:
  ~serialisable() = default;
};
