#pragma once
#include "base_controller.h"
#include "info_controller/article.h"
#include "info_controller/source.h"

namespace gazeta::info_controller::controllers {

class controller_ria : public base_controller {
public:
  virtual ~controller_ria();
  std::vector<article> get_n_articles(int to_read);
};
} // namespace gazeta::info_controller::controllers
