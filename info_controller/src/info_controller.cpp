#include "info_controller/info_controller.h"
#include "controllers/fabric.h"

namespace gazeta::info_controller
{
  info_controller::info_controller() = default;
  info_controller::~info_controller() = default;

  std::vector<article> info_controller::get_n_articles(controller_types ctrl_type, int to_read)
  {
    const auto controller = controllers::fabric::create(ctrl_type);
    if (!controller)
    {
      log()->error("Can't create controller");
      throw std::runtime_error(fmt::format(
          "Unsupported controller {0}",
          static_cast<int>(ctrl_type)));
    }

    auto result = controller->get_n_articles(to_read);
    for (auto &art : result)
    {
      if (art.is_supported)
        log()->info(art.format());
    }

    return result;
  }
} // namespace gazeta::info_controller
