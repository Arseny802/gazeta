#include "pch.h"
#include "main_window.h"

#include <gtkmm.h>

namespace gazeta::gui {
  MainWIndow::MainWIndow() {
    AUTOLOG_GTK;
    set_title("Gazeta");
    set_default_size(2560, 1080);

    m_VBox = Gtk::Box(Gtk::Orientation::VERTICAL);

    set_child(m_VBox);
    m_VBox.append(m_InfobookObject);

    widget_map = new GtkWidget();
  }

  MainWIndow::~MainWIndow() {
    AUTOLOG_GTK;
  }

} // namespace gazeta::gui
