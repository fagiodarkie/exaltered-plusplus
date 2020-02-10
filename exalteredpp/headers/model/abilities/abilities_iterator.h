#ifndef ABILITIES_ITERATOR_H
#define ABILITIES_ITERATOR_H

#include "ability.h"
#include <vector>
#include <map>
#include <iterator>

namespace ability
{
  class abilities;

  template<typename ability_t, typename ability_map_t, typename ability_iter_t>
  class ability_iterator : public ability_iter_t
  {
  protected:
    typedef ability_iterator<ability_t, ability_map_t, ability_iter_t> _self_type_;
    typedef typename std::vector<ability_t>::difference_type _diff_type_;

  public:

    friend class abilities;

    // constructors
    ability_iterator(ability_map_t& map)
      : map_ref(map) { ptr = map.at(_first_filled_ability()).begin(); }

    ability_iterator(const _self_type_& o) = default;

    _self_type_& operator=(const _self_type_& o) = default;
    virtual ~ability_iterator() {}

    // iterator operators: boolean
    operator bool() { return ptr; }
    bool operator==(const _self_type_& o) { return ptr == o.ptr; }
    bool operator!=(const _self_type_& o) { return ptr != o.ptr; }

    // iterator operators: arithmetic
    virtual _self_type_& operator+=(_diff_type_& movement)
    {
      while(movement--)
        increase(ptr);
      return *this;
    }
    virtual _self_type_& operator-=(_diff_type_& movement)
    {
      while(movement--)
        decrease(ptr);
      return *this;
    }

    inline _self_type_& operator++()
    {
      increase(ptr);
      return *this;
    }
    inline _self_type_& operator--()
    {
      decrease(ptr);
      return *this;
    }
    inline _self_type_ operator++(int)
    {
      auto tmp(*this);
      increase(ptr);
      return tmp;
    }
    inline _self_type_ operator--(int)
    {
      auto tmp(*this);
      decrease(ptr);
      return tmp;
    }
    inline _self_type_ operator+(_diff_type_& movement)
    {
      auto tmp(*this);
      tmp += movement;
      return tmp;
    }
    inline _self_type_ operator-(_diff_type_& movement)
    {
      auto tmp(*this);
      tmp -= movement;
      return tmp;
    }

    virtual _diff_type_ operator-(const _self_type_& o)
    {
      if (ability_order_comparison(*ptr, *o.ptr))
        return diff(ptr, o.ptr);
      return diff(o.ptr, ptr);
    }

    // operators: access
    ability_t& operator*() { return *ptr; }
    const ability_t& operator*() const { return *ptr; }
    ability_iter_t& operator->() { return ptr; }
    const ability_iter_t& operator->() const { return ptr; }

    // TODO make it dynamic
    static const ability_enum LAST_ABILITY = ability_enum::TEACHING,
                              FIRST_ABILITY = ability_enum::MELEE;

  protected:
    _diff_type_ diff(ability_iter_t a1, ability_iter_t a2)
    {
      auto it = a1;
      _diff_type_ diff = 0;
      while (it != a2)
        {
          increase(it);
          ++diff;
        }

      return diff;
    }

    void increase(ability_iter_t& it)
    {
      if (it == map_ref.at(LAST_ABILITY).end())
        return;

      auto current_type = it->name().ability_type;
      ++it;
      if ((current_type != LAST_ABILITY) && it == map_ref.at(current_type).end())
        it = map_ref.at(current_type + 1).begin();
    }

    void decrease(ability_iter_t& it)
    {
      if (it == map_ref.at(FIRST_ABILITY).begin())
        return;

      if (it != map_ref.at(it->name().ability_type).begin())
        --it;
      else
        {
          it = map_ref.at(it->name().ability_type - 1).end();
          --it;
        }
    }

  private:
    ability_iter_t ptr;

    ability_map_t& map_ref;

    ability_enum _first_filled_ability() const
    {
      for (auto ability: ABILITIES)
        if (map_ref.find(ability) != map_ref.end()
            && !map_ref.at(ability).empty())
          return ability;
      return LAST_ABILITY;
    }

    ability_enum _next_filled_ability() const
    {
      auto cur_ability = ptr->name().ability_type;
      if (cur_ability == LAST_ABILITY)
        return LAST_ABILITY;

      for (auto ability = std::find(ABILITIES.begin(), ABILITIES.end(), cur_ability) + 1; ability != LAST_ABILITY; ++ability)
        if (map_ref.find(*ability) != map_ref.end()
            && !map_ref.at(ability).empty())
          return ability;
      return LAST_ABILITY;
    }

    ability_enum _last_filled_ability() const
    {
      auto res = LAST_ABILITY;

      for (auto ability: ABILITIES)
        if (map_ref.find(ability) != map_ref.end()
            && !map_ref.at(ability).empty())
          res = ability;

      return res;
    }
  };

}

#endif // ABILITIES_ITERATOR_H
