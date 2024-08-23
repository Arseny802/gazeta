#pragma once
#include "common/article.h"
#include "common/source.h"

namespace gazeta::info_controller::controllers {
  class base_controller {
public:
    virtual ~base_controller();

    virtual std::vector<common::article> get_n_articles(size_t to_read) = 0;
    virtual std::vector<common::article> get_n_articles(size_t to_read, size_t before_id) = 0;

protected:
    std::vector<common::article> read_n_articles_from_tweb(const common::source& src, size_t to_read);
    std::vector<common::article> read_n_articles_from_tweb(const common::source& src, size_t to_read, size_t before_id);
  };
} // namespace gazeta::info_controller::controllers
