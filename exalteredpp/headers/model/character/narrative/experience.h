#ifndef EXPERIENCE_H
#define EXPERIENCE_H

#include "../../thirdparty/serialisable/serialisable.hpp"
#include "abilities/ability_names.h"
#include "attributes/attribute_names.h"
#include "virtues/virtue_names.h"

namespace character { namespace narrative {

    enum experience_expense_type {
      ATTRIBUTE, ABILITY, SPECIALISATION, CHARM, BACKGROUND, VIRTUE, VICE, WILLPOWER,
      DUENDE, JABBERWOCKY_ART, EXULTANCY
    };

    class experience : public Serialisable
    {
    public:
      experience();

      void serialisation() override;

      virtual ~experience();

    private:
      experience_expense_type _expense_type;
      attribute_names::attribute _attribute;
      ability_names::detailed_ability _ability;
      std::string _specialisation_name;
      virtues::virtue_enum _virtue;
      virtues::vice_enum _vice;
      unsigned int _upgrade_value;
    };

}  }

#endif // EXPERIENCE_H
