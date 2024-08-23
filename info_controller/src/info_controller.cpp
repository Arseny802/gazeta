#include "info_controller/info_controller.h"
#include "controllers/fabric.h"
#include "storage/db_manager.h"

namespace gazeta::info_controller {
  const std::string_view info_controller::db_name_ = "gazeta.db";

  info_controller::info_controller(controller_types controller_type): controller_type_(controller_type) {
    controller_pimpl_ = controllers::fabric::create(controller_type);
    db_manager_pimpl_ = std::make_unique<storage::db_manager>(storage::storage_types::sqlite3, db_name_.data());
  }

  info_controller::~info_controller() = default;

  bool info_controller::available() const noexcept {
    return controller_pimpl_ && db_manager_pimpl_;
  }

  std::vector<common::article> info_controller::get_n_articles(size_t to_read) {
    AUTOLOG_IC

    if (!controller_pimpl_ || !db_manager_pimpl_) {
      log()->error("Can't create controller");
      return {};
      throw std::runtime_error(fmt::format("Unsupported controller {0}", static_cast<int>(controller_type_)));
    }

    db_manager_pimpl_->connect();

    auto articles_from_database = db_manager_pimpl_->get_articles(to_read);
    if (articles_from_database.empty()) {
      auto result = controller_pimpl_->get_n_articles(to_read);
      db_manager_pimpl_->set_articles(result);

      return result;
    }

    /* Controller and database have the same articles. Dates:
    controller[0] = 11:00 <-
    controller[1] = 12:00 <-
    controller[2] = 13:00
    database[0] = 12:00 <-
    database[1] = 11:00
    database[2] = 10:00
    */

    std::vector<common::article> result;
    while (result.size() < to_read) {
      auto last_articles_from_controller = controller_pimpl_->get_n_articles(1ull);
      if (last_articles_from_controller.empty()) {
        if (result.empty()) {
          log()->error("Can't get articles from info controller");
          throw std::runtime_error("Can't get articles from info controller");
        }

        // TODO: Многоразвый метод попытки загрузки данных
        break;
      }

      size_t accepteble_index = 0;
      while (last_articles_from_controller[accepteble_index].datetime_occurred <=
             articles_from_database[0].datetime_occurred) {
        ++accepteble_index;
      }

      if (accepteble_index > 0) {
        std::reverse(articles_from_database.begin(), articles_from_database.end());
        result.insert(result.begin(), articles_from_database.cbegin(), articles_from_database.cend());

        result.insert(result.end(),
                      last_articles_from_controller.cbegin() + accepteble_index,
                      last_articles_from_controller.cend());

        std::for_each(last_articles_from_controller.cbegin() + accepteble_index,
                      last_articles_from_controller.cend(),
                      [this](const auto& article) { db_manager_pimpl_->set_article(article); });

        if (result.size() < to_read) {
          auto old_articles = controller_pimpl_->get_n_articles(to_read - result.size(), result.begin()->id);
          result.insert(result.begin(), old_articles.cbegin(), old_articles.cend());
        }
      } else {
        result.insert(result.begin(), last_articles_from_controller.cbegin(), last_articles_from_controller.cend());
        std::for_each(last_articles_from_controller.cbegin(),
                      last_articles_from_controller.cend(),
                      [this](const auto& article) { db_manager_pimpl_->set_article(article); });
      }
    }

    return result;
  }

  std::vector<common::article> info_controller::get_articles_afer(size_t to_read) {
    AUTOLOG_IC

    return {};
  }
} // namespace gazeta::info_controller
