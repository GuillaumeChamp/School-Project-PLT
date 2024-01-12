#include "RandomAI.h"
#include "engine.h"
#include <utility>
#include <algorithm>

namespace ai {

    RandomAI::RandomAI(std::shared_ptr<state::GameState> state, state::PlayerId player, int randomSeed) : AI(
            std::move(state), player) {
        this->randgen = std::mt19937(randomSeed);
    }

    RandomAI::~RandomAI() = default;

    void RandomAI::run() {
        bool isPlaying = state->getPlaying() == playerId;
        if (!isPlaying) {
            return;
        }
        state::Player player = state->getPlayer(playerId);
        std::vector<engine::Command*> listOfCommand{};
        //Phase de Choix du character
        if (state->getGamePhase() == state::Phase::CHOOSE_CHARACTER) {
            auto characters = state->getAvailableCharacter();
            std::uniform_int_distribution<int> distribution(0, characters.size() - 1);
            int index = distribution(randgen);
            auto *command = new engine::ChooseCharacterCommand(playerId, characters[index]);
            listOfCommand.push_back(command);
        }

        //Phase de call character.
        //Cas ou on demande au joueur de chosir une carte
        if (state->getGamePhase() == state::Phase::CALL_CHARACTER && !(state->getDrawableCards()).empty()) {
            auto cards = state->getDrawableCards();
            std::uniform_int_distribution<int> distribution(0, cards.size() - 1);
            int index = distribution(randgen);
            auto *command = new engine::ChooseCardCommand(playerId, cards[index]);
            listOfCommand.push_back(command);
        }

            //Cas général
        else if (state->getGamePhase() == state::Phase::CALL_CHARACTER) {
            //Gold et draw
            std::uniform_int_distribution<> distribution(0, 1);
            int randomValue = distribution(randgen);
            if (randomValue == 0) {
                auto * command = new engine::GainGoldCommand(playerId, 2);
                listOfCommand.push_back(command);
            } else {
                auto * command = new engine::DrawCommand(playerId);
                listOfCommand.push_back(command);
            }


            //Claim Building Gold
            auto * command = new engine::ClaimBuildingGold(playerId);
            listOfCommand.push_back(command);

            //Build
            auto hand = player.getHand();
            std::shuffle(hand.begin(), hand.end(), randgen);
            for (auto &buidling: hand) {
                auto * command = new engine::BuildCommand(playerId, buidling);
                if (command->check(*state)) {
                    listOfCommand.push_back(command);
                    break;
                }
            }

            //Ability
            if (player.isCapacityAvailable()) {
                bool needTargetPlayer = false, needTargetCharacter = false, needTargetCard = false;
                state::PlayerId targetPlayer = state::NO_PLAYER;
                state::CharacterType targetCharacter = state::NO_CHARACTER;
                const state::Card *targetCard = nullptr;

                switch (player.getCharacter()) {
                    case state::CharacterType::ASSASSIN :
                    case state::CharacterType::THIEF :
                        needTargetCharacter = true;
                        break;
                    case state::CharacterType::MAGICIAN :
                        needTargetPlayer = true;
                        break;
                    case state::CharacterType::WARLORD :
                        needTargetPlayer = true;
                        needTargetCard = true;
                        break;
                    default :
                        break;
                }

                if (needTargetCharacter) {
                    std::vector<state::CharacterType> characters;
                    for (const auto &players: state->getListOfPlayer()) {
                        characters.push_back(players.getCharacter());
                    }
                    std::uniform_int_distribution<int> distribution(0, characters.size() - 1);
                    int index = distribution(randgen);
                    targetCharacter = characters[index];
                }

                if (needTargetPlayer) {
                    std::vector<state::Player> players = state->getListOfPlayer();
                    std::uniform_int_distribution<int> distribution(0, players.size() - 1);
                    int index = distribution(randgen);
                    auto pick = players[index];
                    targetPlayer = pick.getIdOfPlayer();

                    if (needTargetCard) {
                        const auto &board = pick.getBoardOfPlayer();
                        if (!board.empty()) {
                            std::uniform_int_distribution<int> distribution(0, board.size() - 1);
                            int index = distribution(randgen);
                            targetCard = &board[index];
                        }
                    }
                }
                auto* command = new engine::UseCharacterAbilityCommand(playerId, targetPlayer, targetCharacter,
                                                               const_cast<state::Card *>(targetCard));
                listOfCommand.push_back(std::move(command));
            }

            //End of turn
            auto* endOfTurnCommand(new engine::EndOfTurnCommand(playerId));
            listOfCommand.push_back(std::move(endOfTurnCommand));
        }

        // Envoie les commandes choisies aléatoirement a l'engine
        for (auto command: listOfCommand) {
            engine::Engine::getInstance().addCommand(std::move(command));
        }
        //listOfCommand.clear();
    }
}