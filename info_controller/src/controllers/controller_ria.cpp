#include "pch.h"
#include "controller_ria.h"
#include "common/article.h"
#include "common/source.h"
#include "info_sources/reader.h"
#include "info_sources/telegram_web.h"

namespace gazeta::info_controller::controllers {
  controller_ria::controller_ria() = default;
  controller_ria::~controller_ria() = default;

  std::vector<common::article> controller_ria::get_n_articles(size_t to_read) {
    AUTOLOG_IC;

    common::source src;
    src.url = "https://t.me/s/rian_ru/";
    return read_n_articles_from_tweb(src, to_read);
  }

  std::vector<common::article> controller_ria::get_n_articles(size_t to_read, size_t before_id) {
    AUTOLOG_IC;

    common::source src;
    src.url = "https://t.me/s/rian_ru/";
    return read_n_articles_from_tweb(src, to_read, before_id);
  }

} // namespace gazeta::info_controller::controllers
