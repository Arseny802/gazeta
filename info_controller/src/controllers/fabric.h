#pragma once
#include "base_controller.h"
#include "info_controller/controller_types.h"

#include <memory>

namespace gazeta::info_controller::controllers
{
  class fabric
  {
  public:
    static std::shared_ptr<base_controller> create(controller_types controller_type) noexcept;
  };
} // namespace gazeta::info_controller::controllers
