#pragma once
#include "base_controller.h"
#include "common/article.h"
#include "common/source.h"

namespace gazeta::info_controller::controllers {
  class controller_ria: public base_controller {
public:
    controller_ria();
    virtual ~controller_ria();

    virtual std::vector<common::article> get_n_articles(int to_read);
  };
} // namespace gazeta::info_controller::controllers
