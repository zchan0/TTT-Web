#include <iostream>
#include <string>
#include "controller/TTTController.h"

using namespace std;

int main(){
    TTTController controller;
    controller.createPlayer("Sue", "S", 1);
    controller.createPlayer("John", "J", 2);
    
	controller.startNewGame();
    cout << controller.getGameDisplay()<< endl;
	
	bool validSelection = false; //this particular test only expects valid (true) returns for setSelection()
	int winner = -1; //initialize to any int that is not an expected status

    //Step1
    validSelection = controller.setSelection(1, 1, 1);    
    if(!validSelection){
    	cout << "Failed testCase: step1 setSelection player1" <<endl;
    	return 0;
	}
    
    validSelection = controller.setSelection(2, 1, 2);
    if(!validSelection){
    	cout << "Failed testCase: step1 setSelection player2" <<endl;
    	return 0;
	}

    cout << controller.getGameDisplay()<< endl;
    
    winner = controller.determineWinner();
    if(winner !=0){
    	cout << "Failed testCase after step1" <<endl;
    	return 0;
	}
    
    //Step2
    validSelection = controller.setSelection(2, 0, 1);
    if(!validSelection){
    	cout << "Failed testCase: step2 setSelection player1" <<endl;
    	return 0;
	}

    validSelection = controller.setSelection(1, 2, 2);
     if(!validSelection){
    	cout << "Failed testCase: step2 setSelection player2" <<endl;
    	return 0;
	}

    cout << controller.getGameDisplay()<< endl;

    winner = controller.determineWinner();
    if(winner !=0){
    	cout << "Failed testCase after step2" <<endl;
    	return 0;
	}
    
    //Step3
    validSelection = controller.setSelection(0, 2, 1);
    if(!validSelection){
    	cout << "Failed testCase: step3 setSelection player1" <<endl;
    	return 0;
	}

    cout << controller.getGameDisplay()<< endl;
    
	winner = controller.determineWinner();
    if(winner !=1){
    	cout << "Failed testCase after step3" <<endl;
    	return 0;
	}else{
        cout << "TestCase1 with  Player1  as winner is successful" << endl;
	}

}
