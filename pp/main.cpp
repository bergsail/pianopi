/*----------------------------------------------------------------------
|    includes
+---------------------------------------------------------------------*/
#include <QtGui/QGuiApplication>
#include <QQuickView>
#include <QQuickItem>
#include <QQmlEngine>
#include <QQmlContext>

#include "poc_utils.h"
#include "poc_qmlutils.h"


/*----------------------------------------------------------------------
|    main
+---------------------------------------------------------------------*/
int main(int argc, char* argv[])
{
    QGuiApplication app(argc, argv);

    // Utility.
    POC_QMLUtils qmlUtils;

    QQuickView view;
    view.engine()->rootContext()->setContextProperty("utils", &qmlUtils);
    view.setSource(QUrl("/home/pi/PianoPi/qml/main.qml"));
    view.setResizeMode(QQuickView::SizeRootObjectToView);
#ifdef RASPBERRY
    view.showFullScreen();
#else
    view.resize(800, 400);
    view.show();
#endif // RASPBERRY
    qApp->connect(view.engine(), SIGNAL(quit()), qApp, SLOT(quit()));

    // If file path is provided from the command line, I start the player
    // immediately.
    QStringList args = app.arguments();
    if (args.size() > 1) {
       QFile f(args.at(1));
       if (!f.exists())
          qWarning("File provided does not exist.");
       else {
          QObject* rootObject  = dynamic_cast<QObject*>(view.rootObject());
          QObject* mediaOutput = rootObject->findChild<QObject*>("mediaOutput");
          //mediaPlayer->setProperty("source", QUrl::fromLocalFile(args.at(1)));
          QMetaObject::invokeMethod(mediaOutput, "showLocalMedia", Q_ARG(QVariant, args.at(1)));
       }
    }

    return app.exec();
}
