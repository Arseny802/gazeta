#pragma once
#include "common/article.h"
#include "common/source.h"
#include "controller_types.h"

#include <memory>
#include <vector>

namespace gazeta::storage {
  class db_manager;
} // namespace gazeta::storage

namespace gazeta::info_controller::controllers {
  class base_controller;
} // namespace gazeta::info_controller::controllers

namespace gazeta::info_controller {
  class info_controller final {
public:
    info_controller(controller_types controller_type);
    ~info_controller();

    bool available() const noexcept;

    std::vector<common::article> get_n_articles(size_t to_read);
    std::vector<common::article> get_articles_afer(size_t to_read);

private:
    controller_types controller_type_;
    std::shared_ptr<controllers::base_controller> controller_pimpl_;

    std::unique_ptr<storage::db_manager> db_manager_pimpl_;
    const static std::string_view db_name_;
  };
} // namespace gazeta::info_controller
