#include "pch.h"
#include "manager.h"

#include <cmrc/cmrc.hpp>
#include <sqlite3.h>

CMRC_DECLARE(gazeta::storage::sql_resources);

namespace gazeta::storage::db::sqlite {
  manager::manager() {
    AUTOLOG_ST;
  }

  manager::~manager() {
    AUTOLOG_ST
    sqlite3_close(db_handler_);
  }

  void read_file() {
    // read_file("sql/create_db.sql");
    // read_file("create_db.sql");
  }

  bool manager::connect(const std::string& db_name) {
    AUTOLOG_ST
    log()->info("Connecting to {0}...", db_name);

    int exit = sqlite3_open(db_name.c_str(), &db_handler_);

    if (exit) {
      log()->error("Error open DB: {0}", sqlite3_errmsg(db_handler_));
      return false;
    } else {
      log()->info("Opened Database '{0}' Successfully!", db_name);
    }

    return true;
  }

  bool manager::create_db() {
    AUTOLOG_ST

    try {
      auto sql_resources = cmrc::gazeta::storage::sql_resources::get_filesystem();
      auto create_db_data = sql_resources.open("create_db.sql");
      std::string create_db = std::string(create_db_data.begin(), create_db_data.end());

      char* messaggeError;
      int exit = sqlite3_exec(db_handler_, create_db.c_str(), NULL, 0, &messaggeError);

      if (exit != SQLITE_OK) {
        log()->error("SQL error: {0}", messaggeError);
        sqlite3_free(messaggeError);
      } else {
        log()->info("Table created Successfully!");
        return true;
      }
    } catch (const std::exception& e) {
      log()->error("Error: {0}", e.what());
    }
    return false;
  }
} // namespace gazeta::storage::db::sqlite
