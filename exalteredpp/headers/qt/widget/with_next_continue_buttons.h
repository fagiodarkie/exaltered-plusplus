#ifndef WITH_NEXT_CONTINUE_BUTTONS_H
#define WITH_NEXT_CONTINUE_BUTTONS_H

#include <QObject>
#include <QPushButton>
#include <functional>
#include "label/interfacelabels.h"

namespace qt { namespace widget {
    class with_next_back_buttons
    {
    public:
      with_next_back_buttons(const QString& back_button_text = labels::CANCEL_LABEL, const QString& next_button_text = labels::NEXT_LABEL);

      virtual ~with_next_back_buttons();

      void enable_next(bool enabled = true);
      void enable_back(bool enabled = true);
      void disable_next();
      void disable_back();

      void on_next_issued(const std::function<void(void)>& lambda);
      void on_back_issued(const std::function<void(void)>& lambda);

    protected:
      QWidget *buttons_layout() const;

    private:
      QWidget *_buttons_layout;
      QPushButton *_next_button, *_back_button;

    };
}}
#endif // WITH_NEXT_CONTINUE_BUTTONS_H
