#include "social/persona.h"

#include "serialisation/json_constants.h"
#include "errors/invalid_parameter.h"

#include <QJsonArray>

namespace character {
  namespace social {

    persona::persona(unsigned int persona_points, unsigned int compulsions, unsigned int emotions, unsigned int illusions,
                     unsigned int motivations, unsigned int serfdom, unsigned int max_philosophies, unsigned int max_philosophy_value)
      : _persona(persona_points),
        _compulsions_specific(compulsions),
        _emotions_specific(emotions),
        _illusions_specific(illusions),
        _motivations_specific(motivations),
        _serfdom_specific(serfdom),
        _max_philosophies(max_philosophies),
        _max_philosophy_value(max_philosophy_value) { }

    unsigned int persona::get_persona              () const
    {
      return _persona;
    }

    unsigned int persona::get_compulsions_specific () const
    {
      return _compulsions_specific;
    }

    unsigned int persona::get_emotions_specific    () const
    {
      return _emotions_specific;
    }

    unsigned int persona::get_illusions_specific   () const
    {
      return _illusions_specific;
    }

    unsigned int persona::get_motivations_specific () const
    {
      return _motivations_specific;
    }

    unsigned int persona::get_serfdom_specific() const
    {
      return _serfdom_specific;
    }

    unsigned int persona::get_max_philosophies     () const
    {
      return _max_philosophies;
    }

    unsigned int persona::get_max_philosophy_value () const
    {
      return _max_philosophy_value;
    }

    void persona::set_persona              (unsigned int new_value)
    {
      _persona = new_value;
    }

    void persona::set_compulsions_specific (unsigned int new_value)
    {
      _compulsions_specific = new_value;
    }

    void persona::set_emotions_specific    (unsigned int new_value)
    {
      _emotions_specific = new_value;
    }

    void persona::set_illusions_specific   (unsigned int new_value)
    {
      _illusions_specific = new_value;
    }

    void persona::set_motivations_specific (unsigned int new_value)
    {
      _motivations_specific = new_value;
    }

    void persona::set_serfdom_specific     (unsigned int new_value)
    {
      _serfdom_specific = new_value;
    }

    void persona::set_max_philosophies     (unsigned int new_value)
    {
      _max_philosophies = new_value;
    }

    void persona::set_max_philosophy_value (unsigned int new_value)
    {
      _max_philosophy_value = new_value;
    }

    QList<philosophy> persona::philosophies() const
    {
      return _philosophies;
    }

    unsigned int persona::get_emotion_bonus_for(emotion e) const
    {
      if (BASE_EMOTIONS.contains(e))
        return _emotion_bonus[e];

      emotion base_emotion = BASE_EMOTION_OF(e);
      unsigned int multiplier = INTIMATE_EMOTIONS.contains(e) ? 3 : 2;
      return _emotion_bonus[base_emotion] * multiplier;
    }

    void persona::set_base_emotion_bonus(emotion e, unsigned int base_bonus)
    {
      if (!BASE_EMOTIONS.contains(e))
        throw new exception::invalid_parameter();

      _emotion_bonus[e] = base_bonus;
    }

    void persona::add_philosophy(const philosophy &p)
    {
      if (_philosophies.size() == _max_philosophies)
        throw new exception::invalid_parameter();

      _philosophies.append(p);
    }

    void persona::increase_philosophy(QString philosophy_name, unsigned int increment)
    {
      auto philosophy_pointer = std::find_if(_philosophies.begin(), _philosophies.end(),
                                             [philosophy_name](const philosophy& current_p) {
          return current_p.name() == philosophy_name;
        });

      if (philosophy_pointer == _philosophies.end())
        throw new exception::invalid_parameter();

      philosophy_pointer->set_value(std::min(philosophy_pointer->value() + increment, _max_philosophy_value));
    }

    void persona::decrease_philosophy(QString philosophy_name, unsigned int decrement)
    {
      auto philosophy_pointer = std::find_if(_philosophies.begin(), _philosophies.end(),
                                             [philosophy_name](const philosophy& current_p) {
          return current_p.name() == philosophy_name;
        });

      if (philosophy_pointer == _philosophies.end())
        throw new exception::invalid_parameter();

      if (philosophy_pointer->value() <= decrement)
        {
          _philosophies.removeOne(*philosophy_pointer);
        }

      philosophy_pointer->set_value(philosophy_pointer->value() - decrement);
    }

    void persona::read_from_json(const QJsonObject &json)
    {
      _persona              = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_PERSONA             ].toString().toInt());
      _compulsions_specific = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_COMPULSIONS_SPECIFIC].toString().toInt());
      _emotions_specific    = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_EMOTIONS_SPECIFIC   ].toString().toInt());
      _illusions_specific   = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_ILLUSIONS_SPECIFIC  ].toString().toInt());
      _motivations_specific = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_MOTIVATIONS_SPECIFIC].toString().toInt());
      _serfdom_specific     = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_SERFDOM_SPECIFIC    ].toString().toInt());
      _max_philosophies     = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_MAX_PHILOSOPHIES    ].toString().toInt());
      _max_philosophy_value = static_cast<unsigned int>(json[serialisation::json_constants::SLOT_MAX_PHILOSOPHY_VALUE].toString().toInt());

      QJsonObject emotion_bonus = json[serialisation::json_constants::SLOT_EMOTION_BONUS].toObject();
      QJsonArray philosophies_obj = json[serialisation::json_constants::SLOT_PHILOSOPHIES].toArray();
      for (int i = 0; i < philosophies_obj.size(); ++i)
        {
          philosophy p;
          p.read_from_json(philosophies_obj[i].toObject());
          _philosophies.insert(i, p);
        }

      for (auto emotion: BASE_EMOTIONS)
        {
          _emotion_bonus[emotion] = static_cast<unsigned int>(emotion_bonus[NAME_OF_EMOTION[emotion]].toString().toInt());
        }
    }

    void persona::write_to_json(QJsonObject &json) const
    {
      json[serialisation::json_constants::SLOT_PERSONA             ] = QString::number(_persona             );
      json[serialisation::json_constants::SLOT_COMPULSIONS_SPECIFIC] = QString::number(_compulsions_specific);
      json[serialisation::json_constants::SLOT_EMOTIONS_SPECIFIC   ] = QString::number(_emotions_specific   );
      json[serialisation::json_constants::SLOT_ILLUSIONS_SPECIFIC  ] = QString::number(_illusions_specific  );
      json[serialisation::json_constants::SLOT_MOTIVATIONS_SPECIFIC] = QString::number(_motivations_specific);
      json[serialisation::json_constants::SLOT_SERFDOM_SPECIFIC    ] = QString::number(_serfdom_specific    );
      json[serialisation::json_constants::SLOT_MAX_PHILOSOPHIES    ] = QString::number(_max_philosophies    );
      json[serialisation::json_constants::SLOT_MAX_PHILOSOPHY_VALUE] = QString::number(_max_philosophy_value);

      QJsonObject emotion_bonus; QJsonArray philosophies_obj;
      for (int i = 0; i < _philosophies.size(); ++i)
        {
          QJsonObject p;
          _philosophies[i].write_to_json(p);
          philosophies_obj.insert(i, p);
        }
      json[serialisation::json_constants::SLOT_PHILOSOPHIES] = philosophies_obj;

      for (auto emotion: BASE_EMOTIONS)
        {
          emotion_bonus[NAME_OF_EMOTION[emotion]] = QString::number(get_emotion_bonus_for(emotion));
        }
      json[serialisation::json_constants::SLOT_EMOTION_BONUS] = emotion_bonus;

    }

    persona::~persona() {}
  }
}
