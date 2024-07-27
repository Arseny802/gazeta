#include "controller_ria.h"
#include "info_controller/article.h"
#include "info_controller/source.h"
#include "info_sources/reader.h"
#include "info_sources/telegram_web.h"
#include "pch.h"

namespace gazeta::info_controller::controllers
{
  controller_ria::controller_ria() = default;
  controller_ria::~controller_ria() = default;

  std::vector<article> controller_ria::get_n_articles(int to_read)
  {
    AUTOLOG;

    source src;
    src.url = "https://t.me/s/rian_ru/";
    return read_n_articles_from_tweb(src, to_read);
  }

} // namespace gazeta::info_controller::controllers
