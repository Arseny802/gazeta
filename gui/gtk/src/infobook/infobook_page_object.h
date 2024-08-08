#pragma once
#include <gtkmm.h>

#include "article_object.h"
#include "info_controller/controller_types.h"

namespace gazeta::gui
{
  class InfobookPageObject final : public Gtk::ScrolledWindow
  {
  public:
    InfobookPageObject(info_controller::controller_types controller_type);
    ~InfobookPageObject() override;

    void load();

  protected:
    class PageColumns : public Gtk::TreeModel::ColumnRecord
    {
    public:
      PageColumns()
      {
        add(m_col_datetime);
        add(m_col_message);
      }

      Gtk::TreeModelColumn<Glib::ustring> m_col_datetime;
      Gtk::TreeModelColumn<Glib::ustring> m_col_message;
    };

  private:
    const info_controller::controller_types controller_type_;

    PageColumns m_columns;
    Gtk::TreeView m_TreeView;
    Glib::RefPtr<Gtk::ListStore> m_refTreeModel;
  };
} // namespace gazeta::gui
