#include "qt/exalteredapp.h"

#include "qt/label/interfacelabels.h"
#include "serialisation/filesystem_db.h"
#include <QGridLayout>

using namespace qt;

ExalteredApp::ExalteredApp(QWidget *parent)
    : QWidget(parent)
{
  character_manager = QSharedPointer<manager::character_manager>(
        new manager::character_manager(
          QSharedPointer<serialisation::db_abstraction>(new serialisation::filesystem_db())));
  init_load_character_screen();
  setWindowTitle(labels::APP_TITLE);
}

ExalteredApp::~ExalteredApp()
{

}
