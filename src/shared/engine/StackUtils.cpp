// stackUtils.cpp
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <random>
#include "config.h"
#include "StackUtils.h"
#include <functional> //needed for shuffle manipulation from list to vect
#include "StartGameCommand.h"
#include "DrawCommand.h"
#include "GainGoldCommand.h"
#include "ChooseCharacterCommand.h"
#include "BuildCommand.h"
#include "ChangePhaseCommand.h"
#include "UseCharacterAbilityCommand.h"
#include "ClaimBuildingGold.h"
#include "EndOfTurnCommand.h"
#include "ChooseCardCommand.h"
#include "GetCardCommand.h"


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


    void StackUtils::createCommand(state::GameState& state, std::string& commandStr) {
    //auto* command = new GetCardCommand(authorPlayer, card);
    //Engine::getInstance(state).addCommand(command);

    std::istringstream iss(commandStr);
    std::string token;
    std::vector<std::string> tokens;

    // Tokenize the input string based on commas
    while (std::getline(iss, token, ',')) {
        tokens.push_back(token);
    }

    if (tokens.size() < 2) {
        std::cerr << "Invalid command format: " << commandStr << std::endl;
        return;
    }

    // Extracting individual components
    auto author = static_cast <state::PlayerId> (std::stoi(tokens[0]));
    auto commandId = static_cast <CommandTypeId> (std::stoi(tokens[1]));
    auto target = static_cast <state::PlayerId> (std::stoi(tokens[2]));

    // Assuming remaining arguments are passed as a vector of strings
    std::vector<std::string> arguments(tokens.begin() + 3, tokens.end());

    // Create command based on commandId using switch-case
    Command* command = nullptr;
    switch(commandId) {
        case CommandTypeId::START_GAME: { //StartGameCommand
            auto* command = new StartGameCommand(author);
            Engine::getInstance(state).addCommand(command);
            break;
        }
        case CommandTypeId::DRAW_CARD: { //DrawCommand
            auto* command = new DrawCommand(author);
            Engine::getInstance(state).addCommand(command);
            break;
        }
        case CommandTypeId::GAIN_GOLD: { //GainGoldCommand
            auto nbOfGold = static_cast <int> (std::stoi(arguments[0]));
            auto* command = new GainGoldCommand(author, nbOfGold);
            Engine::getInstance(state).addCommand(command);
            break;
        }
        case CommandTypeId::CHOOSE_CHARACTER: { //ChooseCharacterCommand
            auto characterType = static_cast <state::CharacterType> (std::stoi(arguments[0]));
            auto* command = new ChooseCharacterCommand(author, characterType);
            Engine::getInstance(state).addCommand(command);
            break;
        }
        case CommandTypeId::BUILD: { //BuildCommand
            // Getting the card's type and cost with its id
            std::tuple<state::CardType, int> cardSpecs = getCardSpecs(arguments[0]); //arguments[0]=cardId
            // Creating the card
            state::Card card{arguments[0], std::get<0>(cardSpecs), std::get<1>(cardSpecs)};
            auto* command = new BuildCommand(author, card);
            Engine::getInstance(state).addCommand(command);
            break;
        }
        case CommandTypeId::SWITCH_PHASE: { //ChangePhaseCommand
            auto phase = static_cast <state::Phase> (std::stoi(arguments[0]));
            auto* command = new ChangePhaseCommand(author, phase);
            Engine::getInstance(state).addCommand(command);
            break;
        }
        case CommandTypeId::USE_ABILITY: { //UseCharacterAbilityCommand
            auto targetCharacter = static_cast <state::CharacterType> (std::stoi(arguments[0]));
            // Getting the card's type and cost with its id
            std::tuple<state::CardType, int> cardSpecs = getCardSpecs(arguments[1]); //arguments[1]=cardId
            // Creating the card
            state::Card* targetCard = new state::Card{arguments[0], std::get<0>(cardSpecs), std::get<1>(cardSpecs)};
            auto* command = new UseCharacterAbilityCommand(author, target, targetCharacter, targetCard);
            Engine::getInstance(state).addCommand(command);
            break;
        }
        case CommandTypeId::CLAIM_BUILDING_GOLD: { //ClaimBuildingGold
            auto* command = new ClaimBuildingGold(author);
            Engine::getInstance(state).addCommand(command);
            break;
        }
        case CommandTypeId::END_OF_TURN: { //EndOfTurnCommand
            auto* command = new EndOfTurnCommand(author);
            Engine::getInstance(state).addCommand(command);
            break;
        }
        case CommandTypeId::CHOOSE_CARD: { //ChooseCardCommand
            // Getting the card's type and cost with its id
            std::tuple<state::CardType, int> cardSpecs = getCardSpecs(arguments[0]); //arguments[0]=cardId
            // Creating the card
            state::Card card{arguments[0], std::get<0>(cardSpecs), std::get<1>(cardSpecs)};
            auto* command = new ChooseCardCommand(author, card);
            Engine::getInstance(state).addCommand(command);
            break;
        }
        case CommandTypeId::GET_CARD: { //GetCardCommand
            // Getting the card's type and cost with its id
            std::tuple<state::CardType, int> cardSpecs = getCardSpecs(arguments[0]); //arguments[0]=cardId
            // Creating the card
            state::Card card{arguments[0], std::get<0>(cardSpecs), std::get<1>(cardSpecs)};
            auto* command = new GetCardCommand(author, card);
            Engine::getInstance(state).addCommand(command);
            break;
        }
        case CommandTypeId::NO_COMMAND: { //NoCommand
            break;
        }
        default:
            std::cerr << "Unknown command: " << commandId << std::endl;
            break;
    }

    return;
    }
} // namespace engine
