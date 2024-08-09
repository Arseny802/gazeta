#include "pch.h"
#include "fabric.h"
#include "sqlite/manager.h"

namespace gazeta::storage::db {
  manager_base_ptr fabric::create(storage_types storage_type) {
    switch (storage_type) {
    case storage_types::sqlite3: return std::make_shared<sqlite::manager>();
    default: throw std::runtime_error("unknown storage type");
    }
  }
} // namespace gazeta::storage::db
