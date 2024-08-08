#pragma once
#include <gtkmm.h>

#include "infobook_page_object.h"
#include "info_controller/controller_types.h"

namespace gazeta::gui
{
  class InfobookObject final : public Gtk::Notebook
  {
  public:
    InfobookObject();
    ~InfobookObject() override;

  protected:
    void on_notebook_switch_page(Gtk::Widget *page, guint page_num);

    std::map<std::string, info_controller::controller_types> info_controller_map;
    //std::unordered_map<std::string, InfobookPageObject> info_controller_page_map;
    std::map<size_t, std::string> info_controller_page_id_map;

    std::array<InfobookPageObject, 2> info_controller_pages;
  };
} // namespace gazeta::gui
