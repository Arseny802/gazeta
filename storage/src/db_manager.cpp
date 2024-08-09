#include "pch.h"
#include "storage/db_manager.h"
#include "db/fabric.h"

namespace gazeta::storage {

  db_manager::db_manager(storage_types storage_type, std::string db_name):
      storage_type_(storage_type),
      db_name_(std::move(db_name)) {
    AUTOLOG_ST;
    manager_pimpl = db::fabric::create(storage_type);
  }

  db_manager::~db_manager() {
    AUTOLOG_ST
  }

  bool db_manager::connect() {
    AUTOLOG_ST
    return manager_pimpl->connect(db_name_);
  }

  bool db_manager::create_db() {
    AUTOLOG_ST
    return manager_pimpl->create_db();
  }
} // namespace gazeta::storage
