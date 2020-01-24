#pragma once

#include <QComboBox>
#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <QGroupBox>

#include "virtues/virtues.h"
#include "widget/with_progress_bar.h"
#include "widget/with_next_continue_buttons.h"

namespace qt {
  namespace wizard {

    class character_creation_virtues_vice : public QWidget, public widget::with_progress_bar, public widget::with_next_back_buttons
    {
      Q_OBJECT

    public:
      character_creation_virtues_vice(QWidget* parent = nullptr);
      void update_virtues_limits(virtues::virtues virtues, unsigned int max_virtues, unsigned int max_virtue_value);

    signals:
      void virtues_chosen(virtues::virtues& chosen_virtues);

    private slots:
      void increase_issued();
      void decrease_issued();

    private:

      static const char* AFFECTED_VIRTUE_VICE_PROPERTY;
      void next_issued();

      unsigned int max_points_on_virtues, max_virtue_value;
      QPushButton *add_vice, *remove_vice;
      virtues::virtues _virtues;
      QComboBox *vice_selector;
      QLabel *vice_label;
      QGroupBox *virtuesbox, *vicebox;
      QMap<virtues::virtue_enum, QComboBox*> virtue_type;
      QMap<virtues::virtue_enum, QLabel*> virtue_label;
      QMap<virtues::virtue_enum, QPushButton*> add_to_virtues_or_vice, remove_from_virtues_or_vice;

      void choose_first_virtue_type();
      void choose_second_virtue_type();
      void choose_third_virtue_type();
      void update_scrollers(int virtue_rank_chosen);

      bool is_virtue(QVariant variant) const;
      void update_label(virtues::virtue_enum virtue);
      void update_vice_label();
      void update_button_status();
      void update_vice();
      void update_group_titles();
    };
  }
}
