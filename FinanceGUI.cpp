
#include <QApplication>
#include "FinanceWindow.h"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    FinanceWindow window;
    window.show();

    return app.exec();
}
