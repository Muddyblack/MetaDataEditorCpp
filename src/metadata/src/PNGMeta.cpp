/**
 * @file PNGMeta.cpp
 * @brief Implements the PNGMeta class.
 * @author Muddyblack
 * @date 26.02.2024
 */
#include <iostream>
#include <fstream>
#include <cstdint>
#include <map>
#include <string>

#include <PNGMeta.h>
#include <Logger.h>



std::map<std::string, std::string> PNGMeta::readPNGHeader(const std::string& filename) {
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

void PNGMeta::writePNGHeader(const std::string& filename, const std::map<std::string, std::string>& properties) {
    std::fstream file(filename, std::ios::binary | std::ios::in | std::ios::out);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << " for writing" << std::endl;
        return;
    }

    // Move the file pointer to the position where the PNG header is stored
    file.seekp(0);

    PNGHeader header;
    file.read(reinterpret_cast<char*>(&header), sizeof(header));

    if (!file) {
        std::cerr << "Error: Unable to read PNG header from file " << filename << std::endl;
        return;
    }

    // Modify the header with new metadata
    for (const auto& pair : properties) {
        if (pair.first == "Width") {
            header.width = std::stoi(pair.second);
        } else if (pair.first == "Height") {
            header.height = std::stoi(pair.second);
        } else if (pair.first == "Bit Depth") {
            header.bitDepth = std::stoi(pair.second);
        } 
        // Add similar lines for other metadata properties
    }

    // Move the file pointer back to the beginning to overwrite the header
    file.seekp(0);
    file.write(reinterpret_cast<char*>(&header), sizeof(header));

    file.close();
}