#include "RandomAI.h"
#include "engine.h"
#include <utility>
namespace ai{

    RandomAI::RandomAI(state::GameState *state, int randomSeed) : AI(state) {
        this->state=state;
        this->randgen= std::mt19937(randomSeed); 
    }

    RandomAI::~RandomAI() {
        this->listOfCommand.clear();
    }

    void RandomAI::run (engine::Engine *engine, state::PlayerId playerId){
        
        bool isPlaying= state->getPlaying()==playerId;
        state::Player player = state->getPlayer(playerId);

        //Phase de Choix du character
        if (state->getGamePhase()==state::Phase::CHOOSE_CHARACTER && isPlaying){
            for(auto &character: state->getAvailableCharacter()){
                auto command = std::make_unique<engine::ChooseCharacterCommand>(playerId, character);
                listOfCommand.push_back(command);
            }
        }

        //Phase de call character.
        //Cas ou on demande au joueur de chosir une carte
        if(state->getGamePhase()==state::Phase::CALL_CHARACTER && isPlaying && !(state->getDrawableCards()).empty()){
            for (auto &card: state->getDrawableCards()){
                auto* command = new engine::ChooseCardCommand(playerId, card);
                listOfCommand.push_back(command);
            }
        }

        //Cas général
        else if(state->getGamePhase()==state::Phase::CALL_CHARACTER && isPlaying){
            
            //Gold et draw
            std::uniform_int_distribution<> distribution(0, 1);
            int randomValue = distribution(randgen);
            if (randomValue == 0) {
                auto command = std::make_unique<engine::GainGoldCommand>(playerId, 2);
                listOfCommand.push_back(command);
            } else {
                auto command = std::make_unique<engine::DrawCommand>(playerId);
                listOfCommand.push_back(command);
            }
            

            //Claim Building Gold
            auto command = std::make_unique<engine::ClaimBuildingCommand>(playerId);
            listOfCommand.push_back(command);

            //Build
            std::vector<engine::BuildCommand> tempBuild;
            building = player.getHand();
            std::uniform_int_distribution<std::size_t> distribution(0, building.size() - 1);

            for (auto &buidling: player.getHand()){
                std::uniform_int_distribution<std::size_t> distribution(0, listOfCommand.size() - 1);
        std::size_t randomIndex = distribution(randgen);
//on choisi un building aleatoire a chaque fois on essaye pui break
        command = listOfCommand[randomIndex];
                command= std::make_unique<engine::BuildCommand>(playerId, building);
                if command.check(state){
                    listOfCommand.push_back(command);
                }
            }

            //Ability
            if (player.isCapacityAvailable()){
                bool needTargetPlayer = false, needTargetCharacter = false, needTargetCard = false;
                state::PlayerId targetPlayer = state::NO_PLAYER;
                state::CharacterType targetCharacter = state::NO_CHARACTER;
                const state::Card *targetCard = nullptr;

                switch(player.getCharacter()){
                    case state::CharacterType::ASSASSIN :
                        needTargetCharacter=true;
                        break;
                    case state::CharacterType::THIEF :
                        needTargetCharacter= true;
                        break;
                    case state::CharacterType::MAGICIAN :
                        needTargetPlayer = true;
                        break;
                    case state::CharacterType::WARLORD :
                        needTargetPlayer=true;
                        needTargetCard = true;
                        break;
                }

                if(needTargetCharacter){
                    std::vector<state::CharacterType> characters;
                    for (auto players: state->getListOfPlayer()){
                        characters.push_back(players.getCharacter());
                    }
                    std::uniform_int_distribution<int> distribution(0, characters.size() - 1);
                    int index = distribution(randgen);
                    targetCharacter= characters[index];      
                }

                if (needTargetPlayer){
                    std::vector<state::Player> players = state->getListOfPlayer();
                    std::uniform_int_distribution<int> distribution(0, players.size() - 1);
                    int index = distribution(randgen);
                    auto pick = players[index];
                    targetPlayer= pick.getIdOfPlayer();

                    if(needTargetCard){
                    const auto& board = pick.getBoardOfPlayer();
                    if(!board.empty()){
                        std::uniform_int_distribution<int> distribution(0, board.size() - 1);
                        int index = distribution(randgen);
                        targetCard= &board[index];
                    }
                }
                }

                
                listOfCommand.push_back(std::make_unique<engine::UseCharacterAbilityCommand>(playerId, targetPlayer, targetCharacter, targetCard));
            }

            //End of turn
            auto command = std::make_unique<engine::EndOfTurnCommand>(playerId);
            listOfCommand.push_back(command);
        }
            
    

        // Retourne l'élément choisi aléatoirement
        std::uniform_int_distribution<std::size_t> distribution(0, listOfCommand.size() - 1);
        std::size_t randomIndex = distribution(randgen);

        command = listOfCommand[randomIndex];
        listOfCommand.clear();
    }
}