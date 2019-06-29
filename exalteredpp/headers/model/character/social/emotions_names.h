#pragma once

#include <QList>
#include <QMap>

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

    static const QList<emotion> BASE_EMOTION = {
      APPROVAL,
      MELANCHOLY,
      NUISANCE,
      CARELESSNESS,
      DISTRACTION,
      FRIGHT,
      INTEREST,
      SERENITY
    };

    static const QMap<emotion, emotion> MIDDLE_EMOTION = {
      { APPROVAL,     TRUST       },
      { MELANCHOLY,   SADNESS     },
      { NUISANCE,     ANGRINESS   },
      { CARELESSNESS, DISTASTE    },
      { DISTRACTION,  SURPRISE    },
      { FRIGHT,       FEAR        },
      { INTEREST,     EXPECTATION },
      { SERENITY,     JOY         }
    };

    static const QMap<emotion, emotion> INTIMATE_EMOTION = {
      { APPROVAL,     ADMIRATION },
      { MELANCHOLY,   GRIEF      },
      { NUISANCE,     RAGE       },
      { CARELESSNESS, REPULSE    },
      { DISTRACTION,  WONDER     },
      { FRIGHT,       TERROR     },
      { INTEREST,     HYPE       },
      { SERENITY,     ECSTASY    }
    };

  }
}
