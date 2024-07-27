#pragma once

namespace gazeta::info_controller
{
  void initialize_logging();
  hare::hlogger_ptr log();
} // namespace gazeta::info_controller

#define GAZETA_PROJECT_NAME "gazeta"
#define GAZETA_MODULE_NAME "info_controller"
#define GAZETA_LOGGER_NAME GAZETA_PROJECT_NAME "." GAZETA_MODULE_NAME

#define AUTOLOG_BT AUTOLOG_IN(GAZETA_LOGGER_NAME);
#define AUTOMEASURE_BT AUTOMEASURE_IN(GAZETA_LOGGER_NAME);