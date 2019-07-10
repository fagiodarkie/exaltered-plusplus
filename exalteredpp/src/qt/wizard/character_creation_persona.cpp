#include "wizard/character_creation_persona.h"

#include <layout/qborderlayout.h>

#include <QFormLayout>
#include <QGroupBox>
#include "label/interfacelabels.h"
#include "layout/layout_constants.h"

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
      QVBoxLayout *specifics_and_emotions = new QVBoxLayout;

      QGroupBox *specifics = new QGroupBox(social_labels::PERSONA_VALUE), *emotion_bonuses = new QGroupBox(social_labels::EMOTION_BONUS_VALUE);
      QFormLayout *specifics_form = new QFormLayout, *emotions_form = new QFormLayout;

      for (QString specific : {
           social_labels::COMPULSIONS_SPECIFIC,
           social_labels::EMOTIONS_SPECIFIC,
           social_labels::ILLUSIONS_SPECIFIC,
           social_labels::SERFDOM_SPECIFIC,
           social_labels::MOTIVATIONS_SPECIFIC })
        {
          label_of_persona_specific.insert(specific, new QLabel);
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

      for (character::social::emotion emotion : character::social::BASE_EMOTIONS)
        {
          label_of_emotion.insert(emotion, new QLabel);
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
          emotions_form->addRow(label_of_emotion[emotion], buttons);
        }

      specifics->setLayout(specifics_form);
      emotion_bonuses->setLayout(emotions_form);
      specifics_and_emotions->addWidget(specifics);
      specifics_and_emotions->addWidget(emotion_bonuses);
      central_persona->setLayout(specifics_and_emotions);
      QScrollArea *scroll = new QScrollArea;
      scroll->setWidget(central_persona);

      QHBoxLayout* buttons_layout = new QHBoxLayout;
      next_page = new QPushButton(NEXT_LABEL);
      cancel = new QPushButton(CANCEL_LABEL);
      buttons_layout->addWidget(cancel);
      buttons_layout->addWidget(next_page);

      next_page->setEnabled(false);
      connect(next_page, &QPushButton::clicked, this, &character_creation_persona::next_issued);
      connect(cancel, &QPushButton::clicked, this, &character_creation_persona::back_issued);

      QWidget* buttons = new QWidget;
      buttons->setLayout(buttons_layout);

      layout::QBorderLayout *outer_layout = new layout::QBorderLayout;
      outer_layout->addWidget(scroll, layout::QBorderLayout::Center);
      outer_layout->addWidget(buttons, layout::QBorderLayout::South);

      setLayout(outer_layout);
    }

    void character_creation_persona::increase_issued()
    {

    }

    void character_creation_persona::decrease_issued()
    {

    }

    void character_creation_persona::check_current_selection()
    {

    }

    void character_creation_persona::next_issued()
    {

    }

    void character_creation_persona::set_current_persona(const character::virtues::virtues& new_virtues,
                                                         const character::social::persona& new_persona,
                                                         const character::creation::character_type_model &model,
                                                         const character::attributes& attributes,
                                                         const character::power::power_container& power)
    {
      _persona = new_persona;
      _virtues = new_virtues;

      unsigned int standard_persona_max = static_cast<unsigned int>(int(attributes[character::attribute_names::CHARISMA]    )
                               + int(attributes[character::attribute_names::MANIPULATION])
                               + int(attributes[character::attribute_names::APPEARANCE]  )
                               + power.get_willpower().permanent_willpower());

      unsigned int exalted_persona_max = standard_persona_max;
      unsigned int essence = power.get_essence().permanent_essence();
      unsigned int min_social_attribute = static_cast<unsigned int>(std::min(attributes[character::attribute_names::CHARISMA],
                                          std::min(attributes[character::attribute_names::MANIPULATION],
                                          attributes[character::attribute_names::APPEARANCE])));
      if (essence > min_social_attribute)
        {
          exalted_persona_max += essence - min_social_attribute;
        }

      _persona.set_persona(model.is_supernatural ? exalted_persona_max : standard_persona_max);

      label_of_persona_specific[social_labels::COMPULSIONS_SPECIFIC]->setText(ATTRIBUTE_WITH_POINTS(social_labels::COMPULSIONS_SPECIFIC, _persona.get_compulsions_specific()));
      label_of_persona_specific[social_labels::EMOTIONS_SPECIFIC   ]->setText(ATTRIBUTE_WITH_POINTS(social_labels::EMOTIONS_SPECIFIC   , _persona.get_emotions_specific()))   ;
      label_of_persona_specific[social_labels::ILLUSIONS_SPECIFIC  ]->setText(ATTRIBUTE_WITH_POINTS(social_labels::ILLUSIONS_SPECIFIC  , _persona.get_illusions_specific()))  ;
      label_of_persona_specific[social_labels::SERFDOM_SPECIFIC    ]->setText(ATTRIBUTE_WITH_POINTS(social_labels::SERFDOM_SPECIFIC    , _persona.get_serfdom_specific()))    ;
      label_of_persona_specific[social_labels::MOTIVATIONS_SPECIFIC]->setText(ATTRIBUTE_WITH_POINTS(social_labels::MOTIVATIONS_SPECIFIC, _persona.get_motivations_specific()));

      for (auto emotion : character::social::BASE_EMOTIONS)
        {
          label_of_emotion[emotion]->setText(ATTRIBUTE_WITH_POINTS(character::social::NAME_OF_EMOTION[emotion], _persona.get_emotion_bonus_for(emotion)));
        }

      check_current_selection();
    }

  }
}
