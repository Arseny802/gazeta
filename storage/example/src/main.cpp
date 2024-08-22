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

  dbm.set_stored_setting({"key1", "val1"});
  dbm.set_stored_setting({"key2", "val2"});
  dbm.set_stored_setting({"key3", "val3"});
  dbm.set_stored_setting({"key4", "val4"});

  log()->info("Value by key 'key1': {0}", dbm.get_stored_setting("key1").value());
  log()->info("Value by key 'key2': {0}", dbm.get_stored_setting("key2").value());
  log()->info("Value by key 'key3': {0}", dbm.get_stored_setting("key3").value());
  log()->info("Value by key 'key4': {0}", dbm.get_stored_setting("key4").value());

  return EXIT_SUCCESS;
}
