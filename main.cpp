#include <iostream>
#include <sstream>
#include <string>

#include "controller/TTTController.h"
#include "model/Json.h"

int main(){
    std::cout << "content-type: text/html\n\n"; 

    std::stringstream post;
    post << std::cin.rdbuf();
    std::string incomingJsonObjectString = post.str();
 

    JsonParser  parser = JsonParser(incomingJsonObjectString);
    Json json = parser.parseJson();
    Json controllerJsonArray  = json["controllerMethods"];
    
    TTTController controller;
    controller.startNewGame();

    for (int i = 0; i < controllerJsonArray.size(); ++i) {
        Json controllerJson = controllerJsonArray[i];
        std::string controllerMethod = controllerJson["name"].stringValue();
        Json inputJson = controllerJson["input"];

        if (controllerMethod == "createPlayer") {
            std::string playerJsonStr;
            inputJson.dump(playerJsonStr);
            controller.createPlayer(playerJsonStr);
        }

        if (controllerMethod == "setSelection") {
            std::string gameJsonStr;
            inputJson.dump(gameJsonStr);
            if (controller.setSelection(gameJsonStr) && controller.determineWinner() != 0) {
                std::cout << "{\"winner\": " << controller.determineWinner() << "}";
            }
        }   
    }

}
