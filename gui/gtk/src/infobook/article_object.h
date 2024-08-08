#pragma once

#include <glibmm.h>
#include "info_controller/article.h"

namespace gazeta::gui
{
  class ArticleObject : public Gtk::Label
  {
  public:
    static Glib::RefPtr<ArticleObject> create(info_controller::article &&article);

    int get_id() const;
    Glib::PropertyProxy<Glib::ustring> property_label();

    static int compare(const Glib::RefPtr<const ArticleObject> &a,
                       const Glib::RefPtr<const ArticleObject> &b);

  protected:
    ArticleObject(info_controller::article &&article);

  private:
    Glib::ustring format_article_message() const;
  
    const info_controller::article article_;
    Glib::Property<Glib::ustring> m_property_label;
  };
} // namespace gazeta::gui
