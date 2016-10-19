var cgiPath = "cgi-bin/ttt.cgi";
var rows = ["top", "", "bottom"];
var markers = [];
var currentPlayer = 1;
var nextPlayer = 2;

var xhttp = new XMLHttpRequest();

var tttJsonObj = 
{
	players:[],
	selections:[],
	controllerMethods:[],
};

function callback() {	
	/**Handle the returned JSON string; after xhttp.send() finishes**/
	xhttp.onreadystatechange = function() {
		if (this.readyState == 4 && this.status == 200) {
			var retJsonObj = JSON.parse(this.responseText);
			if (retJsonObj["winner"] != 0)
				setWinner(retJsonObj["winner"]);
		}
	};

  xhttp.open("POST", cgiPath, true);  
  xhttp.send(JSON.stringify(tttJsonObj));
}

function toggleDisplay(divElement) {
	if(divElement.style.display == 'block')
        divElement.style.display = 'none';
    else
        divElement.style.display = 'block';
}

/** Make Request Helpers */

function reset() {
	// reset UI
	// reset controllerMethods
}

function clickSquare(event) {
	// if (playerOne.length == 8 || playerTwo.length == 8) {
	// 	alert("Need add new player");
	// }

	var pos = event.target.id;
	var row = parseInt(pos[0], 10);
	var col = parseInt(pos[1], 10);
	setSelection(row, col, markers[currentPlayer]);

	var square = {};
	square.row = row;
	square.col = col;
	square.currentPlayer = currentPlayer;
	newTurn();

	var controllerMethod = {};
	controllerMethod.name  = "setSelection";
	controllerMethod.input = square;
	tttJsonObj.controllerMethods.push(controllerMethod);

	callback();
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
		setPlayerInfo(1, name, marker);
		populatePlayer(1, name, marker);
	} else if (playerTwo.length == 8) {
		setPlayerInfo(2, name, marker);
		populatePlayer(2, name, marker);
	} else {
		alert("There are already two players, start play!");
	}
	toggleDisplay(addPlayerDiv);
}

function populatePlayer(num, name, marker) {
	var player = {};
	player.name   = name;
	player.marker = marker;
	player.playerNum = num;

	var controllerMethod = {};
	controllerMethod.name  = "createPlayer";
	controllerMethod.input = player;
 	tttJsonObj.controllerMethods.push(controllerMethod);
}

/** Hanldle Responses */

function setSelection(row, col, marker) {
	// to determin which square
	var id = row * 10 + col;
	document.getElementById(id.toString()).innerHTML = marker;
}

function setWinner(winner) {
	var winnerStr  = '' + winner; 
	var info = "";
	if (winner != 0 && winner != 3) {
		info = "Player " + winnerStr + " won!  ";
	} else {
		info = "Tied!";
	}
	document.getElementById("winner").innerHTML = info;
}

function setPlayerInfo(num, name, marker) {
	// store markers
	markers[num] = marker;

	var info = "Player " + num + ": " + name + " (" + marker + ")";

	if (num == 1) {
		document.getElementsByClassName("player one")[0].innerHTML = info;
	} else if (num == 2) {
		document.getElementsByClassName("player two")[0].innerHTML = info;
	} else {
		console.log("invalid player number: " + num);
	}
}