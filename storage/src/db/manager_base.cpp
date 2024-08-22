#include "pch.h"
#include "manager_base.h"

#include <cmrc/cmrc.hpp>

CMRC_DECLARE(gazeta::storage::sql_resources);

namespace gazeta::storage::db {

  manager_base::manager_base() = default;
  manager_base::~manager_base() = default;

  std::string manager_base::get_sql_file(const std::string& file_name) const {
    auto sql_resources = cmrc::gazeta::storage::sql_resources::get_filesystem();
    auto db_file_data = sql_resources.open(file_name);
    std::string db_file = std::string(db_file_data.begin(), db_file_data.end());
    return db_file;
  }

} // namespace gazeta::storage::db
