#include <string>

#include "types.h"

namespace gazeta::storage {
  namespace db {
    class manager_base;
  } // namespace db

  class db_manager {
public:
    db_manager(storage_types storage_type, std::string db_name);
    ~db_manager();

    bool connect();

    bool create_db();

private:
    const storage_types storage_type_;
    const std::string db_name_;

    std::shared_ptr<db::manager_base> manager_pimpl;
  };

} // namespace gazeta::storage