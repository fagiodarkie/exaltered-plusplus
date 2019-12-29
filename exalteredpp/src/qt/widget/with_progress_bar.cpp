#include "widget/with_progress_bar.h"

namespace qt { namespace widget {

    with_progress_bar::with_progress_bar() : _progress_bar(new QProgressBar) {}

    void with_progress_bar::set_progress_bar_status(unsigned int current, unsigned int total)
    {
      _current_progress_bar_value = current;
      _max_progress_bar_value = total;

      _progress_bar->setRange(0, _max_progress_bar_value);
      _progress_bar->setValue(_current_progress_bar_value);
      _progress_bar->setTextVisible(false);
      _progress_bar->setFixedHeight(5);
    }

}}
