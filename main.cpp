#include <iostream>
#include <sstream>
#include <string>

#include "controller/TTTController.h"
#include "model/Json.h"
#include "controller/DataManager.h"

static const std::string gameBoardFilename = "board.txt";

int main(){
    std::cout << "content-type: text/html\n\n"; 

    std::stringstream post;
    post << std::cin.rdbuf();
    std::string incomingJsonObjectString = post.str();
 
    JsonParser  parser = JsonParser(incomingJsonObjectString);
    Json json = parser.parseJson();
    Json controllerJson  = json["controllerMethod"];

    std::string controllerMethod = controllerJson["name"].stringValue();
    Json inputJson = controllerJson["input"];
    
    TTTController controller;

    if (controllerMethod == "startNewGame") {
        controller.startNewGame();
        DataManager &dataManager = DataManager::getInstance();
        dataManager.empty(gameBoardFilename);
    }

    if (controllerMethod == "createPlayer") {
        std::string playerJsonStr;
        inputJson.dump(playerJsonStr);
        controller.createPlayer(playerJsonStr);
    }

    int winner = 0;
    controller.startNewGame();
    
    // setup players
    std::string playerJsonStr = controller.getAllSavedPlayers();
    JsonParser playersParser = JsonParser(playerJsonStr);
    Json playersJson = playersParser.parseJson();
    Json::array players = playersJson["players"].arrayItems();
    for (size_t i = 0; i < players.size(); ++i) {
        controller.createPlayer(players[i]["name"].stringValue(), players[i]["marker"].stringValue(), players[i]["playerNum"].intValue());
    } 

    if (controllerMethod == "setSelection") {
        // select old selections
        std::string boardJsonStr = controller.getGameDisplay(true);
        JsonParser boardJsonParser = JsonParser(boardJsonStr);
        Json boardJson = boardJsonParser.parseJson();
        Json::array selections = boardJson["gameBoard"].arrayItems();
        for (size_t i = 0; i < selections.size(); ++i) {
            Json selectionJson = selections[i];
            // need to minus 1, for set selection uses array index, starts with 0
            controller.setSelection(selectionJson["row"].intValue() - 1, selectionJson["col"].intValue() - 1, selectionJson["currentPlayer"].intValue());
        }

        // select new selection
        std::string gameJsonStr;
        inputJson.dump(gameJsonStr);
        if (controller.setSelection(gameJsonStr)) {
            // determin winner
            winner = controller.determineWinner();
        }
    }

    std::string gameBoardStr = controller.getGameDisplay(true);
    std::string playersStr = controller.getAllSavedPlayers();
    // remove {} to concat a new valid json string
    gameBoardStr.erase(0, 1);
    gameBoardStr.erase(gameBoardStr.size() - 1);
    playersStr.erase(0, 1);
    playersStr.erase(playersStr.size() - 1);

    std::cout << "{" + gameBoardStr + ", " + playersStr + ", \"winner\": " + patch::to_string(winner) + "}";
}
