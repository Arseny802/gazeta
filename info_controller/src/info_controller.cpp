#include "info_controller/info_controller.h"
#include "controllers/controller_ria.h"

namespace gazeta::info_controller
{
  info_controller::info_controller() = default;
  info_controller::~info_controller() = default;

  std::vector<article> info_controller::get_n_articles(controller_types ctrl_type, int to_read)
  {
    controllers::controller_ria ria;
    auto res = ria.get_n_articles(to_read);
    for (auto &art : ria.get_n_articles(to_read))
    {
      if (art.is_supported)
        hare::info(art.format());
    }

    return res;
  }
} // namespace gazeta::info_controller
