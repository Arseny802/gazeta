#include "pch.h"
#include "infobook_page_object.h"

#include "info_controller/info_controller.h"

namespace gazeta::gui {
  InfobookPageObject::InfobookPageObject(info_controller::controller_types controller_type):
      controller_type_(controller_type),
      controller_(info_controller::info_controller(controller_type_)) {
    AUTOLOG_GTK;

    set_policy(Gtk::PolicyType::AUTOMATIC, Gtk::PolicyType::AUTOMATIC);
    set_hexpand(true);
    set_vexpand(true);
    set_halign(Gtk::Align::FILL);
    set_valign(Gtk::Align::FILL);
    set_child(m_TreeView);

    m_refTreeModel = Gtk::ListStore::create(m_columns);
    m_TreeView.set_model(m_refTreeModel);

    m_TreeView.append_column("Date and Time", m_columns.m_col_datetime);
    m_TreeView.append_column("Message", m_columns.m_col_message);

    set_margin(5);
  }

  InfobookPageObject::~InfobookPageObject() {
    AUTOLOG_GTK;
    if (load_data_thread_ptr_ && load_data_thread_ptr_->joinable()) {
      load_data_thread_ptr_->join();
    }
  }

  void InfobookPageObject::load() {
    AUTOLOG_GTK;
    if (!controller_.available()) {
      log()->warning("Controller with type {} is not available!", int(controller_type_));
      return;
    }

    if (is_loading_.load()) {
      return;
    }

    is_loading_.store(true);
    load_data_thread_ptr_ = std::make_unique<std::thread>([this] {
      try {
        log()->info("Loading data for controller_type {0}...", int(controller_type_));
        const auto result = controller_.get_n_articles(1000);
        for (const auto& item: result) {
          // Do not show articles that are not supported by the controller type
          if (!item.is_supported) {
            continue;
          }

          // Filter out articles that are not important
          if (item.text.find("❗️") == std::string::npos) {
            continue;
          }

          if (used_articles_ids_.find(item.id) != used_articles_ids_.end()) {
            continue;
          }

          Gtk::TreeModel::Row row = *(m_refTreeModel->append());
          row[m_columns.m_col_datetime] = item.get_datetime();
          row[m_columns.m_col_message] = item.text;
          used_articles_ids_.emplace(item.id);
        }
      } catch (const std::exception& e) {
        log()->error("Failed to load data for controller type {0}: {1}", int(controller_type_), e.what());
      } catch (...) {
        log()->error("Failed to load data for controller type {}", int(controller_type_));
      }

      log()->info("Load extra page info in independend thread finished.");
      is_loading_.store(false);
    });
  }

} // namespace gazeta::gui
