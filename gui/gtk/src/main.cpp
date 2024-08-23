#include "main_window.h"
#include <gtkmm/application.h>

int main(int argc, char* argv[]) {
  gazeta::gui::initialize_logging();
  AUTOLOG_GTK;
#if GTKMM_MAJOR_VERSION == 4

  auto app = Gtk::Application::create("org.gtkmm.example");
  return app->make_window_and_run<gazeta::gui::MainWIndow>(argc, argv);

#elif GTKMM_MAJOR_VERSION == 3

  auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");
  gazeta::MainWIndow main_window;
  return app->run(main_window);

#else

  return EXIT_FAILURE;
#endif
  return EXIT_SUCCESS;
}
