#pragma once
#include <string>

namespace gazeta::storage {
  enum class storage_types {
    none = 0,
    sqlite3,
  };

} // namespace gazeta::storage