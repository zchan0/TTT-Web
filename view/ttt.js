var cgiPath = "cgi-bin/ttt.cgi";

// some flags
var currentPlayer = 1;
var nextPlayer = 2;
var gameover = false;

var xhttp = new XMLHttpRequest();

var tttJsonObj = 
{
	controllerMethod: {}				
};

function callback() {	
	/**Handle the returned JSON string; after xhttp.send() finishes**/
	xhttp.onreadystatechange = function() {
		if (this.readyState == 4 && this.status == 200) {
			console.log(this.responseText);

			var retJsonObj = JSON.parse(this.responseText);
			console.log(retJsonObj);
			// gameBoard 
			var gameBoard  = retJsonObj.gameBoard;
			if (gameBoard) {
				for (i = 0; i < gameBoard.length; i++) 
					setSelection(gameBoard[i].row, gameBoard[i].col, gameBoard[i].marker);		
			}
			
			// players
			var players = retJsonObj.players;
			if (players) {
				for (i = 0; i < players.length; i++) {
					setPlayerInfo(players[i].playerNum, players[i].name, players[i].marker);
				}
			}

			// winner
		  var winner = retJsonObj.winner;
		  if (winner) {
		  	setWinner(winner);
		  	if (winner != 0)
		  		gameover = true;
		  }
		}
	};

  xhttp.open("POST", cgiPath, true);  
  xhttp.send(JSON.stringify(tttJsonObj));
}

function resetGame() {
	// reset UI
	gameover = false;
	nextPlayer = 2;
	currentPlayer = 1;
	
	setSelection(1, 1, "");
	setSelection(1, 2, "");
	setSelection(1, 3, "");
	setSelection(2, 1, "");
	setSelection(2, 2, "");
	setSelection(2, 3, "");
	setSelection(3, 1, "");
	setSelection(3, 2, "");
	setSelection(3, 3, "");

	setWinner(0);

	// call backend restart
	tttJsonObj.controllerMethod.name  = "startNewGame";	 
	tttJsonObj.controllerMethod.input = "";
	callback();
}

function toggleDisplay(divElement) {
	if(divElement.style.display == 'block')
        divElement.style.display = 'none';
    else
        divElement.style.display = 'block';
}

/** Make Request Helpers */

function clickSquare(event) {
	var playerOne = document.getElementsByClassName("player one")[0].innerHTML;
	var playerTwo = document.getElementsByClassName("player two")[0].innerHTML;
	if (playerOne.length == 8 || playerTwo.length == 8) {
		alert("Need add new player");
		return;
	}

	if (gameover) {
		return;
	}

	var pos = event.target.id;
	var row = parseInt(pos[0], 10);
	var col = parseInt(pos[1], 10);
	var square = {};

	square.row = row;
	square.col = col;
	square.currentPlayer = currentPlayer;

	tttJsonObj.controllerMethod.name  = "setSelection";
	tttJsonObj.controllerMethod.input = square;

	callback();
	newTurn();
}

function newTurn() {
	var temp = currentPlayer;
	currentPlayer = nextPlayer;
	nextPlayer = temp;
}

function addNewPlayer() {
	var playerOne = document.getElementsByClassName("player one")[0].innerHTML;
	var playerTwo = document.getElementsByClassName("player two")[0].innerHTML;
	var name   = document.getElementById("name").value;
	var marker = document.getElementById("marker").value;

	// 8 means not set player yet
	if (playerOne.length == 8) {
		populatePlayer(1, name, marker);
	} else if (playerTwo.length == 8) {
		populatePlayer(2, name, marker);
	} else {
		alert("There are already two players, start play!");
	}
	// toggle & clear
	toggleDisplay(addPlayerDiv);
	document.getElementById("name").value = "";
	document.getElementById("marker").value = "";
}

function populatePlayer(num, name, marker) {
	var player = {};
	player.name   = name;
	player.marker = marker;
	player.playerNum = num;

	tttJsonObj.controllerMethod.name  = "createPlayer";
	tttJsonObj.controllerMethod.input = player;
	callback();
}

/** Hanldle Responses */

function setSelection(row, col, marker) {
	// to determin which square
	if (marker === undefined) {
		return;
	}
	// truncate to show one character
	if (marker.length > 1) {
		marker = marker.substr(0, 1);
	}
	var id = row * 10 + col;
	document.getElementById(id.toString()).innerHTML = marker;
}

function setWinner(winner) {
	var winnerStr  = '' + winner; 
	var info = "";
	if (winner != 0 && winner != 3) {
		info = "Player " + winnerStr + " won!  ";
	} else if (winner == 3) {
		info = "Tied!";
	}
	document.getElementById("winner").innerHTML = info;
}

function setPlayerInfo(num, name, marker) {
	var info = "Player " + num + ": " + name + " (" + marker + ")";

	if (num == 1) {
		document.getElementsByClassName("player one")[0].innerHTML = info;
	} else if (num == 2) {
		document.getElementsByClassName("player two")[0].innerHTML = info;
	} else {
		console.log("invalid player number: " + num);
	}
}