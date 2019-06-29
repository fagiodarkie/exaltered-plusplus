#pragma once

#include "virtues/virtue_names.h"

#include <QMap>

namespace character {
  namespace social {

    enum specific {
      COMPULSION = 1,
      ILLUSION,
      EMOTION,
      SERFDOM,
      MOTIVATION
    };

    enum emotion {
      APPROVAL = 1,
      MELANCHOLY,
      NUISANCE,
      CARELESSNESS,
      DISTRACTION,
      FRIGHT,
      INTEREST,
      SERENITY
    };

    const QList<emotion> BASE_EMOTIONS = {
      APPROVAL,
      MELANCHOLY,
      NUISANCE,
      CARELESSNESS,
      DISTRACTION,
      FRIGHT,
      INTEREST,
      SERENITY
    };

    const QMap<emotion, QList<emotion>> HIGHER_GRADE_EMOTIONS_PER_EMOTION = {};

    const QMap<virtues::virtue_enum, QList<emotion>> EMOTION_UNDER_VIRTUE = {
      { virtues::COMPASSION, { NUISANCE, CARELESSNESS } },
      { virtues::CONVINCTION, { APPROVAL, MELANCHOLY } },
      { virtues::VALOR, { DISTRACTION, FRIGHT } },
      { virtues::TEMPERANCE, { INTEREST, SERENITY } }
    };

    virtues::virtue_enum VIRTUE_OF_EMOTION(emotion _emotion) {

      if (!BASE_EMOTIONS.contains(_emotion))
        _emotion = *std::find(BASE_EMOTIONS.begin(), BASE_EMOTIONS.end(),
                              [_emotion](emotion higher_grade)
        {
          return // TODO
        });

      return *std::find_if(virtues::VIRTUE_LIST.begin(), virtues::VIRTUE_LIST.end(),
              [_emotion](virtues::virtue_enum virtue)
                {
                  return EMOTION_UNDER_VIRTUE.value(virtue).contains(_emotion);
                });
    }

  }
}
