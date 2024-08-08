#include "pch.h"
#include "infobook_object.h"

namespace gazeta::gui
{
  InfobookObject::InfobookObject()
      : info_controller_pages({
            {InfobookPageObject(info_controller::controller_types::undefined)},
            {InfobookPageObject(info_controller::controller_types::ria)},
        })
  {
    AUTOLOG_GTK;
    info_controller_map["RIA"] = info_controller::controller_types::ria;
    info_controller_map["Undefined"] = info_controller::controller_types::undefined;

    for (auto &item : info_controller_map)
    {
      int page_id = append_page(info_controller_pages[int(item.second)], item.first);
      info_controller_page_id_map[page_id] = item.first;
    }

    set_expand();
    signal_switch_page().connect(sigc::mem_fun(
        *this, &InfobookObject::on_notebook_switch_page));
  }

  InfobookObject::~InfobookObject()
  {
    AUTOLOG_GTK;
  }

  void InfobookObject::on_notebook_switch_page(Gtk::Widget * /* page */, guint page_num)
  {
    AUTOLOG_GTK;
    log()->info("Switched to tab with index {0}", page_num);

    const auto page_controller = info_controller_page_id_map.find(page_num);
    if (page_controller == info_controller_page_id_map.cend())
    {
      log()->warning("Page {0} not found in controllers!", page_num);
      return;
    }

    try
    {
      const std::string &page_id = page_controller->second;
      const int arr_index = static_cast<int>(info_controller_map[page_id]);
      info_controller_pages[arr_index].load();
    }
    catch (const std::exception &e)
    {
      std::cerr << e.what() << '\n';
      log()->error("Exception on notebook_switch_page(): {0}", e.what());
    }
  }

} // namespace gazeta::gui
