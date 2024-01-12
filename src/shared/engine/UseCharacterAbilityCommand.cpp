#include "UseCharacterAbilityCommand.h"

namespace engine {

    UseCharacterAbilityCommand::UseCharacterAbilityCommand(state::PlayerId authorPlayer,
                                                           state::PlayerId targetPlayer,
                                                           state::CharacterType targetCharacter,
                                                           state::Card *targetCard) {
        this->authorPlayer = authorPlayer;
        this->targetPlayer = targetPlayer;
        this->targetCharacter = targetCharacter;
        this->targetCard = targetCard;
    }

    UseCharacterAbilityCommand::~UseCharacterAbilityCommand() = default;

    void UseCharacterAbilityCommand::execute(state::GameState &state) {
        // Getting the players corresponding to the Ids
        state::Player player = state.getPlayer(authorPlayer);

        // Getting the character of the author player to know which power to apply
        state::CharacterType character = player.getCharacter();

        // Applying the character ability 
        if (character == state::CharacterType::ASSASSIN) {
            state.setKilledCharacter(targetCharacter);
        } else if (character == state::CharacterType::THIEF) {
            state.setRobbedCharacter(targetCharacter);
        } else if (character == state::CharacterType::MAGICIAN) {
            // Getting the author player's hand
            std::vector<state::Card> authorHand = player.getHand();

            // He either targets a player to switch his cards with
            if (targetPlayer != state::PlayerId::NO_PLAYER) {
                // Getting the target player's hand
                auto targeted =  state.getPlayer(targetPlayer);
                std::vector<state::Card> targetHand = targeted.getHand();

                // Inverting their hands
                player.setHand(targetHand);
                targeted.setHand(authorHand);

                // Updating the players in the state
                state.updatePlayer(player);
                state.updatePlayer(targeted);
            } else // or if he didn't target any character, he switches his cards with the stack
            {
                // Getting the current stack and initializing a new hand for the player
                std::list<state::Card> stack = state.getStack();
                std::vector<state::Card> newHand;

                // Switching the cards from stack to new hand
                for (int i = 0; i < (int) authorHand.size(); i++) {
                    state::Card card = stack.back();
                    authorHand.pop_back();
                    newHand.push_back(card);
                }
                // Switching the cards from old hand to stack
                for (int i = 0; i < (int) authorHand.size(); i++) {
                    state::Card card = authorHand.back();
                    authorHand.pop_back();
                    stack.push_back(card);
                }

                // Updating the state
                player.setHand(newHand);
                state.updatePlayer(player);
                state.setStack(stack);
            }

        } else if (character == state::CharacterType::KING) {
            state.setCrownOwner(authorPlayer);
        } else if (character == state::CharacterType::BISHOP) {
            // Nothing to do
        } else if (character == state::CharacterType::MERCHANT) {
            // Getting the player's coins and adding one
            int coins = player.getNumberOfCoins();
            coins++;
            // Updating the state
            player.setNumberOfCoins(coins);
            state.updatePlayer(player);
        } else if (character == state::CharacterType::ARCHITECT) {
            // Creating a DrawCommand to draw two cards
            auto *command = new DrawCommand(authorPlayer);
            if (command->check(state)){
                command->execute(state);
            }
            delete command;
        } else if (character == state::CharacterType::WARLORD) {
            // Getting the targeted player's board
            auto targeted =  state.getPlayer(targetPlayer);
            std::vector<state::Card> targetBoard = targeted.getBoardOfPlayer();

            // Destroying the building
            for (auto i = targetBoard.begin(); i < targetBoard.end(); i++) {
                if (targetBoard[i - targetBoard.begin()].getNameOfCard() == targetCard->getNameOfCard()) {
                    targetBoard.erase(i);
                }
            }

            // Updating the Warlord's coins
            int coins = player.getNumberOfCoins();
            coins = coins - targetCard->getCostOfCard();

            // Updating the state
            player.setNumberOfCoins(coins);
            targeted.setBoardOfPlayer(targetBoard);
            state.updatePlayer(player);
            state.updatePlayer(targeted);
        }

    }

    // Check method
    bool UseCharacterAbilityCommand::check(state::GameState &state) {
        state::Player player = state.getPlayer(this->authorPlayer);
        state::CharacterType character = player.getCharacter();

        bool notdead = true;
        bool enoughcoins = true;
        // Checking that the thief isn't robbing the Assassin or his victim        
        if (character == state::CharacterType::THIEF) {
            state::Player targeted = state.getPlayer(state.getPlayerIdByCharacter(targetCharacter));
            notdead = (targetCharacter!=state.getKilledCharacter()) && (targetCharacter!=state::ASSASSIN);
        }
        // Checking that the Warlord has enough coins to destroy the building he's targeting
        else if (character == state::CharacterType::WARLORD) { 
            enoughcoins = (player.getNumberOfCoins() >= targetCard->getCostOfCard());
        }
        return Command::check(state) && player.isCapacityAvailable() && notdead && enoughcoins;
    }
} // namespace engine
