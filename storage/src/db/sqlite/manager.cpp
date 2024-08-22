#include "pch.h"
#include "manager.h"

#include <sqlite3.h>

namespace gazeta::storage::db::sqlite {
  manager::manager() {
    AUTOLOG_ST;
  }

  manager::~manager() {
    AUTOLOG_ST
    sqlite3_close(db_handler_);
  }

  bool manager::connect(const std::string& db_name) {
    AUTOLOG_ST
    log()->info("Connecting to {0}...", db_name);

    int exit = sqlite3_open(db_name.c_str(), &db_handler_);

    if (exit) {
      log()->error("Error open DB: {0}", sqlite3_errmsg(db_handler_));
      return false;
    } else {
      log()->info("Opened Database '{0}' Successfully!", db_name);
    }

    return true;
  }

  bool manager::create_db() {
    AUTOLOG_ST

    try {
      std::string create_db = get_sql_file("sqlite/create_db.sql");

      char* messaggeError;
      int exit = sqlite3_exec(db_handler_, create_db.c_str(), NULL, 0, &messaggeError);

      if (exit != SQLITE_OK) {
        log()->error("SQL error: {0}", messaggeError);
        sqlite3_free(messaggeError);
      } else {
        log()->info("Database created Successfully!");
        return true;
      }
    } catch (const std::exception& e) {
      log()->error("Error: {0}", e.what());
    }
    return false;
  }

  bool manager::execute_query(const char* sql_query) {
    static size_t query_id = 1;
    const size_t current_query_id = query_id++;

    log()->debug("execute_query[{0}] started....", current_query_id);
    log()->trace("query[{0}]: {1}", current_query_id, sql_query);
    try {
      char* messaggeError;
      int exit = sqlite3_exec(db_handler_, sql_query, NULL, 0, &messaggeError);

      if (exit == SQLITE_OK) {
        log()->debug("execute_query[{0}] succeed.", current_query_id);
        return true;
      }

      log()->error("execute_query[{0}] failed, exit code {1}: {2}", current_query_id, exit, messaggeError);
      sqlite3_free(messaggeError);
    } catch (const std::exception& e) {
      log()->error("execute_query[{0}] failed: {1}", current_query_id, e.what());
    }
    return false;
  }

  bool manager::get_stored_setting(common::setting& setting) {
    AUTOLOG
    const char* sql_query = "SELECT `value` FROM `settings` WHERE `key`=?";
    sqlite3_stmt* stmt = prapare_statement(sql_query, setting.key);
    if (!stmt || !execute_query(sql_query)) {
      sqlite3_finalize(stmt);
      return false;
    }

    setting.value = (char*)sqlite3_column_text(stmt, 0);

    sqlite3_finalize(stmt);
    return true;
  }

  std::optional<std::vector<common::setting>> manager::get_stored_settings() {
    AUTOLOG
    const char* sql_query = "SELECT `key`, `value` FROM `settings`";
    sqlite3_stmt* stmt = prapare_statement(sql_query);
    if (!stmt || !execute_query(sql_query)) {
      sqlite3_finalize(stmt);
      return std::nullopt;
    }

    std::vector<common::setting> result;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
      common::setting item;
      item.key = sqlite3_column_int(stmt, 0);
      item.value = (char*)sqlite3_column_text(stmt, 1);
      result.emplace_back(item);
    }

    sqlite3_finalize(stmt);
    return result;
  }

  bool manager::set_stored_setting(const common::setting& setting) {
    AUTOLOG
    const char* sql_query = "INSERT INTO `settings`(`key`, `value`) VALUES (?,?)";
    sqlite3_stmt* stmt = prapare_statement(sql_query, setting.key, setting.value);
    if (!stmt || !execute_query(sql_query)) {
      sqlite3_finalize(stmt);
      return false;
    }

    int last_id = sqlite3_last_insert_rowid(db_handler_);
    log()->debug("set_stored_setting succeed. id = {0}", last_id);

    sqlite3_finalize(stmt);
    return true;
  }

  bool manager::get_info_source(common::source& info_source) {
    AUTOLOG
    const char* sql_query;
    sqlite3_stmt* stmt;
    if (info_source.id > 0) {
      sql_query =
          "SELECT `id`, `name`, `url`, `source_type_id`, `filter`, `filter_startes_with` FROM `source` WHERE `id`=?";
      stmt = prapare_statement(sql_query, info_source.id);
    } else if (!info_source.name.empty()) {
      sql_query =
          "SELECT `id`, `name`, `url`, `source_type_id`, `filter`, `filter_startes_with` FROM `source` WHERE `name`=?";
      stmt = prapare_statement(sql_query, info_source.name);
    } else if (!info_source.url.empty()) {
      sql_query =
          "SELECT `id`, `name`, `url`, `source_type_id`, `filter`, `filter_startes_with` FROM `source` WHERE `url`=?";
      stmt = prapare_statement(sql_query, info_source.url);
    } else {
      return false;
    }

    if (!stmt || !execute_query(sql_query)) {
      sqlite3_finalize(stmt);
      return false;
    }

    info_source.id = sqlite3_column_int(stmt, 0);
    info_source.name = (char*)sqlite3_column_text(stmt, 1);
    info_source.url = (char*)sqlite3_column_text(stmt, 2);
    info_source.source_type_id = sqlite3_column_int(stmt, 3);
    info_source.filter = (char*)sqlite3_column_text(stmt, 4);

    sqlite3_finalize(stmt);
    return true;
  }

  std::optional<std::vector<common::source>> manager::get_info_sources() {
    AUTOLOG
    const char* sql_query =
        "SELECT `id`, `name`, `url`, `source_type_id`, `filter`, `filter_startes_with` FROM `source`";
    sqlite3_stmt* stmt = prapare_statement(sql_query);

    if (!stmt || !execute_query(sql_query)) {
      sqlite3_finalize(stmt);
      return std::nullopt;
    }

    std::vector<common::source> sources;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
      common::source info_source;
      info_source.id = sqlite3_column_int(stmt, 0);
      info_source.name = (char*)sqlite3_column_text(stmt, 1);
      info_source.url = (char*)sqlite3_column_text(stmt, 2);
      info_source.source_type_id = sqlite3_column_int(stmt, 3);
      info_source.filter = (char*)sqlite3_column_text(stmt, 4);
      sources.emplace_back(info_source);
    }

    sqlite3_finalize(stmt);
    return sources;
  }

  bool manager::set_info_source(const common::source& info_source) {
    AUTOLOG
    const char* sql_query =
        "INSERT INTO `source`(`name`, `url`, `source_type_id`, `filter`, `filter_startes_with`) VALUES (?,?,?,?,?)";
    sqlite3_stmt* stmt = prapare_statement(sql_query,
                                           info_source.name,
                                           info_source.url,
                                           info_source.source_type_id,
                                           info_source.filter,
                                           info_source.filter_startes_with);
    if (!stmt || !execute_query(sql_query)) {
      sqlite3_finalize(stmt);
      return false;
    }

    sqlite3_finalize(stmt);
    return true;
  }

  std::optional<std::vector<common::article>> manager::get_article_data(const char* sql_query, sqlite3_stmt* stmt) {
    if (!stmt || !execute_query(sql_query)) {
      sqlite3_finalize(stmt);
      return std::nullopt;
    }

    std::vector<common::article> articles;
    while (sqlite3_step(stmt) == SQLITE_ROW) {
      common::article article;
      article.id = sqlite3_column_int64(stmt, 0);
      article.datetime = sqlite3_column_int(stmt, 1);
      article.text = (char*)sqlite3_column_text(stmt, 2);
      article.source_id = sqlite3_column_int64(stmt, 3);
      article.link = (char*)sqlite3_column_text(stmt, 4);
      article.reply_to_id = sqlite3_column_int(stmt, 5);
      article.images_attached = sqlite3_column_int(stmt, 6) > 0;

      articles.emplace_back(article);
    }

    sqlite3_finalize(stmt);
    for (auto& article: articles) {
      if (!article.images_attached) {
        continue;
      }

      const char* sql_query_image = "SELECT `data` FROM `articles` WHERE `article_id` = ?";
      sqlite3_stmt* stmt_image = prapare_statement(sql_query_image, article.id);
      if (!stmt || !execute_query(sql_query_image)) {
        log()->warning("Failed to get article {} image data", article.id);
        sqlite3_finalize(stmt_image);
        continue;
      }

      common::article::image_t image;
      // image.data = sqlite3_column_blob(stmt_image, 0);
      article.images.emplace_back(image);
      sqlite3_finalize(stmt);
    }

    return articles;
  }

  bool manager::get_article(common::article& article){AUTOLOG}

  std::optional<std::vector<common::article>> manager::get_articles() {
    AUTOLOG
    const char* sql_query = "SELECT `id`, `datetime`, `text`, `source_id`, `link`, `reply_to_id`, "
                            "`images_attached` FROM `articles`";
    sqlite3_stmt* stmt = prapare_statement(sql_query);

    return get_article_data(sql_query, stmt);
  }

  std::optional<std::vector<common::article>> manager::get_articles(int timestamp_begin) {
    AUTOLOG
    const char* sql_query = "SELECT `id`, `datetime`, `text`, `source_id`, `link`, `reply_to_id`, "
                            "`images_attached` FROM `articles` WHERE `datetime` > ?";
    sqlite3_stmt* stmt = prapare_statement(sql_query, timestamp_begin);
    return get_article_data(sql_query, stmt);
  }

  std::optional<std::vector<common::article>> manager::get_articles(int timestamp_begin, int timestamp_end) {
    AUTOLOG
    const char* sql_query = "SELECT `id`, `datetime`, `text`, `source_id`, `link`, `reply_to_id`, "
                            "`images_attached` FROM `articles` WHERE `datetime` > ? AND `datetime` <?";
    sqlite3_stmt* stmt = prapare_statement(sql_query, timestamp_begin, timestamp_end);
    return get_article_data(sql_query, stmt);
  }

  std::optional<std::vector<common::article>> manager::get_articles_by_source(int source_id) {
    AUTOLOG
    const char* sql_query = "SELECT `id`, `datetime`, `text`, `source_id`, `link`, `reply_to_id`, "
                            "`images_attached` FROM `articles` WHERE `source_id` = ?";
    sqlite3_stmt* stmt = prapare_statement(sql_query, source_id);
    return get_article_data(sql_query, stmt);
  }

  std::optional<std::vector<common::article>> manager::get_articles_by_source(int source_id, int timestamp_begin) {
    AUTOLOG
    const char* sql_query = "SELECT `id`, `datetime`, `text`, `source_id`, `link`, `reply_to_id`, "
                            "`images_attached` FROM `articles` WHERE `source_id` = ? AND `datetime` > ?";
    sqlite3_stmt* stmt = prapare_statement(sql_query, source_id, timestamp_begin);
    return get_article_data(sql_query, stmt);
  }

  std::optional<std::vector<common::article>> manager::get_articles_by_source(int source_id,
                                                                              int timestamp_begin,
                                                                              int timestamp_end) {

    AUTOLOG
    const char* sql_query =
        "SELECT `id`, `datetime`, `text`, `source_id`, `link`, `reply_to_id`, "
        "`images_attached` FROM `articles` WHERE `source_id` = ? AND `datetime` > ? AND `datetime` <?";
    sqlite3_stmt* stmt = prapare_statement(sql_query, source_id, timestamp_begin, timestamp_end);
    return get_article_data(sql_query, stmt);
  }

  bool manager::set_article(const common::article& article) {
    AUTOLOG
    const char* sql_query = "INSERT INTO `articles`(`id`, `datetime`, `text`, `source_id`, `link`, `reply_to_id`, "
                            "`images_attached`) VALUES (?,?,?,?,?,?,?)";
    sqlite3_stmt* stmt = prapare_statement(sql_query);
    if (!stmt || !execute_query(sql_query)) {
      sqlite3_finalize(stmt);
      return false;
    }

    int last_id = sqlite3_last_insert_rowid(db_handler_);
    log()->debug("set_stored_setting succeed. id = {0}", last_id);

    sqlite3_finalize(stmt);

    for (const auto& image: article.images) {
      const char* sql_query_images = "INSERT INTO `images`(`article_id`, `data`) VALUES (?,?)";
      sqlite3_stmt* stmt_images = prapare_statement(sql_query_images, last_id, image.url);
      if (!stmt_images || !execute_query(sql_query_images)) {
        log()->error("Error occurred while uploading image for article {0}!", article.id);
      }

      sqlite3_finalize(stmt_images);
    }
    return true;
  }

  bool manager::set_articles(const std::vector<common::article>& articles) {
    AUTOLOG
    for (const auto& article: articles) {
      set_article(article);
    }
    return true;
  }
} // namespace gazeta::storage::db::sqlite
