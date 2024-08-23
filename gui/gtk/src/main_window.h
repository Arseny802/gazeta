#pragma once
#include <gtkmm.h>

#include "infobook/infobook_object.h"

namespace gazeta::gui {
  class MainWIndow final: public Gtk::Window {
public:
    MainWIndow();
    ~MainWIndow() override;

protected:
    void on_button_quit();
    void on_notebook_switch_page(Gtk::Widget* page, guint page_num);

    Gtk::Box m_VBox;
    gazeta::gui::InfobookObject m_InfobookObject;

    GtkWidget* widget_map;
  };
} // namespace gazeta::gui
