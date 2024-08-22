#pragma once
#include "common/article.h"
#include "common/source.h"
#include "controller_types.h"

#include <memory>
#include <vector>

namespace gazeta::info_controller {
  namespace controllers {
    class base_controller;
  } // namespace controllers

  struct info_controller {
    info_controller(controller_types controller_type);
    ~info_controller();

    std::vector<common::article> get_n_articles(int to_read);
    std::vector<common::article> get_articles_afer(int to_read);

    controller_types controller_type;
    std::shared_ptr<controllers::base_controller> controller_pimpl;
  };
} // namespace gazeta::info_controller
