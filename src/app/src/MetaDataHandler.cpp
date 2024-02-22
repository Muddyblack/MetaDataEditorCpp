#include <MetaDataHandler.h>
#include <QImageReader>
#include <QImageWriter>
#include <QFile>
#include <QImage>

MetaDataHandler::MetaDataHandler() {
    // Constructor
}

QMap<QString, QString> MetaDataHandler::readMetadata(const QString &filePath) {
    QMap<QString, QString> metadata;

    QImageReader reader(filePath);
    foreach (QString key, reader.textKeys()) {
        metadata.insert(key, reader.text(key));
    }

    return metadata;
}

void MetaDataHandler::writeMetadata(const QString &filePath, const QMap<QString, QString> &metadata, const QImage &image) {
     qDebug() << "Writing metadata to file: " << filePath;

    QFile file(filePath);
    if (!file.exists()) {
        file.open(QIODevice::WriteOnly);
        file.close();
    }

    QImageWriter writer(filePath);
    writer.setText("Software", "MetaDataEditor");
    QMapIterator<QString, QString> i(metadata);
    while (i.hasNext()) {
        i.next();
        writer.setText(i.key(), i.value());
    }

    if (!writer.write(image)) {
        qCritical() << "Error writing metadata to file";
    }
}