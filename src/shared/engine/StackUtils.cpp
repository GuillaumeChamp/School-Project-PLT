// stackUtils.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#include "config.h"
#include "StackUtils.h"
#include <functional> //needed for shuffle manipulation from list to vect


namespace engine {

    // Method to initialize the stack based on the csv file of all cards
    std::list<state::Card> StackUtils::initStack() {
        std::string res = RES_DIR;
        const std::string &filename = res + "cards.csv";
        std::list<state::Card> cards;
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
            line.substr(0, pos);
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
        // create a vector of (wrapped) references to elements in the list
        // http://en.cppreference.com/w/cpp/utility/functional/reference_wrapper
        std::vector<std::reference_wrapper<const state::Card> > vec(cards.cbegin(), cards.cend());
        // shuffle (the references in) the vector
        std::shuffle(vec.begin(), vec.end(), std::mt19937{std::random_device{}()});
        // copy the shuffled sequence into a new list
        std::list<state::Card> shuffled_list{vec.begin(), vec.end()};
        // swap the old list with the shuffled list
        cards.swap(shuffled_list);

        file.close();

        return cards;

    }


    std::tuple<state::CardType, int> StackUtils::getCardSpecs(std::string cardId){
        std::string res = RES_DIR;
        const std::string &filename = res + "cards.csv";
        std::ifstream file(filename);
 
        if (!file.is_open()) {
            std::cerr << "Error opening file: " << filename << std::endl;
            exit(EXIT_FAILURE);
        }

        std::string line;
        std::getline(file, line); // remove header

        std::string id, name, multiplicity, type, cost;
        while (id!=cardId) {
            std::getline(file, line);
            std::istringstream iss(line);

            auto pos = line.find(',');
            id = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find(',');
            line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find(',');
            multiplicity = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find(',');
            type = line.substr(0, pos);
            line.erase(0, pos + 1);

            pos = line.find('\r');
            cost = line.substr(0, pos);         
        }

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

        std::tuple<state::CardType, int> cardSpecs = std::make_tuple(typeValue, costValue);
        return cardSpecs;
    }


} // namespace engine
