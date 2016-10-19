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
    
    /**Example of incomingJsonObjectString
       {"dealership":{"name":"Brown Auto","city":"Atlanta"},"vehicles":{},"controllerMethod":{"name":"addVehicle","input":{"make":"ford","color":"red","year":2012}}}
    **/ 

    /**
    insert code here:
        1. Call your implementation of a JSON reader that can parse the incoming string/jsonObject using only C++, STL   
        
        2. Use the controllerMethod (or whatever you want to name it) to decide which controller method to call. Ex
           if  controllerMethod.name == "addVehicle" 
                controller.addVehicle(controllerMethod.input)
                        //this method then calls whatever model and persistence objects you've created
                
        3. Call your implementation of a JSON writer that can compose and return the full, updated jsonObject string                    
    **/

    // Mock data for UI example
    std::string mockResponse = "{\"game\":{\"row\":18,\"col\":1,\"currentPlayer\":17,\"winner\":0},\"players\":[{\"name\":\"Cece\",\"marker\":\"C\"}, {\"name\":\"Sam\",\"marker\":\"S\"}]}";

    JsonParser  parser = JsonParser(mockResponse);
    Json json = parser.parseJson();
    Json json1 = json["game"];
    std::cout << json1["row"].intValue();

    // std::cout << post.str();
}
