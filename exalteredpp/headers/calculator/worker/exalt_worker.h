#pragma once

#include "common_worker.h"

namespace calculator {
  namespace worker {

    class exalt_worker : public common_worker<round_up>
    {
    public:
      ~exalt_worker() override;

    protected:
      virtual double _persona(const character::character& c) const override;
      virtual double _natural_aggravated_soak(const character::character& c) const override;
    };

  }
}
