#include "pch.h"

#include <cmrc/cmrc.hpp>
#include <sqlite3.h>

#include "storage/db_manager.h"

CMRC_DECLARE(gazeta::storage::sql_resources);

int main() {
  using namespace gazeta::storage;
  example::initialize_logging();
  AUTOLOG_STE

  const std::string db_name = "example.db";
  db_manager dbm(storage_types::sqlite3, db_name);

  if (!dbm.connect()) {
    return EXIT_FAILURE;
  }

  dbm.set_stored_setting({"key1", "val1"});
  dbm.set_stored_setting({"key2", "val2"});
  dbm.set_stored_setting({"key3", "val3"});
  dbm.set_stored_setting({"key4", "val4"});

  example::log()->info("Value by key 'key1': {0}", dbm.get_stored_setting("key1"));
  example::log()->info("Value by key 'key2': {0}", dbm.get_stored_setting("key2"));
  example::log()->info("Value by key 'key3': {0}", dbm.get_stored_setting("key3"));
  example::log()->info("Value by key 'key4': {0}", dbm.get_stored_setting("key4"));

  return EXIT_SUCCESS;
}
