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

    std::vector<philosophy> persona::philosophies() const
    {
      return _philosophies;
    }

    unsigned int persona::get_emotion_bonus_for(emotion e) const
    {
      if (commons::contains(BASE_EMOTIONS, e))
        return _emotion_bonus.at(e);

      emotion base_emotion = BASE_EMOTION_OF(e);
      unsigned int multiplier = commons::contains(INTIMATE_EMOTIONS, e) ? 3 : 2;
      return _emotion_bonus.at(base_emotion) * multiplier;
    }

    void persona::set_base_emotion_bonus(emotion e, unsigned int base_bonus)
    {
      if (!commons::contains(BASE_EMOTIONS, e))
        throw new exception::invalid_parameter();

      _emotion_bonus[e] = base_bonus;
    }

    void persona::add_philosophy(const philosophy &p)
    {
      if (_philosophies.size() == _max_philosophies)
        throw new exception::invalid_parameter();

      _philosophies.push_back(p);
    }

    void persona::increase_philosophy(std::string philosophy_name, unsigned int increment)
    {
      auto philosophy_pointer = std::find_if(_philosophies.begin(), _philosophies.end(),
                                             [philosophy_name](const philosophy& current_p) {
          return current_p.name() == philosophy_name;
        });

      if (philosophy_pointer == _philosophies.end())
        throw new exception::invalid_parameter();

      philosophy_pointer->set_value(std::min(philosophy_pointer->value() + increment, _max_philosophy_value));
    }

    void persona::decrease_philosophy(std::string philosophy_name, unsigned int decrement)
    {
      auto philosophy_pointer = std::find_if(_philosophies.begin(), _philosophies.end(),
                                             [philosophy_name](const philosophy& current_p) {
          return current_p.name() == philosophy_name;
        });

      if (philosophy_pointer == _philosophies.end())
        throw new exception::invalid_parameter();

      if (philosophy_pointer->value() <= decrement)
        {
          _philosophies.erase(philosophy_pointer);
        }

      philosophy_pointer->set_value(philosophy_pointer->value() - decrement);
    }

    void persona::serialisation()
    {
      synch(serialisation::json_constants::SLOT_PERSONA             , _persona             );
      synch(serialisation::json_constants::SLOT_COMPULSIONS_SPECIFIC, _compulsions_specific);
      synch(serialisation::json_constants::SLOT_EMOTIONS_SPECIFIC   , _emotions_specific   );
      synch(serialisation::json_constants::SLOT_ILLUSIONS_SPECIFIC  , _illusions_specific  );
      synch(serialisation::json_constants::SLOT_MOTIVATIONS_SPECIFIC, _motivations_specific);
      synch(serialisation::json_constants::SLOT_SERFDOM_SPECIFIC    , _serfdom_specific    );
      synch(serialisation::json_constants::SLOT_MAX_PHILOSOPHIES    , _max_philosophies    );
      synch(serialisation::json_constants::SLOT_MAX_PHILOSOPHY_VALUE, _max_philosophy_value);
      synch(serialisation::json_constants::SLOT_PHILOSOPHIES        , _philosophies        );
      for (auto emotion: BASE_EMOTIONS)
        synch(NAME_OF_EMOTION.at(emotion), _emotion_bonus[emotion]);
    }

    persona::~persona() {}
  }
}
