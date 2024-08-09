#pragma once
#include <memory>
#include <string>

namespace gazeta::storage::db {
  class manager_base {
public:
    manager_base();
    virtual ~manager_base();

    virtual bool connect(const std::string& db_name) = 0;
    virtual bool create_db() = 0;
  };
  using manager_base_ptr = std::shared_ptr<manager_base>;

} // namespace gazeta::storage::db
