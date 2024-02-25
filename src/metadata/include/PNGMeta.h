/**
 * @file PNGMeta.h
 * @brief Handles reading and writing metadata for PNG.
 * @author Muddyblack
 * @date 26.02.2024
 */
#ifndef PNGMeta_H
#define PNGMeta_H

/**
 * @class PNGMeta_H
 * @brief Handles reading and writing metadata from/to PNG-files.
 */
class PNGMeta {
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
     * @brief Reads the PNG header from a PNG file.
     * @param filename The name of the file to read from.
     * @return A map of metadata keys to values.
     */
    static std::map<std::string, std::string> readPNGHeader(const std::string& filename);

    /**
     * @brief Writes a PNG header to a file.
     * @param filename The name of the file to write to.
     * @param properties The metadata to write.
     */
    static void writePNGHeader(const std::string& filename, const std::map<std::string, std::string>& properties);
    
};

#endif // PNGMeta_H