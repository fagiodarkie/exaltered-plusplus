#ifndef QEXPERIENCE_SCREEN_H
#define QEXPERIENCE_SCREEN_H

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QScrollArea>
#include <QLabel>

#include "character.h"
#include "widget/session_experience_logger.h"
#include "widget/experience_purchase_widget.h"
#include "managers/character_manager.h"

namespace qt { namespace screen {

    class qexperience_screen : public QWidget
    {
      Q_OBJECT
    public:
      explicit qexperience_screen(std::shared_ptr<character::character> character,
                                  std::shared_ptr<manager::character_manager> &ch_manager,
                                  QWidget *parent = nullptr);

      ~qexperience_screen();

    signals:

    public slots:

    private:
      widget::session_experience_logger *_logger;
      widget::experience_purchase_widget *_purchase_logger;
      QPushButton *open_logger, *open_expense_logger;

      void recompute_logger_session();
      void add_session(const narrative::session_awards& new_awards);
      void refresh();

      void refresh_awards();
      void refresh_expenses();
      void add_award_list(unsigned int session_number) const;
      void add_expense(const narrative::experience_purchase& purchase);
      void update_status_label() const;

      QWidget *awards, *expenses, *listexpenses,
        *awards_buttons;
      QVBoxLayout *awards_vbox;
      QScrollArea *awards_scroll;
      QLabel *status;

      std::shared_ptr<character::character> _character;
      std::shared_ptr<manager::character_manager> _character_manager;
    };

} }

#endif // QEXPERIENCE_SCREEN_H
