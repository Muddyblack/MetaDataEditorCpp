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
#include <fstream>
#include <cstdint>
#include <map>
#include <string>

#include <MetaDataHandler.h>


MetaDataHandler::MetaDataHandler() {
    // Constructor
}

std::map<std::string, std::string> MetaDataHandler::readPNGHeader(const std::string& filename) {
    std::map<std::string, std::string> metadata;
    std::ifstream file(filename, std::ios::binary);
    
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return metadata;
    }

    PNGHeader header;
    file.read(reinterpret_cast<char*>(&header), sizeof(header));

    if (!file) {
        std::cerr << "Error: Unable to read PNG header from file " << filename << std::endl;
        return metadata;
    }

    // Check PNG signature
    if (header.signature[0] != 0x89 || header.signature[1] != 'P' || header.signature[2] != 'N' ||
        header.signature[3] != 'G' || header.signature[4] != 0x0D || header.signature[5] != 0x0A ||
        header.signature[6] != 0x1A || header.signature[7] != 0x0A) {
        std::cerr << "Error: File " << filename << " is not a valid PNG file" << std::endl;
        return metadata;
    }

    // Add header information to metadata
    metadata["Width"] = std::to_string(header.width);
    metadata["Height"] = std::to_string(header.height);
    metadata["Bit Depth"] = std::to_string(static_cast<int>(header.bitDepth));
    metadata["Color Type"] = std::to_string(static_cast<int>(header.colorType));
    metadata["Compression Method"] = std::to_string(static_cast<int>(header.compressionMethod));
    metadata["Filter Method"] = std::to_string(static_cast<int>(header.filterMethod));
    metadata["Interlace Method"] = std::to_string(static_cast<int>(header.interlaceMethod));

    file.close();

    return metadata;
}

QMap<QString, QString> MetaDataHandler::readMetadata(const QString &filePath) {
    qDebug() << "Reading metadata from file: " << filePath;
    std::map<std::string, std::string> metadata = readPNGHeader(filePath.toStdString());

    QMap<QString, QString> qMetadata;
    for (const auto &pair : metadata) {
        qMetadata.insert(QString::fromStdString(pair.first), QString::fromStdString(pair.second));
    }

    return qMetadata;
}

void MetaDataHandler::writePNGHeader(const std::string& filename, const std::map<std::string, std::string>& properties) {
    std::ofstream file(filename, std::ios::binary);
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << " for writing" << std::endl;
        return;
    }

    // PNG signature
    file.put(0x89);
    file.put('P');
    file.put('N');
    file.put('G');
    file.put(0x0D);
    file.put(0x0A);
    file.put(0x1A);
    file.put(0x0A);

    // IHDR chunk
    uint32_t width = std::stoi(properties.at("Width"));
    uint32_t height = std::stoi(properties.at("Height"));
    uint8_t bitDepth = std::stoi(properties.at("Bit Depth"));
    uint8_t colorType = std::stoi(properties.at("Color Type"));
    uint8_t compressionMethod = std::stoi(properties.at("Compression Method"));
    uint8_t filterMethod = std::stoi(properties.at("Filter Method"));
    uint8_t interlaceMethod = std::stoi(properties.at("Interlace Method"));

    uint32_t chunkLength = 13;
    file.put(chunkLength >> 24);
    file.put((chunkLength >> 16) & 0xFF);
    file.put((chunkLength >> 8) & 0xFF);
    file.put(chunkLength & 0xFF);
    file.put('I');
    file.put('H');
    file.put('D');
    file.put('R');
    file.put(bitDepth);
    file.put(colorType);
    file.put(compressionMethod); // Compression method
    file.put(filterMethod); // Filter method
    file.put(interlaceMethod); // Interlace method (0 for no interlace, 1 for Adam7 interlace)
    file.put(0); // CRC (ignored)

    // Write width and height
    file.put(width >> 24);
    file.put((width >> 16) & 0xFF);
    file.put((width >> 8) & 0xFF);
    file.put(width & 0xFF);
    file.put(height >> 24);
    file.put((height >> 16) & 0xFF);
    file.put((height >> 8) & 0xFF);
    file.put(height & 0xFF);

    // TODO Calculate and write CRC for IHDR chunk

    file.close();
    std::cout << "PNG file with header written successfully: " << filename << std::endl;
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
    writePNGHeader(filePath.toStdString(), properties);
}