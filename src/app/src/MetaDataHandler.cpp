/**
 * @file MetaDataHandler.cpp
 * @brief Implements the MetaDataHandler class.
 * @author Muddyblack
 * @date 21.02.2024
 */
#include <QImageReader>
#include <QImageWriter>
#include <QFile>
#include <QImage>

#include <iostream>
#include <map>
#include <string>

#include <iostream>
#include <fstream>
#include <cstdint>
#include <map>
#include <string>

#include <MetaDataHandler.h>
#include <PNGMeta.h>

MetaDataHandler::MetaDataHandler() {
    // Constructor
}

QMap<QString, QString> MetaDataHandler::readMetadata(const QString &filePath) {
    qDebug() << "Reading metadata from file: " << filePath;
    std::map<std::string, std::string> metadata = PNGMeta::readPNGHeader(filePath.toStdString());

    QMap<QString, QString> qMetadata;
    for (const auto &pair : metadata) {
        qMetadata.insert(QString::fromStdString(pair.first), QString::fromStdString(pair.second));
    }

    return qMetadata;
}

void MetaDataHandler::writeMetadata(const QString &filePath, const QMap<QString, QString> &metadata) {
    qDebug() << "Writing metadata to file: " << filePath;
    std::map<std::string, std::string> properties;
    QMapIterator<QString, QString> i(metadata);
    while (i.hasNext()) {
        i.next();
        properties.insert(std::make_pair(i.key().toStdString(), i.value().toStdString()));
    }
    qDebug() << properties.size() << " metadata properties to write", properties;
    PNGMeta::writePNGHeader(filePath.toStdString(), properties);
}