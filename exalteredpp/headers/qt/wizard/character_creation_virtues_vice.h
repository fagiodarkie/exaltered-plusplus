#pragma once

#include <QComboBox>
#include <QPushButton>
#include <QWidget>
#include <QLabel>

#include "virtues/virtues.h"

namespace qt {
  namespace wizard {

    using character::virtues::virtues;
    using namespace character::virtues;

    class character_creation_virtues_vice : public QWidget
    {
      Q_OBJECT

    public:
      character_creation_virtues_vice(virtues virtues, unsigned int max_virtues, QWidget* parent = nullptr);

    signals:
      void back_issued();
      void virtues_chosen(const virtues& chosen_virtues);

    private slots:
      void increase_issued();
      void decrease_issued();

    private:

      static const char* AFFECTED_VIRTUE_VICE_PROPERTY;
      void next_issued();

      unsigned int max_points_on_virtues;
      QPushButton *next_page, *cancel;
      virtues _virtues;
      QComboBox *vice_selector;
      QLabel *vice_label;
      QMap<virtue_enum, QComboBox*> virtue_type;
      QMap<virtue_enum, QLabel*> virtue_label;
      QList<QPushButton*> add_to_virtues_or_vice, remove_from_virtues_or_vice;

      void choose_first_virtue_type();
      void choose_second_virtue_type();
      void choose_third_virtue_type();

      bool is_virtue(QVariant variant) const;
      void update_label(virtue_enum virtue);
      void update_vice_label();
      void update_button_status();
      void update_vice();
    };
  }
}
