#include <QJsonObject>

#pragma once

class serialisable {
public:
    virtual void read(QJsonObject &json) = 0;
    virtual void write(QJsonObject &json) const = 0;
    virtual ~serialisable();
};
