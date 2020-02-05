#include "wizard/final_damage_results_push_knock_page.h"

#include "layout/qborderlayout.h"
#include <QVBoxLayout>
#include <QHBoxLayout>

namespace qt {
  namespace wizard {
    final_damage_results_push_knock_page::final_damage_results_push_knock_page(QWidget *parent) : QWidget(parent)
    {
      layout::QBorderLayout *outer = new layout::QBorderLayout;

      status_label = new QLabel;
      status_label->setWordWrap(true);

      push_meters_spin = new QSpinBox;
      push_meters_spin->setMinimum(0);

      knockdown_radio = new QRadioButton("Knockdown", this);
      knockdown_radio->setChecked(true);
      knockback_radio = new QRadioButton("Knockback", this);

      knock_him = new QCheckBox("Push the defender");
      knock_him->setChecked(false);
      knock_toggled(Qt::CheckState::Unchecked);
      connect(knock_him, &QCheckBox::stateChanged, this, &final_damage_results_push_knock_page::knock_toggled);

      QHBoxLayout *radios = new QHBoxLayout;
      QWidget *radios_widget = new QWidget;
      radios->addWidget(knockdown_radio);
      radios->addWidget(knockback_radio);
      radios_widget->setLayout(radios);

      QVBoxLayout *knocks_layout = new QVBoxLayout;
      knocks_layout->addWidget(status_label);
      knocks_layout->addWidget(knock_him);
      knocks_layout->addWidget(radios_widget);
      knocks_layout->addWidget(new QLabel("Spend successes:"));
      knocks_layout->addWidget(push_meters_spin);
      QWidget *knocks_widget = new QWidget;
      knocks_widget->setLayout(knocks_layout);

      QVBoxLayout *center = new QVBoxLayout;
      center->addWidget(status_label);
      center->addWidget(knocks_widget);
      center->setAlignment(Qt::AlignTop);
      QWidget* center_widget = new QWidget;
      center_widget->setLayout(center);

      outer->addWidget(_progress_bar, layout::QBorderLayout::North);
      outer->addWidget(center_widget, layout::QBorderLayout::Center);
      outer->addWidget(buttons_layout(), layout::QBorderLayout::South);

      setLayout(outer);

      enable_next();
      on_next_issued([this]() { knock_chosen(); });
    }

    void final_damage_results_push_knock_page::set_final_damage_stats(unsigned int final_damage_rolled, unsigned int final_damage_pool)
    {
      status_label->setText(QString("With a post-soak damage pool of %0 dice, a total of %1 successes were rolled for damage.\r\n"
                                    "Do you wish to spend some to push back or knockdown your opponent?")
                            .arg(final_damage_pool).arg(final_damage_rolled));

      push_meters_spin->setMaximum(final_damage_rolled);
    }

    void final_damage_results_push_knock_page::knock_toggled(int new_toggle_state)
    {
      bool enabled = (new_toggle_state == Qt::CheckState::Unchecked) ? false : true;
      knockdown_radio->setEnabled(enabled);
      knockback_radio->setEnabled(enabled);
      push_meters_spin->setEnabled(enabled);
    }

    void final_damage_results_push_knock_page::knock_chosen()
    {
      if (!knock_him->isChecked())
        emit no_knocking();
      else if (knockdown_radio->isChecked())
        emit knockdown(push_meters_spin->value());
      else
        emit knockback(push_meters_spin->value());
    }
  }
}
