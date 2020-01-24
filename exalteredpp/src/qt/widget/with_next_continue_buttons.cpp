#include "widget/with_next_continue_buttons.h"

#include <QHBoxLayout>
#include "caste_style.h"

namespace qt { namespace widget {
with_next_back_buttons::with_next_back_buttons(const QString& back_button_text, const QString& next_button_text)
{
  _back_button = new QPushButton(back_button_text);
  _next_button = new QPushButton(next_button_text);
  qt::style::foreground(_next_button);
  _buttons_layout = new QWidget;
  _next_button->setEnabled(false);

  auto _layout = new QHBoxLayout;
  _layout->addWidget(_back_button);
  _layout->addWidget(_next_button);
  _buttons_layout->setLayout(_layout);
}

QWidget* with_next_back_buttons::buttons_layout() const
{
  return _buttons_layout;
}

void with_next_back_buttons::on_next_issued(const std::function<void(void)>& lambda)
{
  _next_button->connect(_next_button, &QPushButton::clicked, lambda);
}

void with_next_back_buttons::on_back_issued(const std::function<void(void)>& lambda)
{
  _back_button->connect(_back_button, &QPushButton::clicked, lambda);
}

void with_next_back_buttons::enable_next(bool enabled)
{
  _next_button->setEnabled(enabled);
}

void with_next_back_buttons::enable_back(bool enabled)
{
  _back_button->setEnabled(enabled);
}

void with_next_back_buttons::disable_next()
{
  _next_button->setEnabled(false);
}

void with_next_back_buttons::disable_back()
{
  _back_button->setEnabled(false);
}

with_next_back_buttons::~with_next_back_buttons()
{
  qt::style::forget(_next_button);
  delete _back_button;
  delete _next_button;
  delete _buttons_layout;
}
}}
