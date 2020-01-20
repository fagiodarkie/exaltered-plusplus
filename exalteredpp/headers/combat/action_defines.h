#ifndef ACTION_DEFINES_H
#define ACTION_DEFINES_H

namespace combat {
    enum class action_speed : unsigned char
    {
      LENTO       = 20,
      ADAGIO      = 22,
      ANDANTE     = 25,
      ALLEGRETTO  = 28,
      PRESTO      = 30
    };
}

#endif // ACTION_DEFINES_H
