#include <iostream>
#include <sstream>
#include <string>

#include "controller/TTTController.h"
#include "model/Json.h"

int main(){
    // std::cout << "content-type: text/html\n\n"; 

    // std::stringstream post;
    // post << std::cin.rdbuf();
    // std::string incomingJsonObjectString = post.str();

 
    std::string mockresponese = "{\"controllerMethod\":{\"name\":\"createPlayer\",\"input\":{\"num\":1,\"name\":\"Cece\",\"marker\":\"C\"}},\"players\":[],\"board\":{},\"game\":{}}";
 
    JsonParser  parser = JsonParser(mockresponese);
    Json json = parser.parseJson();
    Json controllerJson = json["controllerMethod"];

    std::string controllerMethod = controllerJson["name"].stringValue();
    std::cout << controllerMethod << std::endl;
    Json inputJson = controllerJson["input"];
    std::string out;
    inputJson.dump(out);
    std::cout << out; 

}
