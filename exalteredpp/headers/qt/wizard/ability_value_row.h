#ifndef ABILITY_VALUE_ROW_H
#define ABILITY_VALUE_ROW_H

#include <QFormLayout>
#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QMap>

#include "abilities/abilities.h"
#include "abilities/ability_names.h"
#include "exalt/exalt_caste.h"

using character::ability_group;

namespace qt {
  namespace wizard {
    class ability_value_row
    {
    public:
      ability_value_row(const ability_group& model_ability_group);
      void update(const ability_group& new_ability_group);

    private:

      ability_group _ability;
      void update_labels();

      static const char* REFERRED_ABILITY;
      static const char* REFERRED_SUB_ABILITY;
    };
  }
}

#endif // ABILITY_VALUE_ROW_H
