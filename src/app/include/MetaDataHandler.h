#ifndef MetaDataHandler_H
#define MetaDataHandler_H

#include <QMap>
#include <QString>

class MetaDataHandler {
public:
    MetaDataHandler();

    // Reads metadata from the image file at the given path
    // Returns a map where the keys are the metadata keys and the values are the metadata values
    QMap<QString, QString> readMetadata(const QString &filePath);

    // Writes metadata to the image file at the given path
    // The metadata to write is given as a map where the keys are the metadata keys and the values are the metadata values
    void writeMetadata(const QString &filePath, const QMap<QString, QString> &metadata);
};

#endif // MetaDataHandler_H