/**
 * @file MetaDataHandler.h
 * @brief Handles reading and writing metadata.
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
     * @struct PNGHeader
     * @brief Represents the header of a PNG file.
     */
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

    /**
     * @struct PNGChunk
     * @brief Represents a chunk of a PNG file.
     */
    struct PNGChunk {
        uint32_t length;
        uint8_t type[4];
        uint8_t* data;
        uint32_t crc;
    };

    /**
     * @brief Constructs a new MetaDataHandler object.
     */
    MetaDataHandler();

    /**
     * @brief Reads the PNG header from a PNG file.
     * @param filename The name of the file to read from.
     * @return A map of metadata keys to values.
     */
    std::map<std::string, std::string> readPNGHeader(const std::string& filename);


    /**
     * @brief Reads metadata from a file.
     * @param filePath The path of the file to read from.
     * @return A map of metadata keys to values.
     */
    QMap<QString, QString> readMetadata(const QString &filePath);

    // Writes metadata to the image file at the given path
    // The metadata to write is given as a map where the keys are the metadata keys and the values are the metadata values
   
    /**
     * @brief Writes a PNG header to a file.
     * @param filename The name of the file to write to.
     * @param properties The metadata to write.
     */
    void writePNGHeader(const std::string& filename, const std::map<std::string, std::string>& properties);
    
    /**
     * @brief Writes metadata to a file.
     * @param filePath The path of the file to write to.
     * @param metadata The metadata to write.
     */
    void writeMetadata(const QString &filePath, const QMap<QString, QString> &metadata);
};

#endif // MetaDataHandler_H