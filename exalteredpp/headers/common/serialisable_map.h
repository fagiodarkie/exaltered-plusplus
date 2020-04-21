#ifndef SERIALISABLE_MAP_H
#define SERIALISABLE_MAP_H

#include "../thirdparty/serialisable/serialisable.hpp"
#include <map>

template<typename T>
class serialisable_int_map : public std::map<int, T>, public Serialisable
{
public:
  void serialisation() override
  {
    if (saving())
      {
        char syncTag[2];
        for (auto pair: *this)
          {
            sprintf(syncTag, "%d", pair.first);
            synch(syncTag, pair.second);
          }
      }
    else
      {
        for (auto key: objectKeys())
          {
            T newValue;
            synch(key, newValue);
            this->operator[](std::stoi(key.c_str())) = newValue;
          }
      }
  }
};

#endif // SERIALISABLE_MAP_H
