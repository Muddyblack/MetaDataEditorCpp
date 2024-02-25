/**
 * @file MetaDataHandler.h
 * @brief Handles reading and writing metadata for application.
 * @author Muddyblack
 * @date 21.02.2024
 */
#ifndef MetaDataHandler_H
#define MetaDataHandler_H

#include <QMap>
#include <QString>
#include <QImage>

/**
 * @class MetaDataHandler
 * @brief Handles reading and writing metadata from/to files.
 */
class MetaDataHandler {
public:
    /**
     * @brief Constructs a new MetaDataHandler object.
     */
    MetaDataHandler();

    /**
     * @brief Reads metadata from a file.
     * @param filePath The path of the file to read from.
     * @return A map of metadata keys to values.
     */
    QMap<QString, QString> readMetadata(const QString &filePath);

    /**
     * @brief Writes metadata to a file.
     * @param filePath The path of the file to write to.
     * @param metadata The metadata to write.
     */
    void writeMetadata(const QString &filePath, const QMap<QString, QString> &metadata);
};

#endif // MetaDataHandler_H