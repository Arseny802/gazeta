#pragma once

namespace gazeta::info_controller
{
  void initialize_logging();
  hare::hlogger_ptr log();
} // namespace gazeta::info_controller

#define GAZETA_IC_PROJECT_NAME "gazeta"
#define GAZETA_IC_MODULE_NAME "info_controller"
#define GAZETA_IC_LOGGER_NAME GAZETA_IC_PROJECT_NAME "." GAZETA_IC_MODULE_NAME

#define AUTOLOG_IC AUTOLOG_IN(GAZETA_IC_LOGGER_NAME);
#define AUTOMEASURE_IC AUTOMEASURE_IN(GAZETA_IC_LOGGER_NAME);
