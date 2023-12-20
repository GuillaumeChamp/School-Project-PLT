// stackUtils.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <ctime>
#include "config.h"
#include "StackUtils.h"

namespace engine {

  // Method to initialize the stack based on the csv file of all cards
  std::vector<state::Card> StackUtils::initStack() {
    std::string res = RES_DIR;
    const std::string& filename = res + "cards.csv";
    std::vector<state::Card> cards;
    std::ifstream file(filename);

        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            exit(EXIT_FAILURE);
        }

        std::string line;
        std::getline(file, line); // remove header

        std::string id, name, multiplicity, type, cost;
        while (std::getline(file, line)) {
            std::istringstream iss(line);

            auto pos = line.find(',');
            id = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find(',');
            name = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find(',');
            multiplicity = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find(',');
            type = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find('\r');
            cost = line.substr(0, pos);

            int multiplicityValue = std::stoi(multiplicity);
            int costValue = std::stoi(cost);
            state::CardType typeValue;
            if (type == "Religious") {
                typeValue = state::CardType::RELIGIOUS;
            } else if (type == "Military") {
                typeValue = state::CardType::MILITARY;
            } else if (type == "Commercial") {
                typeValue = state::CardType::COMMERCIAL;
            } else if (type == "Noble") {
                typeValue = state::CardType::NOBLE;
            } else if (type == "Wonder") {
                typeValue = state::CardType::WONDER;
            }

            for (int i = 0; i < multiplicityValue; ++i) {
                state::Card card(id, typeValue, costValue);
                cards.push_back(card);
            }
        }

        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        std::random_shuffle(cards.begin(), cards.end());


        file.close();

        return cards;

    }

} // namespace engine
