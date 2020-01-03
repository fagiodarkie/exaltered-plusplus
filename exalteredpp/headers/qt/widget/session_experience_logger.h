#ifndef SESSION_EXPERIENCE_LOGGER_H
#define SESSION_EXPERIENCE_LOGGER_H

#include <QDialog>
#include <QPushButton>
#include <QLineEdit>
#include <QSpinBox>
#include <vector>
#include "narrative/session_awards.h"

namespace qt { namespace widget {

    class session_experience_logger : public QDialog
    {
      Q_OBJECT

    public:
      explicit session_experience_logger(QWidget *parent = nullptr);

      void set_next_session_number(unsigned int session_number);

    signals:

      void session_logged(const character::narrative::session_awards& awards);

    private:

      QMap<character::narrative::experience_award_type, unsigned int> MAX_VALUE = {
        { character::narrative::PLAYTIME,              24 },
        { character::narrative::ROLEPLAY_CHARACTER,    5 },
        { character::narrative::ROLEPLAY_TEAMMATES,    5 },
        { character::narrative::ROLEPLAY_NARRATOR,     5 },
        { character::narrative::MOTIVATION,            11 },
        { character::narrative::NARRATION,             1000 },
        { character::narrative::LONG_TIME_CALIBRATION, 1000 },
        { character::narrative::STUNT,                 3 },
        { character::narrative::COOL,                  3 },
        { character::narrative::INTUITION,             3 },
        { character::narrative::MEMENTO_AUDERE_SEMPER, 5 },
        { character::narrative::ACTING_OSCAR,          5 },
        { character::narrative::BOSSFIGHT,             20 },
        { character::narrative::EASTER_EGG,            20 },
        { character::narrative::VOLUNTEERING,          50 },
        { character::narrative::DIVINE_GAME,           100 },
        { character::narrative::COSPLAY,               51 }
      };

      void submit_session();
      void refresh();

      unsigned int _session;
      QPushButton *submit;
      QMap<character::narrative::experience_award_type, QLineEdit*> description_fields;
      QMap<character::narrative::experience_award_type, QSpinBox*> award_fields;
    };

} }
#endif // SESSION_EXPERIENCE_LOGGER_H
