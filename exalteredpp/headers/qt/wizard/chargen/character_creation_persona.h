#pragma once

#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QMap>
#include <QGroupBox>

#include "character.h"
#include "widget/with_progress_bar.h"
#include "widget/with_next_continue_buttons.h"

namespace qt {
  namespace wizard {

  class character_creation_persona : public QWidget, public widget::with_progress_bar, public widget::with_next_back_buttons
  {
    Q_OBJECT
  public:
    character_creation_persona(QWidget *parent = nullptr);
    void set_current_persona(const virtues::virtues& new_virtues,
                             const character::social::persona& new_persona,
                             const character::creation::character_type_model &model,
                             const attribute::attributes& attribute);

  signals:
    void persona_created(character::social::persona& persona);

  private:

    static const char *SPECIFIC_PROPERTY, *EMOTION_PROPERTY;

    void check_current_selection();
    void update_titles();

    void increase_issued();
    void decrease_issued();

    void change_persona(const QString& specific, int delta);
    void change_emotion(int emotion_value, int delta);

    QLabel *summary;
    QGroupBox* persona_box;
    QMap<virtues::virtue_enum, QGroupBox*> emotions_of_virtue;
    QMap<character::social::emotion, QLabel*> label_of_emotion;
    QMap<QString, QLabel*> label_of_persona_specific;
    QMap<QString, QPushButton*> increase_specific, decrease_specific;
    QMap<character::social::emotion, QPushButton*> increase_emotion_bonus, decrease_emotion_bonus;
    character::social::persona _persona;
    virtues::virtues _virtues;
  };

  }
}

