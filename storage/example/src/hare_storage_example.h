#pragma once

namespace gazeta::storage::example {
  void initialize_logging();
  hare::hlogger_ptr log();
} // namespace gazeta::storage::example

#define GAZETA_STORAGE_EXAMPLE_PROJECT_NAME "gazeta"
#define GAZETA_STORAGE_EXAMPLE_MODULE_NAME "storage.example"
#define GAZETA_STORAGE_EXAMPLE_LOGGER_NAME GAZETA_STORAGE_EXAMPLE_PROJECT_NAME "." GAZETA_STORAGE_EXAMPLE_MODULE_NAME

#define AUTOLOG_STE AUTOLOG_IN(GAZETA_STORAGE_EXAMPLE_LOGGER_NAME);
#define AUTOMEASURE_STE AUTOMEASURE_IN(GAZETA_STORAGE_EXAMPLE_LOGGER_NAME);
