//
// Created by guillaume on 1/11/24.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

#include <functional> //needed for shuffle manipulation from list to vect

#include "CommandCreator.h"
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

using namespace engine;

Command *CommandCreator::createCommand(const std::string &commandStr) {
    std::istringstream iss(commandStr);
    std::string token;
    std::vector<std::string> tokens;

    // Tokenize the input string based on commas
    while (std::getline(iss, token, ',')) {
        tokens.push_back(token);
    }

    if (tokens.size() < 2) {
        std::cerr << "Invalid command format: " << commandStr << std::endl;
        return nullptr;
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
            command = new StartGameCommand(author);
            break;
        }
        case CommandTypeId::DRAW_CARD: { //DrawCommand
            command = new DrawCommand(author);
            break;
        }
        case CommandTypeId::GAIN_GOLD: { //GainGoldCommand
            auto nbOfGold = static_cast <int> (std::stoi(arguments[0]));
            command = new GainGoldCommand(author, nbOfGold);
            break;
        }
        case CommandTypeId::CHOOSE_CHARACTER: { //ChooseCharacterCommand
            auto characterType = static_cast <state::CharacterType> (std::stoi(arguments[0]));
            command = new ChooseCharacterCommand(author, characterType);
            break;
        }
        case CommandTypeId::BUILD: { //BuildCommand
            // Getting the card's type and cost with its id
            std::tuple<state::CardType, int> cardSpecs = StackUtils::getCardSpecs(arguments[0]); //arguments[0]=cardId
            // Creating the card
            state::Card card{arguments[0], std::get<0>(cardSpecs), std::get<1>(cardSpecs)};
            command = new BuildCommand(author, card);
            break;
        }
        case CommandTypeId::SWITCH_PHASE: { //ChangePhaseCommand
            auto phase = static_cast <state::Phase> (std::stoi(arguments[0]));
            command = new ChangePhaseCommand(author, phase);
            break;
        }
        case CommandTypeId::USE_ABILITY: { //UseCharacterAbilityCommand
            auto targetCharacter = static_cast <state::CharacterType> (std::stoi(arguments[0]));
            // Getting the card's type and cost with its id
            std::tuple<state::CardType, int> cardSpecs = StackUtils::getCardSpecs(arguments[1]); //arguments[1]=cardId
            // Creating the card
            auto* targetCard = new state::Card{arguments[0], std::get<0>(cardSpecs), std::get<1>(cardSpecs)};
            command = new UseCharacterAbilityCommand(author, target, targetCharacter, targetCard);
            break;
        }
        case CommandTypeId::CLAIM_BUILDING_GOLD: { //ClaimBuildingGold
            command = new ClaimBuildingGold(author);
            break;
        }
        case CommandTypeId::END_OF_TURN: { //EndOfTurnCommand
            command = new EndOfTurnCommand(author);
            break;
        }
        case CommandTypeId::CHOOSE_CARD: { //ChooseCardCommand
            // Getting the card's type and cost with its id
            std::tuple<state::CardType, int> cardSpecs = StackUtils::getCardSpecs(arguments[0]); //arguments[0]=cardId
            // Creating the card
            state::Card card{arguments[0], std::get<0>(cardSpecs), std::get<1>(cardSpecs)};
            command = new ChooseCardCommand(author, card);
            break;
        }
        case CommandTypeId::GET_CARD: { //GetCardCommand
            // Getting the card's type and cost with its id
            std::tuple<state::CardType, int> cardSpecs = StackUtils::getCardSpecs(arguments[0]); //arguments[0]=cardId
            // Creating the card
            state::Card card{arguments[0], std::get<0>(cardSpecs), std::get<1>(cardSpecs)};
            command = new GetCardCommand(author, card);
            break;
        }
        case CommandTypeId::NO_COMMAND: { //NoCommand
            break;
        }
        default:
            std::cerr << "Unknown command: " << commandId << std::endl;
            break;
    }
    return command;
}
