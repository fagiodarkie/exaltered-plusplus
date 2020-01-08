#pragma once

#include <QComboBox>
#include <QPushButton>
#include <QWidget>
#include <QLabel>
#include <QGroupBox>

#include "virtues/virtues.h"
#include "widget/with_progress_bar.h"

namespace qt {
  namespace wizard {

    using character::virtues::virtues;
    using namespace character::virtues;

    class character_creation_virtues_vice : public QWidget, public widget::with_progress_bar
    {
      Q_OBJECT

    public:
      character_creation_virtues_vice(QWidget* parent = nullptr);
      void update_virtues_limits(virtues virtues, unsigned int max_virtues, unsigned int max_virtue_value);


    signals:
      void back_issued();
      void virtues_chosen(virtues& chosen_virtues);

    private slots:
      void increase_issued();
      void decrease_issued();

    private:

      static const char* AFFECTED_VIRTUE_VICE_PROPERTY;
      void next_issued();

      unsigned int max_points_on_virtues, max_virtue_value;
      QPushButton *next_page, *cancel, *add_vice, *remove_vice;
      virtues _virtues;
      QComboBox *vice_selector;
      QLabel *vice_label;
      QGroupBox *virtuesbox, *vicebox;
      QMap<virtue_enum, QComboBox*> virtue_type;
      QMap<virtue_enum, QLabel*> virtue_label;
      QMap<virtue_enum, QPushButton*> add_to_virtues_or_vice, remove_from_virtues_or_vice;

      void choose_first_virtue_type();
      void choose_second_virtue_type();
      void choose_third_virtue_type();
      void update_scrollers(int virtue_rank_chosen);

      bool is_virtue(QVariant variant) const;
      void update_label(virtue_enum virtue);
      void update_vice_label();
      void update_button_status();
      void update_vice();
      void update_group_titles();
    };
  }
}
