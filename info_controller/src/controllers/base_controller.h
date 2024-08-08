#pragma once
#include "info_controller/article.h"
#include "info_controller/source.h"

namespace gazeta::info_controller::controllers
{
  class base_controller
  {
  public:
    virtual ~base_controller();

    virtual std::vector<article> get_n_articles(int to_read) = 0;

  protected:
    std::vector<article> read_n_articles_from_tweb(const source &src, int to_read);
  };
} // namespace gazeta::info_controller::controllers
