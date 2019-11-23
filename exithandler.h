#ifndef EXITHANDLER_HH_
#define EXITHANDLER_HH_
#include <QObject>
#include <QApplication>
class ExitHandler : public QObject {
private:
    static QApplication *_app;
    static int _counter;
public:
    ExitHandler();
    static void setApplication(QApplication *app);
    static void setup();
    static void run(int s);
};
#endif // EXITHANDLER_HH_