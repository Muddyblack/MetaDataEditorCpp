/**
 * @file PNGMeta.cpp
 * @brief Implements the PNGMeta class.
 * @author Muddyblack
 * @date 26.02.2024
 */
#include <iostream>
#include <fstream>
#include <map>
#include <string>
#include <cstring>

#ifdef _WIN32
    #include <Winsock2.h> // for ntohl function
    #pragma comment(lib, "ws2_32.lib") // Link with ws2_32.lib
#elif defined(__unix__) || defined(__unix) || (defined(__APPLE__) && defined(__MACH__))
    #include <arpa/inet.h> // for ntohl function
#endif

#include <PNGMeta.h>
#include <Logger.h>

//READING METADATA
std::map<std::string, std::string> PNGMeta::readPNGMetaData(const std::string& filename) {
    std::map<std::string, std::string> metadata;

    // Read the PNG header
    std::map<std::string, std::string> header = readPNGHeader(filename);
    metadata.insert(header.begin(), header.end());

    // Read the text chunks
    // TODO refactor to use a single function for reading chunks
    std::map<std::string, std::string> textChunks = readPNGTextChunks(filename);
    metadata.insert(textChunks.begin(), textChunks.end());

    return metadata;
}

// TODO Kind of a duplicate code, can be refactored all into readPNGHeader 
std::map<std::string, std::string> PNGMeta::readPNGTextChunks(const std::string& filename) {
    std::map<std::string, std::string> textChunks;
    std::ifstream file(filename, std::ios::binary);
    
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return textChunks;
    }

    PNGChunk chunk;
    while (file.read(reinterpret_cast<char*>(&chunk.length), sizeof(chunk.length))) {
        logDebug() << "Read chunk with type " << chunk.type[0] << chunk.type[1] << chunk.type[2] << chunk.type[3] << " and length " << chunk.length;
        // Check if it's a text chunk
        if (chunk.type[0] == 't' && chunk.type[1] == 'E' && chunk.type[2] == 'X' && chunk.type[3] == 't') {
            logDebug() << "Found text chunk";
            // Assume the keyword is ASCII text, null-terminated
            std::string keyword(reinterpret_cast<char*>(chunk.data));
            // Skip null terminator
            file.seekg(1, std::ios_base::cur);
            // Read text chunk data
            std::string data(chunk.length - 1, '\0');
            file.read(reinterpret_cast<char*>(&data[0]), chunk.length - 1);
            textChunks[keyword] = data;
        } else {
            // Skip to next chunk
            file.seekg(chunk.length + 4, std::ios_base::cur); // +4 for CRC
        }
    }

    file.close();

    return textChunks;
}


std::map<std::string, std::string> PNGMeta::readPNGHeader(const std::string& filename) {
    std::map<std::string, std::string> metadata;
    std::ifstream file(filename, std::ios::binary);
    
    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << std::endl;
        return metadata;
    }

    if (!file) {
        std::cerr << "Error: Unable to read PNG header from file " << filename << std::endl;
        return metadata;
    }

    PNGHeader header;

    file.read(reinterpret_cast<char*>(&header.signature), sizeof(header.signature));

    // Check PNG signature
    if (header.signature[0] != 0x89 || header.signature[1] != 'P' || header.signature[2] != 'N' ||
        header.signature[3] != 'G' || header.signature[4] != 0x0D || header.signature[5] != 0x0A ||
        header.signature[6] != 0x1A || header.signature[7] != 0x0A) {
        std::cerr << "Error: File " << filename << " is not a valid PNG file" << std::endl;
        return metadata;
    }
    // Skip IHDR chunk length and type
    file.seekg(8, std::ios::cur);

    // Read IDHR chunk data
    file.read(reinterpret_cast<char*>(&header.width), sizeof(header.width));
    file.read(reinterpret_cast<char*>(&header.height), sizeof(header.height));
    file.read(reinterpret_cast<char*>(&header.bitDepth), sizeof(header.bitDepth));
    file.read(reinterpret_cast<char*>(&header.colorType), sizeof(header.colorType));
    file.read(reinterpret_cast<char*>(&header.compressionMethod), sizeof(header.compressionMethod));
    file.read(reinterpret_cast<char*>(&header.filterMethod), sizeof(header.filterMethod));
    file.read(reinterpret_cast<char*>(&header.interlaceMethod), sizeof(header.interlaceMethod));

    // Convert width and height from big endian to little endian
    header.width = ntohl(header.width);
    header.height = ntohl(header.height);

    // Add header information to metadata  --- equivalent to IDHR chunk
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


// WRITING METADATA
static const uint32_t crc32_table[256] = { /* Lookup table values */ };

// Function to calculate CRC32 checksum
uint32_t PNGMeta::calculate_crc32(const uint8_t *data, size_t length) {
    uint32_t crc = 0xFFFFFFFF;
    for (size_t i = 0; i < length; ++i) {
        crc = (crc >> 8) ^ crc32_table[(crc ^ data[i]) & 0xFF];
    }
    return crc ^ 0xFFFFFFFF;
}

// TODO Kind of a duplicate code, can be refactored all into writePNGHeader like has to be done in readPNGMetaData
void PNGMeta::writePNGTextChunks(const std::string& filename, const std::map<std::string, std::string>& textChunks) {
    std::fstream file(filename, std::ios::binary | std::ios::in | std::ios::out);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << " for writing" << std::endl;
        return;
    }

    // Move the file pointer to the end to append text chunks
    file.seekp(0, std::ios_base::end);

    // Write each text chunk
    for (const auto& pair : textChunks) {
        PNGChunk chunk;
        chunk.length = pair.first.size() + pair.second.size() + 1; // Keyword + Null Terminator + Data
        memcpy(chunk.type, "tEXt", 4);
        chunk.data = new uint8_t[chunk.length];
        memcpy(chunk.data, pair.first.c_str(), pair.first.size());
        chunk.data[pair.first.size()] = '\0'; // Null terminator
        memcpy(chunk.data + pair.first.size() + 1, pair.second.c_str(), pair.second.size());
        // CRC calculation here
        chunk.crc = calculate_crc32(chunk.data, chunk.length);
        
        // Write chunk length, type, and CRC
        file.write(reinterpret_cast<char*>(&chunk.length), sizeof(chunk.length));
        file.write(reinterpret_cast<char*>(&chunk.type), sizeof(chunk.type));
        file.write(reinterpret_cast<char*>(&chunk.crc), sizeof(chunk.crc));
        // Write chunk data
        file.write(reinterpret_cast<char*>(chunk.data), chunk.length);
        delete[] chunk.data;
    }

    file.close();
}

// TODO allow to save in new not yet existing file
void PNGMeta::writePNGHeader(const std::string& filename, const std::map<std::string, std::string>& properties) {
    std::fstream file(filename, std::ios::binary | std::ios::in | std::ios::out);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << " for writing" << std::endl;
        return;
    }

    PNGHeader header;

    // Skip PNG signature
    file.seekg(8, std::ios::cur);

    // Skip IHDR chunk length and type
    file.seekg(8, std::ios::cur);

    // Read the header fields individually
    file.read(reinterpret_cast<char*>(&header.width), sizeof(header.width));
    file.read(reinterpret_cast<char*>(&header.height), sizeof(header.height));
    file.read(reinterpret_cast<char*>(&header.bitDepth), sizeof(header.bitDepth));
    file.read(reinterpret_cast<char*>(&header.colorType), sizeof(header.colorType));
    file.read(reinterpret_cast<char*>(&header.compressionMethod), sizeof(header.compressionMethod));
    file.read(reinterpret_cast<char*>(&header.filterMethod), sizeof(header.filterMethod));
    file.read(reinterpret_cast<char*>(&header.interlaceMethod), sizeof(header.interlaceMethod));

    // Modify the header with new metadata
    for (const auto& pair : properties) {
        if (pair.first == "Width") {
            header.width = htonl(std::stoi(pair.second));
        } else if (pair.first == "Height") {
            header.height = htonl(std::stoi(pair.second));
        } else if (pair.first == "Bit Depth") {
            header.bitDepth = static_cast<uint8_t>(std::stoi(pair.second));
        } else if (pair.first == "Color Type") {
            header.colorType = static_cast<uint8_t>(std::stoi(pair.second));
        } else if (pair.first == "Compression Method") {
            header.compressionMethod = static_cast<uint8_t>(std::stoi(pair.second));
        } else if (pair.first == "Filter Method") {
            header.filterMethod = static_cast<uint8_t>(std::stoi(pair.second));
        } else if (pair.first == "Interlace Method") {
            header.interlaceMethod = static_cast<uint8_t>(std::stoi(pair.second));
        }
    }

    // Move the file pointer back to the beginning of the IHDR chunk data
    file.seekp(-13, std::ios_base::cur);

    // Write the header fields individually
    file.write(reinterpret_cast<char*>(&header.width), sizeof(header.width));
    file.write(reinterpret_cast<char*>(&header.height), sizeof(header.height));
    file.write(reinterpret_cast<char*>(&header.bitDepth), sizeof(header.bitDepth));
    file.write(reinterpret_cast<char*>(&header.colorType), sizeof(header.colorType));
    file.write(reinterpret_cast<char*>(&header.compressionMethod), sizeof(header.compressionMethod));
    file.write(reinterpret_cast<char*>(&header.filterMethod), sizeof(header.filterMethod));
    file.write(reinterpret_cast<char*>(&header.interlaceMethod), sizeof(header.interlaceMethod));

    file.close();
}