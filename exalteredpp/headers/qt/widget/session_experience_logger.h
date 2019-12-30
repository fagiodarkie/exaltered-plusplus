#ifndef SESSION_EXPERIENCE_LOGGER_H
#define SESSION_EXPERIENCE_LOGGER_H

#include <QWidget>

namespace qt { namespace widget {

    class session_experience_logger : public QWidget
    {
      Q_OBJECT
    public:
      explicit session_experience_logger(QWidget *parent = nullptr);

    signals:

    public slots:
    };

} }
#endif // SESSION_EXPERIENCE_LOGGER_H
