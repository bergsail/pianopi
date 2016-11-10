
#ifndef POC_UTILS_H
#define POC_UTILS_H

/*----------------------------------------------------------------------
|    includes
+---------------------------------------------------------------------*/
#include <QHash>
#include <QString>

/*----------------------------------------------------------------------
|    POC_Utils class
+---------------------------------------------------------------------*/
class POC_Utils
{
public:
   static const QStringList& getSupportedImageFormats();
   static const QStringList& getSupportedImageExtensions();
   static const QStringList& getSupportedVideoExtensions();
   static const QStringList& getSupportedAudioExtensions();

   static const QStringList getFilterFromExts(const QStringList& extensions);

   static bool isSupportedVideo(QString file);
   static bool isSupportedImage(QString file);
   static bool isSupportedAudio(QString file);

   static void listSupportedImageFormats();
   static void listSupportedImageExtensions();

   static const QHash<QString, QString>& getMimeToExtMap();

   static QString getFileExtension(const QString& file);
};

#endif // POC_UTILS_H
