
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>

#include "./state.h"  

std::vector<state::Card> initDeck() {
    const std::string& filename = "./res/cards.csv";
    std::vector<state::Card> cards;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        exit(EXIT_FAILURE);
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string id, name, multiplicity, type, cost;

        if (!(iss >> id >> name >> multiplicity >> type >> cost)) {
            std::cerr << "Error reading line: " << line << std::endl;
            exit(EXIT_FAILURE);
        }

        int multiplicityValue = std::stoi(multiplicity);
        int costValue = std::stoi(cost);
        state::CardType typeValue;
        if (type == "Religious") {
            typeValue = state::CardType::Religious;
        } else if (type == "Military") {
           typeValue = state::CardType::Military;
        } else if (type == "Commercial") {
            typeValue = state::CardType::Commercial;
        } else if (type == "Noble") {
            typeValue = state::CardType::Noble;
        } else if (type == "Wonder") {
            typeValue = state::CardType::Wonder;
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


