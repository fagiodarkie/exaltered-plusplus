#pragma once

#include <QList>
#include <QMap>
#include "virtues/virtue_names.h"

namespace character {
  namespace social {

    enum emotion {
      APPROVAL = 1, TRUST,        ADMIRATION,
      MELANCHOLY,   SADNESS,      GRIEF,
      NUISANCE,     ANGRINESS,    RAGE,
      CARELESSNESS, DISTASTE,     REPULSE,
      DISTRACTION,  SURPRISE,     WONDER,
      FRIGHT,       FEAR,         TERROR,
      INTEREST,     EXPECTATION,  HYPE,
      SERENITY,     JOY,          ECSTASY
    };

    static const QMap<emotion, QString> NAME_OF_EMOTION = {
      { APPROVAL    , "Approval" },
      { TRUST       , "Trust" },
      { ADMIRATION  , "Admiration" },
      { MELANCHOLY  , "Melancholy" },
      { SADNESS     , "Sadness" },
      { GRIEF       , "Grief" },
      { NUISANCE    , "Nuisance" },
      { ANGRINESS   , "Angriness" },
      { RAGE        , "Rage" },
      { CARELESSNESS, "Carelessness" },
      { DISTASTE    , "Distaste" },
      { REPULSE     , "Repulse" },
      { DISTRACTION , "Distraction" },
      { SURPRISE    , "Surprise" },
      { WONDER      , "Wonder" },
      { FRIGHT      , "Fright" },
      { FEAR        , "Fear" },
      { TERROR      , "Terror" },
      { INTEREST    , "Interest" },
      { EXPECTATION , "Expectation" },
      { HYPE        , "Hype" },
      { SERENITY    , "Serenity" },
      { JOY         , "Joy" },
      { ECSTASY     , "Ecstasy" }
    };

    static const QList<emotion> BASE_EMOTIONS = {
      APPROVAL,
      MELANCHOLY,
      NUISANCE,
      CARELESSNESS,
      DISTRACTION,
      FRIGHT,
      INTEREST,
      SERENITY
    };

    static const QList<emotion> MIDDLE_EMOTIONS = {
      TRUST,
      SADNESS,
      ANGRINESS,
      DISTASTE,
      SURPRISE,
      FEAR,
      EXPECTATION,
      JOY
    };

    static const QList<emotion> INTIMATE_EMOTIONS = {
      ADMIRATION,
      GRIEF,
      RAGE,
      REPULSE,
      WONDER,
      TERROR,
      HYPE,
      ECSTASY
    };

    static const QMap<emotion, emotion> MIDDLE_EMOTION_GRADES = {
      { APPROVAL,     TRUST       },
      { MELANCHOLY,   SADNESS     },
      { NUISANCE,     ANGRINESS   },
      { CARELESSNESS, DISTASTE    },
      { DISTRACTION,  SURPRISE    },
      { FRIGHT,       FEAR        },
      { INTEREST,     EXPECTATION },
      { SERENITY,     JOY         }
    };

    static const QMap<emotion, emotion> INTIMATE_EMOTION_GRADES = {
      { APPROVAL,     ADMIRATION },
      { MELANCHOLY,   GRIEF      },
      { NUISANCE,     RAGE       },
      { CARELESSNESS, REPULSE    },
      { DISTRACTION,  WONDER     },
      { FRIGHT,       TERROR     },
      { INTEREST,     HYPE       },
      { SERENITY,     ECSTASY    }
    };

    static const QMap<virtues::virtue_enum, QList<emotion>> EMOTION_UNDER_VIRTUE = {
      { virtues::COMPASSION, { NUISANCE, CARELESSNESS } },
      { virtues::CONVINCTION, { APPROVAL, MELANCHOLY } },
      { virtues::VALOR, { DISTRACTION, FRIGHT } },
      { virtues::TEMPERANCE, { INTEREST, SERENITY } }
    };

    static virtues::virtue_enum VIRTUE_OF_EMOTION(enum emotion _emotion) {

      emotion emotion_to_look_up = _emotion;
      if (!BASE_EMOTIONS.contains(_emotion))
        emotion_to_look_up = *std::find_if(BASE_EMOTIONS.begin(), BASE_EMOTIONS.end(),
                              [_emotion](enum emotion lower_grade)
        {
          return (_emotion == MIDDLE_EMOTION_GRADES[lower_grade])
            || (_emotion == INTIMATE_EMOTION_GRADES[lower_grade]);
        });

      return *std::find_if(virtues::VIRTUE_LIST.begin(), virtues::VIRTUE_LIST.end(),
              [emotion_to_look_up](virtues::virtue_enum virtue)
                {
                  return EMOTION_UNDER_VIRTUE[virtue].contains(emotion_to_look_up);
                });
    }

    static emotion BASE_EMOTION_OF(emotion e)
    {
      if (BASE_EMOTIONS.contains(e))
        return e;

      return *std::find_if(BASE_EMOTIONS.begin(), BASE_EMOTIONS.end(),
                          [e](emotion base) { return (MIDDLE_EMOTION_GRADES[base] == e)
                                                      || (INTIMATE_EMOTION_GRADES[base] == e); });
    }


  }
}
