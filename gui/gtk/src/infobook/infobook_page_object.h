#pragma once
#include <gtkmm.h>

#include "info_controller/controller_types.h"
#include "info_controller/info_controller.h"

namespace gazeta::gui {
  class InfobookPageObject final: public Gtk::ScrolledWindow {
public:
    InfobookPageObject(info_controller::controller_types controller_type);
    ~InfobookPageObject() override;

    void load();

protected:
    class PageColumns: public Gtk::TreeModel::ColumnRecord {
  public:
      PageColumns() {
        add(m_col_datetime);
        add(m_col_message);
      }

      Gtk::TreeModelColumn<Glib::ustring> m_col_datetime;
      Gtk::TreeModelColumn<Glib::ustring> m_col_message;
    };

private:
    const info_controller::controller_types controller_type_;
    info_controller::info_controller controller_;

    PageColumns m_columns;
    Gtk::TreeView m_TreeView;
    Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
    std::unordered_set<size_t> used_articles_ids_;

    std::atomic_bool is_loading_ = false;
    std::unique_ptr<std::thread> load_data_thread_ptr_;
  };
} // namespace gazeta::gui
