#include "screen/qexperience_screen.h"

namespace qt { namespace screen {

qexperience_screen::qexperience_screen(std::shared_ptr<character::character> character,
                                       manager::character_manager &ch_manager,
                                       unsigned int session_number,
                                       QWidget *parent) : QWidget(parent), _character(character), _character_manager(ch_manager), _session_number(session_number)
{
  open_logger = new QPushButton("Add session");
}



} }
