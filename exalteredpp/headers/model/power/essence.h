#pragma once

#include "../thirdparty/serialisable/serialisable.hpp"

namespace power {
  class essence : public Serialisable
  {
  public:
    essence();

    unsigned int permanent_essence() const;
    void set_permanent_essence(unsigned int permanent_essence);

    unsigned int khan() const;
    void set_khan(unsigned int khan);

    unsigned int available_personal_essence() const;
    unsigned int available_peripheral_essence() const;
    unsigned int available_spiritual_essence() const;
    unsigned int total_personal_essence() const;
    unsigned int total_peripheral_essence() const;
    unsigned int total_spiritual_essence() const;
    unsigned int committed_personal_essence() const;
    unsigned int committed_peripheral_essence() const;
    unsigned int committed_spiritual_essence() const;

    void commit_essence(unsigned int commit_essence);
    void commit_spiritual_essence(unsigned int commit_essence);
    void decommit_essence(unsigned int commit_essence);
    void decommit_spiritual_essence(unsigned int commit_essence);

    bool can_spend_essence(unsigned int essence) const;
    bool can_spend_spiritual_essence(unsigned int essence) const;

    void spend_essence(unsigned int essence);
    void spend_spiritual_essence(unsigned int essence);
    void recover_essence(unsigned int essence);
    void recover_spiritual_essence(unsigned int essence);

    void set_bonus_personal_essence(unsigned int essence);
    void set_bonus_peripheral_essence(unsigned int essence);
    void set_bonus_spiritual_essence(unsigned int essence);

    void set_celestial_portion(unsigned int celestial_portion);
    unsigned int get_celestial_portion_percentage() const;
    unsigned int get_terrestrial_portion_percentage() const;

    void set_total_personal_essence(unsigned int total_personal_essence);
    void set_total_peripheral_essence(unsigned int total_peripheral_essence);
    void set_total_spiritual_essence(unsigned int total_spiritual_essence);

    virtual void serialisation() override;
    virtual ~essence();

  private:
    unsigned int
      _permanent_essence,
      _khan,
      _celestial_portion,
      _personal_committed_essence,
      _personal_spent_essence,
      _peripheral_committed_essence,
      _peripheral_spent_essence,
      _spiritual_committed_essence,
      _spiritual_spent_essence,
      _total_personal_essence,
      _total_peripheral_essence,
      _total_spiritual_essence,
      _bonus_personal_essence,
      _bonus_peripheral_essence,
      _bonus_spiritual_essence;

  };
}
