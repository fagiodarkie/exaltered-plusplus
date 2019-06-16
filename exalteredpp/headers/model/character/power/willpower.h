#pragma once

namespace character {
  namespace power {
    class willpower
    {
    public:
      willpower();

      unsigned int temporary_willpower() const;

      unsigned int permanent_willpower() const;



    private:
      unsigned int _permanent_willpower, _temporary_willpower;
    };
  }
}

