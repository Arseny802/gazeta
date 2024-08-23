#include <string>

#include "common/common.hpp"
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

    /// settings
    std::string get_stored_setting(const std::string& key, std::string default_value = std::string());
    std::string get_stored_setting(common::setting& setting, std::string default_value = std::string());
    bool set_stored_setting(const common::setting& setting);

    /// source_types (data reciever types)
    std::vector<common::source_type> get_source_types();

    /// sources (data URLs)
    bool get_info_source(common::source& info_source);
    std::vector<common::source> get_info_sources();
    bool set_info_source(const common::source& info_source);

    /// articles (concrete data)
    bool get_article(common::article& article);
    std::vector<common::article> get_articles(size_t limit = 100);
    std::vector<common::article> get_articles(int timestamp_begin);
    std::vector<common::article> get_articles(int timestamp_begin, int timestamp_end);
    std::vector<common::article> get_articles_by_source(int source_id, size_t limit = 100);
    std::vector<common::article> get_articles_by_source(int source_id, int timestamp_begin);
    std::vector<common::article> get_articles_by_source(int source_id, int timestamp_begin, int timestamp_end);
    bool set_article(const common::article& article);
    bool set_articles(const std::vector<common::article>& articles);

private:
    std::atomic_bool connected_ = false;
    const storage_types storage_type_;
    const std::string db_name_;
    std::map<std::string, std::string> settings_;

    std::shared_ptr<db::manager_base> manager_pimpl;
  };

} // namespace gazeta::storage