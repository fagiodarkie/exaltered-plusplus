#pragma once

#include "../thirdparty/serialisable/serialisable.hpp"

namespace character {
  namespace social {

    class philosophy : public Serialisable
    {
    public:
      philosophy(std::string name = "", unsigned int value = 1);

      std::string name() const;
      unsigned int value() const;

      void set_value(unsigned int new_value);

      bool operator== (const philosophy& o) const;

      virtual void serialisation() override;
      virtual ~philosophy();

    private:
      unsigned int _value;
      std::string _name;
    };
  }
}
