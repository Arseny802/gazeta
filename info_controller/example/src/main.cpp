#include "pch.h"
#include "info_controller/info_controller.h"

int main()
{
  using namespace gazeta::info_controller;
  example::initialize_logging();
  AUTOLOG;

  info_controller controller(controller_types::ria);
  auto result = controller.get_n_articles(100);

  return 0;
}
