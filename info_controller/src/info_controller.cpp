#include "info_controller/info_controller.h"
#include "controllers/fabric.h"

namespace gazeta::info_controller
{
  info_controller::info_controller(controller_types controller_type)
      : controller_type(controller_type)
  {
    controller_pimpl = controllers::fabric::create(controller_type);
  }

  info_controller::~info_controller() = default;

  std::vector<article> info_controller::get_n_articles(int to_read)
  {
    if (!controller_pimpl)
    {
      log()->error("Can't create controller");
      throw std::runtime_error(fmt::format(
          "Unsupported controller {0}",
          static_cast<int>(controller_type)));
    }

    auto result = controller_pimpl->get_n_articles(to_read);
    for (auto &art : result)
    {
      if (art.is_supported)
        log()->info(art.format());
    }

    return result;
  }
} // namespace gazeta::info_controller
