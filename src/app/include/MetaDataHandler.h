#ifndef MetaDataHandler_H
#define MetaDataHandler_H

#include <QMap>
#include <QString>
#include <QImage>

class MetaDataHandler {
public:
    struct PNGHeader {
        uint8_t signature[8];
        uint32_t width;
        uint32_t height;
        uint8_t bitDepth;
        uint8_t colorType;
        uint8_t compressionMethod;
        uint8_t filterMethod;
        uint8_t interlaceMethod;
    };

    struct PNGChunk {
        uint32_t length;
        uint8_t type[4];
        uint8_t* data;
        uint32_t crc;
    };

    MetaDataHandler();

    std::map<std::string, std::string> readPNGHeader(const std::string& filename);


    // Reads metadata from the image file at the given path
    // Returns a map where the keys are the metadata keys and the values are the metadata values
    QMap<QString, QString> readMetadata(const QString &filePath);

    // Writes metadata to the image file at the given path
    // The metadata to write is given as a map where the keys are the metadata keys and the values are the metadata values
    void writePNGHeader(const std::string& filename, const std::map<std::string, std::string>& properties);
    void writeMetadata(const QString &filePath, const QMap<QString, QString> &metadata, const QImage &image);
};

#endif // MetaDataHandler_H