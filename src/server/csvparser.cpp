#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>

// Define a struct to represent each entry in the CSV
struct CSVEntry {
    int id;
    std::string name;
    int multiplicity;
    std::string type;
    int cost;
};

int main() {
    // Create a vector to store the CSV entries
    std::vector<CSVEntry> entries;

    // Open the CSV file
    std::ifstream csvFile("resources/cards.csv");

    if (!csvFile.is_open()) {
        std::cerr << "Error: Unable to open the CSV file." << std::endl;
        return 1;
    }

    // Read and parse the CSV data
    std::string line;
    while (std::getline(csvFile, line)) {
        // Split the line into tokens using ',' as the delimiter
        std::istringstream iss(line);
        std::string token;
        CSVEntry entry;

        // Read and assign values to the entry struct with error checking
        if (std::getline(iss, token, ',')) {
            try {
                entry.id = std::stoi(token);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error parsing ID: " << e.what() << std::endl;
                continue; // Skip this entry
            }
        }
        if (std::getline(iss, entry.name, ',')) {
            // Note: name is read as a string without conversion
        }
        if (std::getline(iss, token, ',')) {
            try {
                entry.multiplicity = std::stoi(token);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error parsing Multiplicity: " << e.what() << std::endl;
                continue; // Skip this entry
            }
        }
        if (std::getline(iss, entry.type, ',')) {
            // Note: type is read as a string without conversion
        }
        if (std::getline(iss, token, ',')) {
            try {
                entry.cost = std::stoi(token);
            } catch (const std::invalid_argument& e) {
                std::cerr << "Error parsing Cost: " << e.what() << std::endl;
                continue; // Skip this entry
            }
        }

        // Add the entry to the vector
        entries.push_back(entry);
    }

    // Close the CSV file
    csvFile.close();

    // Print the parsed data
    for (const CSVEntry& entry : entries) {
        std::cout << "ID: " << entry.id << ", Name: " << entry.name
                  << ", Multiplicity: " << entry.multiplicity << ", Type: " << entry.type
                  << ", Cost: " << entry.cost << std::endl;
    }

    return 0;
}
