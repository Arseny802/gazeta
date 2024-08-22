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

  std::optional<std::string> db_manager::get_stored_setting(const std::string& key) {
    AUTOLOG_ST
    common::setting setting;
    setting.key = key;
    manager_pimpl->get_stored_setting(setting);
    return setting.value;
  }

  bool db_manager::set_stored_setting(const common::setting& setting) {
    AUTOLOG_ST
    return manager_pimpl->set_stored_setting(setting);
  }
} // namespace gazeta::storage
