#pragma once

namespace gazeta::storage {
  void initialize_logging();
  hare::hlogger_ptr log();
} // namespace gazeta::storage

#define GAZETA_PROJECT_NAME "gazeta"
#define GAZETA_MODULE_NAME "storage"
#define GAZETA_LOGGER_NAME GAZETA_PROJECT_NAME "." GAZETA_MODULE_NAME

#define AUTOLOG_ST AUTOLOG_IN(GAZETA_LOGGER_NAME);
#define AUTOMEASURE_ST AUTOMEASURE_IN(GAZETA_LOGGER_NAME);
