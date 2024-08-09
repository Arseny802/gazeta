#include "pch.h"

#include <cmrc/cmrc.hpp>
#include <sqlite3.h>

#include "storage/db_manager.h"

CMRC_DECLARE(gazeta::storage::sql_resources);

int main() {
  using namespace gazeta::storage;
  example::initialize_logging();

  const std::string db_name = "example.db";
  db_manager dbm(storage_types::sqlite3, db_name);

  if (!dbm.connect()) {
    return EXIT_FAILURE;
  }

  if (!dbm.create_db()) {
    return EXIT_FAILURE;
  }

  return EXIT_SUCCESS;
}
