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

 
    // std::string mockresponese = "{\"controllerMethod\":{\"name\":\"createPlayer\",\"input\":{\"playerNum\":1,\"name\":\"Cece\",\"marker\":\"C\"}},\"players\":[],\"board\":{},\"game\":{}}";
 
    JsonParser  parser = JsonParser(incomingJsonObjectString);
    Json json = parser.parseJson();
    Json controllerJson = json["controllerMethod"];

    TTTController controller;

    std::string controllerMethod = controllerJson["name"].stringValue();
    std::cout << controllerMethod << std::endl;
    Json inputJson = controllerJson["input"];

    if (controllerMethod == "createPlayer") {
        std::string playerJsonStr;
        inputJson.dump(playerJsonStr);
        controller.createPlayer(playerJsonStr);
    }

}
