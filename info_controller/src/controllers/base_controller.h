#pragma once
#include "common/article.h"
#include "common/source.h"

namespace gazeta::info_controller::controllers {
  class base_controller {
public:
    virtual ~base_controller();

    virtual std::vector<common::article> get_n_articles(int to_read) = 0;

protected:
    std::vector<common::article> read_n_articles_from_tweb(const common::source& src, int to_read);
  };
} // namespace gazeta::info_controller::controllers
