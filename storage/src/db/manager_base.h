#pragma once
#include "common/common.hpp"
#include <memory>
#include <string>

namespace gazeta::storage::db {
  class manager_base {
public:
    manager_base();
    virtual ~manager_base();

    virtual bool connect(const std::string& db_name) = 0;
    virtual bool create_db() = 0;

    virtual bool get_stored_setting(common::setting& setting) = 0;
    virtual bool set_stored_setting(const common::setting& setting) = 0;

protected:
    std::string get_sql_file(const std::string& file_name) const;
  };
  using manager_base_ptr = std::shared_ptr<manager_base>;

} // namespace gazeta::storage::db
