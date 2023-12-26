// EndOfTurnCommand.cpp
#include "EndOfTurnCommand.h"
#include <iostream>

namespace engine {

    // Constructor
    EndOfTurnCommand::EndOfTurnCommand(state::PlayerId authorPlayer) {
        this->authorPlayer = authorPlayer;
    }

    // Destructor
    EndOfTurnCommand::~EndOfTurnCommand() = default;

    // Execute method
    void EndOfTurnCommand::execute(state::GameState &state) {
        // Switch to the next player
        
        state::Player player = state.getPlayer(authorPlayer);
        state::PlayerId currentPlayer = state.getPlaying();
        state::PlayerId lastPlayer = static_cast<state::PlayerId>((static_cast<int>(state.getCrownOwner()) + 2) % 4 + 1);
        state::CharacterType calledCharacterId =  static_cast<state::CharacterType>((static_cast<int>(state.getCurrentCharacter())%7) +1);

        //Change phase if curent player is lastplayer
        if (currentPlayer==lastPlayer){
            auto* command = new ChangePhaseCommand(this->authorPlayer, state.getGamePhase());
            command->execute(state);
            //engine::Engine* gameEngine = engine::Engine::getInstance(state);
            //Engine::getInstance(state)->addCommand(command);
            
            //Le curent player change 
            currentPlayer = static_cast<state::PlayerId>((static_cast<int>(currentPlayer)%4)+1 );
            //on ré-initialise alors ce current player avec ces capacitésS 
            state::Player playerToInit = state.getPlayer(currentPlayer);
            //reinitialise les capacité activables une fois par tour
            playerToInit.setDrawAvailability(true);
            playerToInit.setCapacityAvailability(true);
            state.updatePlayer(playerToInit); 
            
        }
        //If the current character is not the last player
        else{
        
            //The curent player change 
            currentPlayer = static_cast<state::PlayerId>((static_cast<int>(currentPlayer)%4)+1 );
            //on ré-initialise alors ce current player avec ces capacitésS 
            state::Player playerToInit = state.getPlayer(currentPlayer);
            //reinitialise les capacités activables une fois par tour
            playerToInit.setDrawAvailability(true);
            playerToInit.setCapacityAvailability(true);
            state.updatePlayer(playerToInit);

            if((state.getGamePhase()==state::Phase::CHOOSE_CHARACTER)){
                //nothing to do now 
            }

            //If we are in the phase CALL_CHARACTER 
            //il aura un appel des characters choisi par les joueurs
        
            if((state.getGamePhase()==state::Phase::CALL_CHARACTER)){
                //on regarde parmis les personnages choisis pour effectuer un appel
                //on incrémente calledCharaterId jusqu'à ce que sa valeur soit égale au character ID
                while (calledCharacterId < 8) {
                    bool characterFound = false;
                    for (auto& player : state.getListOfPlayer()) {
                        if (player.getCharacter() == calledCharacterId) {
                            currentPlayer=player.getIdOfPlayer();//on récupere l'id du player associé au call du personnage.
                            characterFound = true;
                            break; // Sortir de la boucle si le personnage est trouvé
                        }
                    }
                    if (characterFound) {
                    break; // Sortir du while si le personnage est trouvé
                    }
                    calledCharacterId = static_cast<state::CharacterType>((static_cast<int>(calledCharacterId) % 7) + 1);
                }
                //OK on a notre prochain character à call, mais avant de le call on doit vérifier si ce character à ete tué
        
            //Si le character a été tué on saute le tour du current player qui possède ce character
            if(calledCharacterId==state.getKilledCharacter()){
                
                //on incrémente calledCharaterId jusqu'à ce que sa valeur soit égale au character ID
                    while (calledCharacterId < 8) {
                        bool characterFound = false;
                        for (auto& player : state.getListOfPlayer()) {
                            if (player.getCharacter() == calledCharacterId) {
                                currentPlayer=player.getIdOfPlayer();//on récupere l'id du player associé au call du personnage.
                                characterFound = true;
                                break; // Sortir de la boucle si le personnage est trouvé
                            }
                        }
                    if (characterFound) {
                    break; // Sortir du while si le personnage est trouvé
                    }
                    calledCharacterId = static_cast<state::CharacterType>((static_cast<int>(calledCharacterId) % 7) + 1);
                }
            }
            if (calledCharacterId == state.getRobbedCharacter()) {
            auto coins = playerToInit.getNumberOfCoins();
            playerToInit.setNumberOfCoins(0);
            auto thief = state.getPlayer(state.getPlayerIdByCharacter(state::CharacterType::THIEF));
            thief.setNumberOfCoins(coins + thief.getNumberOfCoins());
            state.updatePlayer(thief);
            state.updatePlayer(playerToInit);
        }
            }
        }
        //Mise à jour du state 
            state.setPlaying(currentPlayer);
            state.setCurrentCharacter(calledCharacterId);
        
    }

    // Check method
    bool EndOfTurnCommand::check(state::GameState &state) {
        return Command::check(state);
    }


} // namespace engine
