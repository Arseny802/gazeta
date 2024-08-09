#pragma once
#include "../manager_base.h"

#include <sqlite3.h>

namespace gazeta::storage::db::sqlite {
  class manager: public manager_base {
public:
    manager();
    ~manager() override;

    bool connect(const std::string& db_name) override;
    bool create_db() override;

private:
    sqlite3* db_handler_;
  };
} // namespace gazeta::storage::db::sqlite
