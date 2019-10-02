#pragma once

#include "../thirdparty/serialisable/serialisable.hpp"
#include "philosophy.h"

#include <list>
#include "emotions_names.h"
#include "virtues/virtue_names.h"

namespace character {
  namespace social {
    class persona : public Serialisable
    {
    public:
      persona(unsigned int persona_points = 0, unsigned int compulsions = 0, unsigned int emotions = 0, unsigned int illusions = 0,
              unsigned int motivations = 0, unsigned int serfdom = 0, unsigned int max_philosophies = 1, unsigned int max_philosophy_value = 1);

      unsigned int get_persona              () const;
      unsigned int get_compulsions_specific () const;
      unsigned int get_emotions_specific    () const;
      unsigned int get_illusions_specific   () const;
      unsigned int get_motivations_specific () const;
      unsigned int get_serfdom_specific     () const;
      unsigned int get_max_philosophies     () const;
      unsigned int get_max_philosophy_value () const;

      std::vector<philosophy> philosophies() const;
      unsigned int get_emotion_bonus_for(emotion e) const;

      void set_persona              (unsigned int new_value);
      void set_compulsions_specific (unsigned int new_value);
      void set_emotions_specific    (unsigned int new_value);
      void set_illusions_specific   (unsigned int new_value);
      void set_motivations_specific (unsigned int new_value);
      void set_serfdom_specific     (unsigned int new_value);
      void set_max_philosophies     (unsigned int new_value);
      void set_max_philosophy_value (unsigned int new_value);

      void set_base_emotion_bonus(emotion e, unsigned int base_bonus);
      void add_philosophy(const philosophy &p);
      void increase_philosophy(std::string philosophy_name, unsigned int increment = 1);
      void decrease_philosophy(std::string philosophy_name, unsigned int decrement = 1);

      virtual void serialisation() override;
      virtual ~persona();

    private:
      unsigned int
        _persona,
        _compulsions_specific,
        _emotions_specific,
        _illusions_specific,
        _motivations_specific,
        _serfdom_specific,
        _max_philosophies,
        _max_philosophy_value;


      std::vector<philosophy>::iterator find_philosophy(const std::string& philosophy_name);
      std::map<emotion, unsigned int> _emotion_bonus;
      std::vector<philosophy> _philosophies;
    };
  }
}

