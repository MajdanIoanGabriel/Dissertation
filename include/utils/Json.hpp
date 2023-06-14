#ifndef JSON_HPP
#define JSON_HPP

#include <iostream>
#include <fstream>
#include <map>
#include <nlohmann/json.hpp>
#include <vector>

namespace json {
    void writeToJSON(const std::string filename, const std::map<size_t, std::vector<double>>& data) {
        // Create a JSON object
        nlohmann::json jsonObject;

        // Convert the map into a JSON object
        for (const auto& pair : data) {
            jsonObject[std::to_string(pair.first)] = pair.second;
        }

        // Write the JSON object to a file
        std::ofstream file(filename);
        file << jsonObject.dump(4);  // Dump the JSON object with indentation of 4 spaces
        file.close();

        std::cout << "Data successfully written to " << filename << std::endl;
    }
}

#endif
