#include "pianorollplugin.h"
#include "pianoroll.h"
#include <QQmlEngine>
#include <qqml.h>
#include <QDebug>
void PianorollPlugin::registerTypes(const char *uri)
{
    qDebug(uri);
    Q_ASSERT(uri == QLatin1String("PianoRoll"));
    qmlRegisterType<PianoRoll>(uri, 1, 0, "PianoRoll");
}
