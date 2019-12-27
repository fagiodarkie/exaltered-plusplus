#pragma once

#include <QLabel>
#include <QPushButton>
#include <QWidget>
#include <QMap>
#include "character.h"

namespace qt {
  namespace wizard {

  class character_creation_persona : public QWidget
  {
    Q_OBJECT
  public:
    character_creation_persona(QWidget *parent = nullptr);
    void set_current_persona(const character::virtues::virtues& new_virtues,
                             const character::social::persona& new_persona,
                             const character::creation::character_type_model &model,
                             const character::attributes& attributes,
                             const character::power::power_container& power);

  signals:
    void back_issued();
    void persona_created(character::social::persona& persona);

  private:

    static const char *SPECIFIC_PROPERTY, *EMOTION_PROPERTY;

    void next_issued();
    void check_current_selection();

    void increase_issued();
    void decrease_issued();

    void change_persona(const QString& specific, int delta);
    void change_emotion(int emotion_value, int delta);

    QPushButton *next_page, *cancel;
    QMap<character::social::emotion, QLabel*> label_of_emotion;
    QMap<QString, QLabel*> label_of_persona_specific;
    QMap<QString, QPushButton*> increase_specific, decrease_specific;
    QMap<character::social::emotion, QPushButton*> increase_emotion_bonus, decrease_emotion_bonus;
    character::social::persona _persona;
    character::virtues::virtues _virtues;
  };

  }
}

