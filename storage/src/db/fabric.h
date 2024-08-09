#pragma once
#include <memory>

#include "manager_base.h"
#include "storage/types.h"

namespace gazeta::storage::db {
  class fabric final {
public:
    static manager_base_ptr create(storage_types storage_type);
  };
} // namespace gazeta::storage::db
