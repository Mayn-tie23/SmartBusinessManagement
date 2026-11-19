
#include <QApplication>
#include <QWidget>

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    QWidget window;
    window.setWindowTitle("Smart Business Management");
    window.resize(800, 500);
    window.show();

    return app.exec();
}
