#include "window.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Main window creation and display
    Window w;
    w.show();

    // Enter the main event loop
    return a.exec();
}
