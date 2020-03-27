#include "wizard/chargen/character_creation_virtues_vice.h"

#include "label/interfacelabels.h"
#include "layout/qborderlayout.h"
#include "layout/layout_constants.h"
#include <QFormLayout>
#include <QHBoxLayout>

#include "label/interfacelabels.h"
#include "common/reverse_search.h"
#include "caste_style.h"

namespace qt {
  namespace wizard {

    using namespace labels;

    using namespace virtues;

    const char* character_creation_virtues_vice::AFFECTED_VIRTUE_VICE_PROPERTY = "affected-virtue";

    character_creation_virtues_vice::character_creation_virtues_vice(QWidget* parent)
      : QWidget (parent)
    {
      QWidget *virtues_widget = new QWidget;
      QFormLayout *virtues_form = new QFormLayout;
      virtuesbox = new QGroupBox;
      vicebox = new QGroupBox;

      for (virtue_enum v: VIRTUE_LIST)
        {
          // virtue types creation
          QComboBox *virtue_cbox = new QComboBox;
          for (auto rank : VIRTUE_RANK_LIST)
            {
              virtue_cbox->addItem(RANK_NAME.at(rank).c_str(), rank);
            }
          virtue_type[v] = virtue_cbox;

          // label
          virtue_label[v] = new QLabel;
          update_label(v);

          // increase / decrease management
          QPushButton *add = new QPushButton("+");
          add->setFixedSize(layout::SQUARE_BUTTON_STD_SIZE);
          add->setProperty(AFFECTED_VIRTUE_VICE_PROPERTY, v);
          connect(add, &QPushButton::clicked, this, &character_creation_virtues_vice::increase_issued);
          add_to_virtues_or_vice[v] = add;

          QPushButton *remove = new QPushButton("-");
          remove->setFixedSize(layout::SQUARE_BUTTON_STD_SIZE);
          remove->setProperty(AFFECTED_VIRTUE_VICE_PROPERTY, v);
          connect(remove, &QPushButton::clicked, this, &character_creation_virtues_vice::decrease_issued);
          remove_from_virtues_or_vice[v] = remove;

          QHBoxLayout *row = new QHBoxLayout;
          row->addWidget(remove);
          row->addWidget(add);
          row->addWidget(virtue_cbox);
          virtues_form->addRow(virtue_label.value(v), row);
        }
      virtuesbox->setLayout(virtues_form);

      // fill vice
      {
        vice_selector = new QComboBox;
        for (auto vice: VICE_NAME)
          vice_selector->addItem(vice.second.c_str());
        connect(vice_selector, &QComboBox::currentTextChanged, this, &character_creation_virtues_vice::update_vice);

        // increase / decrease management
        add_vice = new QPushButton("+");
        add_vice->setFixedSize(layout::SQUARE_BUTTON_STD_SIZE);
        connect(add_vice, &QPushButton::clicked, this, &character_creation_virtues_vice::increase_issued);

        remove_vice = new QPushButton("-");
        remove_vice->setFixedSize(layout::SQUARE_BUTTON_STD_SIZE);
        connect(remove_vice, &QPushButton::clicked, this, &character_creation_virtues_vice::decrease_issued);

        vice_label = new QLabel;
        update_vice_label();

        QHBoxLayout *row = new QHBoxLayout;
        row->addWidget(vice_label);
        row->addWidget(vice_selector);
        row->addWidget(remove_vice);
        row->addWidget(add_vice);
        vicebox->setLayout(row);
      }

      QVBoxLayout *virtues_vice = new QVBoxLayout;
      virtues_vice->setAlignment(Qt::AlignTop);
      virtues_vice->addWidget(virtuesbox);
      virtues_vice->addWidget(vicebox);
      virtues_widget->setLayout(virtues_vice);

      on_next_issued([this]() { next_issued(); });

      layout::QBorderLayout *outer_layout = new layout::QBorderLayout;
      outer_layout->addWidget(_progress_bar, layout::QBorderLayout::North);
      outer_layout->addWidget(virtues_widget, layout::QBorderLayout::Center);
      outer_layout->addWidget(buttons_layout(), layout::QBorderLayout::South);
      update_group_titles();

      setLayout(outer_layout);
    }

    void character_creation_virtues_vice::update_virtues_limits(class virtues virtues, unsigned int max_virtues, unsigned int max_virtue_value)
    {
      _virtues = virtues;
      max_points_on_virtues = max_virtues;
      this->max_virtue_value = max_virtue_value;

      update_group_titles();
      update_button_status();
    }

    void character_creation_virtues_vice::update_button_status()
    {
      unsigned int total_points_spent = 0;
      for (virtue_enum virt: VIRTUE_LIST)
        total_points_spent += _virtues[virt].value() - 1;

      total_points_spent += _virtues.vice_value() - 1;

      bool add_disabled = (total_points_spent == max_points_on_virtues);
      for (auto virtue : VIRTUE_LIST)
        {
          add_to_virtues_or_vice[virtue]->setDisabled(add_disabled || _virtues.value(virtue).value() >= max_virtue_value);
        }
      add_vice->setDisabled(add_disabled || _virtues.vice_value() >= max_virtue_value);

      for (virtue_enum v: VIRTUE_LIST)
        {
          remove_from_virtues_or_vice[v]->setDisabled(_virtues[v].value() <= 1);
        }
      remove_vice->setDisabled(_virtues.vice_value() <= 1);

      enable_next(add_disabled);
    }

    void character_creation_virtues_vice::update_label(virtue_enum virtue)
    {
      virtue_label[virtue]->setText(labels::creation_wizard::ATTRIBUTE_WITH_POINTS(VIRTUE_NAME.at(virtue).c_str(), _virtues.value(virtue).value()));
    }

    void character_creation_virtues_vice::update_vice_label()
    {
      vice_label->setText(labels::creation_wizard::ATTRIBUTE_WITH_POINTS(labels::creation_wizard::VICE_SELECTOR, _virtues.vice_value()));
    }

    bool character_creation_virtues_vice::is_virtue(QVariant variant) const
    {
      return !variant.isNull();
    }

    void character_creation_virtues_vice::next_issued()
    {
      emit virtues_chosen(_virtues);
    }

    void character_creation_virtues_vice::update_group_titles()
    {
      unsigned int remaining = 0;
      for (auto virtue: VIRTUE_LIST)
        if (_virtues.value(virtue).value() > 0)
          remaining += _virtues.value(virtue).value() - 1;
      if (_virtues.vice_value() > 0)
        remaining += _virtues.vice_value() - 1;

      virtuesbox->setTitle(QString("Virtues (%1 / %2 points spent)").arg(remaining).arg(max_points_on_virtues));
      vicebox->setTitle(QString("Vice (%1 / %2 points spent)").arg(remaining).arg(max_points_on_virtues));
    }

    void character_creation_virtues_vice::increase_issued()
    {
      QVariant sender_variant = sender()->property(AFFECTED_VIRTUE_VICE_PROPERTY);

      if (is_virtue(sender_variant))
        {
          virtue_enum affected_virtue = static_cast<virtue_enum>(sender_variant.toInt());
          _virtues.value(affected_virtue).set_value(_virtues.value(affected_virtue).value() + 1);
          update_label(affected_virtue);
        }
      else
        {
          _virtues.set_vice_value(_virtues.vice_value() + 1);
          update_vice_label();
        }
      update_button_status();
      update_group_titles();
    }

    void character_creation_virtues_vice::decrease_issued()
    {
      QVariant sender_variant = sender()->property(AFFECTED_VIRTUE_VICE_PROPERTY);

      if (is_virtue(sender_variant))
        {
          virtue_enum affected_virtue = static_cast<virtue_enum>(sender_variant.toInt());
          _virtues.value(affected_virtue).set_value(_virtues.value(affected_virtue).value() - 1);
          update_label(affected_virtue);
        }
      else
        {
          _virtues.set_vice_value(_virtues.vice_value() - 1);
          update_vice_label();
        }
      update_button_status();
      update_group_titles();
    }

    void character_creation_virtues_vice::update_vice()
    {
      vice_enum selected_vice = commons::reverse_search_in_map(VICE_LIST, VICE_NAME, vice_selector->currentText().toStdString());
      _virtues.set_vice_type(selected_vice);
    }
  }
}
