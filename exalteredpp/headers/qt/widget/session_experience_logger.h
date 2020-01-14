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
      ~session_experience_logger();

      void set_next_session_number(unsigned int session_number);

    signals:

      void session_logged(const narrative::session_awards& awards);

    private:

      QMap<narrative::experience_award_type, unsigned int> MAX_VALUE = {
        { narrative::PLAYTIME,              24 },
        { narrative::ROLEPLAY_CHARACTER,    5 },
        { narrative::ROLEPLAY_TEAMMATES,    5 },
        { narrative::ROLEPLAY_NARRATOR,     5 },
        { narrative::MOTIVATION,            11 },
        { narrative::NARRATION,             1000 },
        { narrative::LONG_TIME_CALIBRATION, 1000 },
        { narrative::STUNT,                 3 },
        { narrative::COOL,                  3 },
        { narrative::INTUITION,             3 },
        { narrative::MEMENTO_AUDERE_SEMPER, 5 },
        { narrative::ACTING_OSCAR,          5 },
        { narrative::BOSSFIGHT,             20 },
        { narrative::EASTER_EGG,            20 },
        { narrative::VOLUNTEERING,          50 },
        { narrative::DIVINE_GAME,           100 },
        { narrative::COSPLAY,               51 }
      };

      void submit_session();
      void refresh();

      unsigned int _session;
      QPushButton *submit;
      QMap<narrative::experience_award_type, QLineEdit*> description_fields;
      QMap<narrative::experience_award_type, QSpinBox*> award_fields;
    };

} }
#endif // SESSION_EXPERIENCE_LOGGER_H
