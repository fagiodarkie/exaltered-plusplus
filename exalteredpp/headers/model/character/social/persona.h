#pragma once

#include "serialisable.h"
#include "philosophy.h"
#include "emotions_names.h"
#include "virtues/virtue_names.h"

namespace character {
  namespace social {
    class persona : public serialisable
    {
    public:
      void read_from_json(const QJsonObject &json);
      void write_to_json(QJsonObject &json) const;



      ~persona();

    private:
      unsigned int
        _persona,
        _compulsions_specific,
        _emotions_specific,
        _illusions_specific,
        _motivations_specific,
        _max_philosophies,
        _max_philosophy_value;

      QMap<virtues::virtue_enum, unsigned int> _max_emotion_bonus;
      QMap<emotion, unsigned int> _emotion_bonus;
      QList<philosophy> _philosophies;
    };
  }
}

