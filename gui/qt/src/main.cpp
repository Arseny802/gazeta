#include <QCoreApplication>
#include <QDebug>
#include <QMessageLogger>

int main(int argc, char *argv[]) {
  QCoreApplication a(argc, argv);
  qDebug() << "Hello World";
  return QCoreApplication::exec();
}