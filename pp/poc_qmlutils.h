#ifndef POC_QMLUTILS_H
#define POC_QMLUTILS_H
/*----------------------------------------------------------------------
|    includes
+---------------------------------------------------------------------*/
#include <QObject>
#include <QStringList>

/*----------------------------------------------------------------------
|    POC_QMLUtils class
+---------------------------------------------------------------------*/
class POC_QMLUtils : public QObject
{
   Q_OBJECT
public:
   explicit POC_QMLUtils(QObject* parent = 0);

   Q_INVOKABLE QString getHomeDir();
   Q_INVOKABLE QString getPathFromUri(QString uri);
   Q_INVOKABLE QString getFileExtension(QString file);

   // File methods.
   Q_INVOKABLE bool isSupportedImage(QString file);
   Q_INVOKABLE bool isSupportedVideo(QString file);
   Q_INVOKABLE bool isSupportedAudio(QString file);

   // Gallery methods.
   Q_INVOKABLE QString getNextImage(QString imageAbsPath);
   Q_INVOKABLE QString getPrevImage(QString imageAbsPath);
   Q_INVOKABLE QStringList getSupportedImageExtensions();
};

#endif // POC_QMLUTILS_H
