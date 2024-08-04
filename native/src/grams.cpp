// Standard library includes
#include <fstream>
#include <iostream>
#include <locale>
#include <string>
#include <unordered_map>
#include <vector>
#include <cstdio> // For temporary file generation (optional)

// Third-party library includes
#include <fmt/core.h>

// Local project includes
#include "export_header.h"
#include "frequency_map_generated.h"


std::string huchars = "§0'1~\"2ˇ+3^!4˘%5°/6˛=7`(8˙)9´Öö˝Üü¨Óó¸␉Qq\\Ww|EeÄRrTtZzUu€IiÍOoPpŐő÷Úú×␍Caps LockAaäSsđDdĐFf[Gg]HhJjíKkłLlŁÉé$ÁáßŰű¤ShiftÍí<Yy>Xx#Cc&Vv@Bb{Nn}Mm<?,;:.>_-*Shift␠";
std::string uschars = "`!1@2#3$4%5^6&7*8(9)0_-+=␉QqWwEeRrTtYyUuIiOoPp{[}]␍Caps LockAaSsDdFfGgHhJjKkLl:;\"'|\\ShiftZzXxCcVvBbNnMm<,>.?/Shift␠";

void update_frequency(std::unordered_map<std::string, int>& freq, const std::string& buffer) {
    // Example: Count frequencies of individual UTF-8 characters
    size_t i = 0, len = buffer.size();
    while (i < len) {
        int char_len = 1;
        if ((buffer[i] & 0xF8) == 0xF0) char_len = 4;
        else if ((buffer[i] & 0xF0) == 0xE0) char_len = 3;
        else if ((buffer[i] & 0xE0) == 0xC0) char_len = 2;

        std::string utf8_char = buffer.substr(i, char_len);
        freq[utf8_char]++;

        i += char_len;
    }
}

void PrintFrequencies(const std::unordered_map<std::string, int>& frequency_map) {
    // Create a temporary file
    std::ofstream tempFile("output.txt"); // You can replace "output.txt" with a dynamically created temp file if needed

    if (!tempFile.is_open()) {
        std::cerr << "Error: Could not open temporary file for writing." << std::endl;
        return;
    }

    // Iterate over the frequency map and print the keys and values
    for (const auto& pair : frequency_map) {
        const std::string& key = pair.first;
        int frequency = pair.second;
        tempFile << key << " - Frequency: " << frequency << std::endl;
    }

    tempFile.close(); // Close the file when done
}

// Struct to hold buffer, builder context, and buffer size
struct FlatBufferResult {
    uint8_t* buffer;
    flatbuffers::FlatBufferBuilder* builderContext;
    int bufferSize;
};

extern "C" { // Ensure C linkage for name mangling

    OPTIKLAVI_API void __cdecl FreeResult(FlatBufferResult* result) {
        delete result->builderContext;
    }

    OPTIKLAVI_API int __cdecl CalculateNGramFrequency(const char* filename, FlatBufferResult* result) {
        std::ifstream file(filename, std::ios::binary);
        if (!file.is_open()) {
            return -1;
        }

        std::string content((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());
        file.close();

        std::unordered_map<std::string, int> frequency_map;
        update_frequency(frequency_map, content);

        PrintFrequencies(frequency_map);

        std::vector<flatbuffers::Offset<OptiKlavi::FrequencyMap::KeyValue>> key_value_vector;
        auto builder = new flatbuffers::FlatBufferBuilder();
        for (const auto& pair : frequency_map) {
            auto key = builder->CreateString(pair.first);  // Serialize the key (string)
            auto kv_offset = OptiKlavi::FrequencyMap::CreateKeyValue(*builder, key, pair.second);  // Create KeyValue pair
            key_value_vector.push_back(kv_offset);  // Add it to the vector
        }

        auto entries = builder->CreateVector(key_value_vector);
        auto freq_map = CreateFrequencyMap(*builder, entries);

        builder->Finish(freq_map);

        // Populate the struct with the buffer, builder context, and buffer size
        result->buffer = builder->GetBufferPointer();
        result->builderContext = builder;
        result->bufferSize = builder->GetSize();

        return 0;
    }
} // extern "C"