#include <iostream>
#include <sstream>
#include <string>

#include "controller/TTTController.h"
#include "model/Json.h"
#include "controller/DataManager.h"

static const std::string playersFilename   = "players.txt";

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

    if (controllerMethod == "createPlayer") {
        
        // create exsited player from file
        DataManager& dataManager = DataManager::getInstance();
        std::string otherPlayerStr;
        dataManager.read(playersFilename, otherPlayerStr, true);
        
        if (!otherPlayerStr.empty()) {
            JsonParser otherPlayerParser = JsonParser(otherPlayerStr);
            Json otherPlayerJson = otherPlayerParser.parseJson();
            controller.createPlayer(otherPlayerJson["name"].stringValue(), otherPlayerJson["marker"].stringValue(), otherPlayerJson["playerNum"].intValue());
        }

        // create one from web
        std::string playerJsonStr;
        inputJson.dump(playerJsonStr);
        controller.createPlayer(playerJsonStr);
    }

    if (controllerMethod == "setSelection") {
        std::string gameJsonStr;
        inputJson.dump(gameJsonStr);
        controller.setSelection(gameJsonStr);
    }

    if (controllerMethod == "startNewGame") {
        controller.startNewGame();
    } 

    std::cout << controller.getGameDisplay(true);
}
