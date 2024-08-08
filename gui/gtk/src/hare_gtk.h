#pragma once

namespace gazeta::gui
{
  void initialize_logging();
  hare::hlogger_ptr log();
} // namespace gazeta::gui

#define GAZETA_PROJECT_NAME "gazeta"
#define GAZETA_MODULE_NAME "gtk"
#define GAZETA_LOGGER_NAME GAZETA_PROJECT_NAME "." GAZETA_MODULE_NAME

#define AUTOLOG_GTK AUTOLOG_IN(GAZETA_LOGGER_NAME);
#define AUTOMEASURE_GTK AUTOMEASURE_IN(GAZETA_LOGGER_NAME);