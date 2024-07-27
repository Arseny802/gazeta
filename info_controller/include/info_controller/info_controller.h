#pragma once
#include "article.h"
#include "controller_types.h"
#include "source.h"

#include <vector>

namespace gazeta::info_controller
{
  struct info_controller
  {
    info_controller();
    ~info_controller();

    std::vector<article> get_n_articles(controller_types ctrl_type, int to_read);
  };
} // namespace gazeta::info_controller
