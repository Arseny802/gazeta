#include "pch.h"
#include "article_object.h"

namespace gazeta::gui
{
  ArticleObject::ArticleObject(info_controller::article &&article)
      : Gtk::Label(format_article_message()),
        article_(std::move(article)),
        m_property_label(*this, "label", format_article_message())
  {
  }

  Glib::RefPtr<ArticleObject> ArticleObject::create(info_controller::article &&article)
  {
    return Glib::make_refptr_for_instance(new ArticleObject(std::move(article)));
  }

  int ArticleObject::get_id() const
  {
    return article_.id;
  }

  Glib::PropertyProxy<Glib::ustring> ArticleObject::property_label()
  {
    return m_property_label.get_proxy();
  }

  int ArticleObject::compare(const Glib::RefPtr<const ArticleObject> &a,
                             const Glib::RefPtr<const ArticleObject> &b)
  {
    if (!a || !b)
    {
      log()->warning("ArticleObject::compare(): Empty RefPtr");
      return 0;
    }

    return a->get_id() - b->get_id();
  }

  Glib::ustring ArticleObject::format_article_message() const
  {
    Glib::ustring label_text = article_.text;
    return label_text;
  }
} // namespace gazeta::gui