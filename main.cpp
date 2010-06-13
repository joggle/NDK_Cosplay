#include <QtGui>

#include "DialogAccess.h"

int main(int argc, char** argv)
{
  QApplication app(argc, argv);
  app.setOrganizationName("Nan Desu Kan Denver");
  app.setApplicationName("NDK Costume Contest Main");
  DialogAccess access;
  /*if (access.result() == QDialog::Accepted)
  {
    if (access.permission() == DialogAccess::SuperUser)
    {
    } else if (access.permission() == DialogAccess::Judge)
    {
    }
  }*/

  // MainWidget bla;
  // bla.show();
  access.show();
  return app.exec();
}

