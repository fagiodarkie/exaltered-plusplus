#ifndef QEXPERIENCE_SCREEN_H
#define QEXPERIENCE_SCREEN_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLabel>

#include "character.h"
#include "widget/session_experience_logger.h"
#include "managers/character_manager.h"

namespace qt { namespace screen {

    class qexperience_screen : public QWidget
    {
      Q_OBJECT
    public:
      explicit qexperience_screen(std::shared_ptr<character::character> character,
                                  manager::character_manager &ch_manager,
                                  QWidget *parent = nullptr);


    signals:

    public slots:

    private:
      widget::session_experience_logger *_logger;
      QPushButton *open_logger;

      void recompute_logger_session();
      void add_session(const character::narrative::session_awards& new_awards);
      void refresh();

      void refresh_awards();
      void refresh_expenses();
      void add_award_list(unsigned int session_number) const;
      void add_expense(const character::narrative::experience_purchase& purchase) const;
      void update_status_label() const;

      QWidget *awards, *expenses, *listawards, *listexpenses,
        *awards_buttons;
      QVBoxLayout *awards_vbox;
      QScrollArea *awards_scroll;
      QLabel *status;

      std::shared_ptr<character::character> _character;
      manager::character_manager _character_manager;
    };

} }

#endif // QEXPERIENCE_SCREEN_H
