#pragma once

#include <QWidget>

#include "character.h"

namespace qt { namespace screen {
    class qcharacterexperience : public QWidget
    {
      Q_OBJECT
    public:
      explicit qcharacterexperience(std::shared_ptr<character::character> character, QWidget* parent = nullptr) {};


    private:
      std::shared_ptr<character::character> _character;

    };

} }


