#ifndef WITH_PROGRESS_BAR_H
#define WITH_PROGRESS_BAR_H

#include <QProgressBar>

namespace qt { namespace widget {

    class with_progress_bar
    {
    public:

      void set_progress_bar_status(unsigned int current, unsigned int total);

    private:
      unsigned int _current_progress_bar_value, _max_progress_bar_value;

    protected:
      QProgressBar* _progress_bar;
    };

} }

#endif // WITH_PROGRESS_BAR_H
