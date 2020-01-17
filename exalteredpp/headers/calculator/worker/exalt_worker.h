#pragma once

#include "common_worker.h"

namespace calculator {
  namespace worker {

    class exalt_worker : public common_worker<round_up>
    {
    public:
      ~exalt_worker() override;

    protected:
      virtual long int _persona(const character::creation::character_type& type,
                                       const attribute::attributes& attribute,
                                       const power::willpower& willpower,
                                       const power::essence& essence) const override;

      virtual double _natural_aggravated_soak(const character::character& c) const override;

      virtual double _lethal_soak(const character::character& c) const override;
    };

  }
}
