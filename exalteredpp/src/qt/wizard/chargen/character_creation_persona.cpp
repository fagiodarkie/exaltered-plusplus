#include "wizard/chargen/character_creation_persona.h"

#include <layout/qborderlayout.h>
#include <QDebug>
#include <QFormLayout>
#include "label/interfacelabels.h"
#include "layout/layout_constants.h"
#include "caste_style.h"

#include <QScrollArea>

namespace qt {
  namespace wizard {

    using namespace labels::creation_wizard;
    using namespace labels;

    const char* character_creation_persona::SPECIFIC_PROPERTY = "specific";
    const char* character_creation_persona::EMOTION_PROPERTY = "emotion";

    character_creation_persona::character_creation_persona(QWidget *parent) : QWidget(parent)
    {
      QWidget* central_persona = new QWidget;
      QVBoxLayout *specifics_and_emotions = new QVBoxLayout, *emotion_boxes = new QVBoxLayout;

      persona_box = new QGroupBox(social_labels::PERSONA_VALUE);
      QGroupBox *emotion_bonuses = new QGroupBox(social_labels::EMOTION_BONUS_VALUE);
      QFormLayout *specifics_form = new QFormLayout;
      specifics_form->setSizeConstraint(QLayout::SetMinimumSize);
      specifics_and_emotions->setSizeConstraint(QLayout::SetMinimumSize);

      for (QString specific : {
           social_labels::COMPULSIONS_SPECIFIC,
           social_labels::EMOTIONS_SPECIFIC,
           social_labels::ILLUSIONS_SPECIFIC,
           social_labels::SERFDOM_SPECIFIC,
           social_labels::MOTIVATIONS_SPECIFIC })
        {
          label_of_persona_specific[specific] = new QLabel;
          label_of_persona_specific[specific]->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
          QPushButton *increase = new QPushButton("+"), *decrease = new QPushButton("-");
          increase->setProperty(SPECIFIC_PROPERTY, specific);
          increase->setFixedSize(layout::SQUARE_BUTTON_STD_SIZE);
          increase_specific.insert(specific, increase);
          connect(increase, &QPushButton::clicked, this, &character_creation_persona::increase_issued);

          decrease->setFixedSize(layout::SQUARE_BUTTON_STD_SIZE);
          decrease->setProperty(SPECIFIC_PROPERTY, specific);
          decrease_specific.insert(specific, decrease);
          connect(decrease, &QPushButton::clicked, this, &character_creation_persona::decrease_issued);

          QHBoxLayout *buttons = new QHBoxLayout;
          buttons->addWidget(decrease);
          buttons->addWidget(increase);
          specifics_form->addRow(label_of_persona_specific[specific], buttons);
        }
      persona_box->setLayout(specifics_form);

      for (virtues::virtue_enum virtue: virtues::VIRTUE_LIST)
        {
          emotions_of_virtue[virtue] = new QGroupBox;
          QFormLayout *emotions = new QFormLayout;

          for (character::social::emotion emotion: character::social::EMOTION_UNDER_VIRTUE.at(virtue))
            {
              label_of_emotion[emotion] = new QLabel;
              label_of_emotion[emotion]->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::MinimumExpanding);
              QPushButton *increase = new QPushButton("+"), *decrease = new QPushButton("-");
              increase->setProperty(EMOTION_PROPERTY, static_cast<int>(emotion));
              increase->setFixedSize(layout::SQUARE_BUTTON_STD_SIZE);
              increase_emotion_bonus.insert(emotion, increase);
              connect(increase, &QPushButton::clicked, this, &character_creation_persona::increase_issued);

              decrease->setFixedSize(layout::SQUARE_BUTTON_STD_SIZE);
              decrease->setProperty(EMOTION_PROPERTY, static_cast<int>(emotion));
              decrease_emotion_bonus.insert(emotion, decrease);
              connect(decrease, &QPushButton::clicked, this, &character_creation_persona::decrease_issued);

              QHBoxLayout *buttons = new QHBoxLayout;
              buttons->addWidget(decrease);
              buttons->addWidget(increase);
              emotions->addRow(label_of_emotion[emotion], buttons);
            }

          emotions_of_virtue[virtue]->setLayout(emotions);
          emotion_boxes->addWidget(emotions_of_virtue[virtue]);
        }

      emotion_boxes->setAlignment(Qt::AlignTop);
      emotion_bonuses->setLayout(emotion_boxes);
      specifics_and_emotions->addWidget(persona_box);
      specifics_and_emotions->addWidget(emotion_bonuses);
      central_persona->setLayout(specifics_and_emotions);
      QScrollArea *scroll = new QScrollArea;
      scroll->setWidget(central_persona);

      on_next_issued([this]() { emit persona_created(_persona); });

      layout::QBorderLayout *outer_layout = new layout::QBorderLayout;
      outer_layout->addWidget(_progress_bar, layout::QBorderLayout::North);
      outer_layout->addWidget(scroll, layout::QBorderLayout::Center);
      outer_layout->addWidget(buttons_layout(), layout::QBorderLayout::South);

      update_titles();
      setLayout(outer_layout);
    }

    void character_creation_persona::update_titles()
    {
      unsigned int total_specifics = _persona.get_emotions_specific()
          + _persona.get_illusions_specific()
          + _persona.get_motivations_specific()
          + _persona.get_compulsions_specific()
          + _persona.get_serfdom_specific();
      persona_box->setTitle(QString("Persona values (%1 / %2 points spent)")
                            .arg(total_specifics).arg(_persona.get_persona()));

      for (virtues::virtue_enum virtue: virtues::VIRTUE_LIST)
        {
          int spent_on_emotion = 0;
          for (character::social::emotion emotion: character::social::EMOTION_UNDER_VIRTUE.at(virtue))
            spent_on_emotion += _persona.get_emotion_bonus_for(emotion);

          emotions_of_virtue[virtue]->setTitle(QString("Emotions of %1 (%2 / %3 points spent)")
                                               .arg(virtues::VIRTUE_NAME.at(virtue).c_str())
                                               .arg(spent_on_emotion).arg(_virtues.value(virtue).value()));
        }
    }

    void character_creation_persona::increase_issued()
    {
      if (!sender()->property(EMOTION_PROPERTY).isNull())
        change_emotion(sender()->property(EMOTION_PROPERTY).toInt(), 1);

      if (!sender()->property(SPECIFIC_PROPERTY).isNull())
        change_persona(sender()->property(SPECIFIC_PROPERTY).toString(), 1);
    }

    void character_creation_persona::decrease_issued()
    {
      if (!sender()->property(EMOTION_PROPERTY).isNull())
        change_emotion(sender()->property(EMOTION_PROPERTY).toInt(), -1);

      if (!sender()->property(SPECIFIC_PROPERTY).isNull())
        change_persona(sender()->property(SPECIFIC_PROPERTY).toString(), -1);
    }

    void character_creation_persona::change_persona(const QString &specific, int delta)
    {
      unsigned int specific_value = 0;
      if (specific == social_labels::COMPULSIONS_SPECIFIC)
        {
          _persona.set_compulsions_specific(_persona.get_compulsions_specific() + delta);
          specific_value = _persona.get_compulsions_specific();
        }
      if (specific == social_labels::EMOTIONS_SPECIFIC)
        {
          _persona.set_emotions_specific(_persona.get_emotions_specific() + delta);
          specific_value = _persona.get_emotions_specific();
        }
      if (specific == social_labels::ILLUSIONS_SPECIFIC)
        {
          _persona.set_illusions_specific(_persona.get_illusions_specific() + delta);
          specific_value = _persona.get_illusions_specific();
        }
      if (specific == social_labels::SERFDOM_SPECIFIC)
        {
          _persona.set_serfdom_specific(_persona.get_serfdom_specific() + delta);
          specific_value = _persona.get_serfdom_specific();
        }
      if (specific == social_labels::MOTIVATIONS_SPECIFIC)
        {
          _persona.set_motivations_specific(_persona.get_motivations_specific() + delta);
          specific_value = _persona.get_motivations_specific();
        }

      label_of_persona_specific[specific]->setText(ATTRIBUTE_WITH_POINTS(specific, specific_value));
      check_current_selection();

    }

    void character_creation_persona::change_emotion(int emotion_value, int delta)
    {
      character::social::emotion emotion = static_cast<character::social::emotion>(emotion_value);
      _persona.set_base_emotion_bonus(emotion, _persona.get_emotion_bonus_for(emotion) + delta);
      label_of_emotion[emotion]->setText(ATTRIBUTE_WITH_POINTS(character::social::NAME_OF_EMOTION.at(emotion).c_str(), _persona.get_emotion_bonus_for(emotion)));
      check_current_selection();
    }

    void character_creation_persona::check_current_selection()
    {
      unsigned int total_specifics = _persona.get_emotions_specific()
          + _persona.get_illusions_specific()
          + _persona.get_motivations_specific()
          + _persona.get_compulsions_specific()
          + _persona.get_serfdom_specific();
      bool can_up_specifics = total_specifics < _persona.get_persona();
      bool chose_specifics = total_specifics == _persona.get_persona();

      decrease_specific[social_labels::MOTIVATIONS_SPECIFIC ]->setEnabled(_persona.get_motivations_specific() > 0);
      decrease_specific[social_labels::ILLUSIONS_SPECIFIC   ]->setEnabled(_persona.get_illusions_specific()   > 0);
      decrease_specific[social_labels::EMOTIONS_SPECIFIC    ]->setEnabled(_persona.get_emotions_specific()    > 0);
      decrease_specific[social_labels::COMPULSIONS_SPECIFIC ]->setEnabled(_persona.get_compulsions_specific() > 0);
      decrease_specific[social_labels::SERFDOM_SPECIFIC     ]->setEnabled(_persona.get_serfdom_specific()     > 0);

      increase_specific[social_labels::MOTIVATIONS_SPECIFIC ]->setEnabled(can_up_specifics);
      increase_specific[social_labels::ILLUSIONS_SPECIFIC   ]->setEnabled(can_up_specifics);
      increase_specific[social_labels::EMOTIONS_SPECIFIC    ]->setEnabled(can_up_specifics);
      increase_specific[social_labels::COMPULSIONS_SPECIFIC ]->setEnabled(can_up_specifics);
      increase_specific[social_labels::SERFDOM_SPECIFIC     ]->setEnabled(can_up_specifics);

      QMap<virtues::virtue_enum, unsigned int> current_available;
      bool chose_all_emotion_bonus = true;

      for (auto virtue: virtues::VIRTUE_LIST) {
        current_available[virtue] = _virtues[virtue].value();

        for (auto emotion: character::social::EMOTION_UNDER_VIRTUE.at(virtue))
          current_available[virtue] -= _persona.get_emotion_bonus_for(emotion);

        if (chose_all_emotion_bonus && (current_available[virtue] > 0))
          chose_all_emotion_bonus = false;
      }

      for (auto emotion: character::social::BASE_EMOTIONS)
        {
          increase_emotion_bonus[emotion]->setEnabled(current_available[character::social::VIRTUE_OF_EMOTION(emotion)] > 0);
          decrease_emotion_bonus[emotion]->setEnabled(_persona.get_emotion_bonus_for(emotion) > 0);
        }

      update_titles();
      enable_next(chose_specifics && chose_all_emotion_bonus);
    }

    void character_creation_persona::set_current_persona(const virtues::virtues& new_virtues,
                                                         const character::social::persona& new_persona,
                                                         const character::creation::character_type_model &,
                                                         const attribute::attributes& )
    {
      _persona = new_persona;
      _virtues = new_virtues;

      label_of_persona_specific[social_labels::COMPULSIONS_SPECIFIC]->setText(ATTRIBUTE_WITH_POINTS(social_labels::COMPULSIONS_SPECIFIC, _persona.get_compulsions_specific()));
      label_of_persona_specific[social_labels::EMOTIONS_SPECIFIC   ]->setText(ATTRIBUTE_WITH_POINTS(social_labels::EMOTIONS_SPECIFIC   , _persona.get_emotions_specific())   );
      label_of_persona_specific[social_labels::ILLUSIONS_SPECIFIC  ]->setText(ATTRIBUTE_WITH_POINTS(social_labels::ILLUSIONS_SPECIFIC  , _persona.get_illusions_specific())  );
      label_of_persona_specific[social_labels::SERFDOM_SPECIFIC    ]->setText(ATTRIBUTE_WITH_POINTS(social_labels::SERFDOM_SPECIFIC    , _persona.get_serfdom_specific())    );
      label_of_persona_specific[social_labels::MOTIVATIONS_SPECIFIC]->setText(ATTRIBUTE_WITH_POINTS(social_labels::MOTIVATIONS_SPECIFIC, _persona.get_motivations_specific()));

      for (auto emotion : character::social::BASE_EMOTIONS)
        {
          label_of_emotion[emotion]->setText(ATTRIBUTE_WITH_POINTS(character::social::NAME_OF_EMOTION.at(emotion).c_str(), _persona.get_emotion_bonus_for(emotion)));
        }

      check_current_selection();
    }

  }
}
