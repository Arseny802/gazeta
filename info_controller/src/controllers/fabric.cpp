#include "pch.h"
#include "fabric.h"
#include "base_controller.h"
#include "controllers/controller_ria.h"

namespace gazeta::info_controller::controllers
{
  std::shared_ptr<base_controller> fabric::create(controller_types controller_type) noexcept
  {
    switch (controller_type)
    {
    case controller_types::ria:
      return std::make_shared<controller_ria>();
      break;
    default:
      return nullptr;
      break;
    }
  }
} // namespace gazeta::info_controller::controllers
