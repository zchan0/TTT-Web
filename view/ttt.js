var cgiPath = "cgi-bin/ttt.cgi";
var rows = ["top", "", "bottom"];
var markers = [];

var xhttp = new XMLHttpRequest();

var tttJsonObj = 
{
	controllerMethod:{},
	players:[],
	board:{},
	game:{}
};

callback();

function callback() {	
	/**Handle the returned JSON string; after xhttp.send() finishes**/
	xhttp.onreadystatechange = function() {
		if (this.readyState == 4 && this.status == 200) {
			console.log(this.responseText);
			var retJsonObj = JSON.parse(this.responseText);
			console.log(retJsonObj);

			// Set players info
			var players = retJsonObj.players;
			for (var i = 0; i < players.length; i++) {
				var player = players[i];
				setPlayerInfo(i + 1, player.name, player.marker);
			}

			// Set selection
			var game = retJsonObj.game;
			setSelection(game.row, game.col, markers[game.currentPlayer]);
			setWinner(0);
		}
	};

  xhttp.open("POST", cgiPath, true);  
  xhttp.send();
}

function send() {
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
	console.log("reset");
}

function clickSquare(event) {
	console.log(event.target.className);
}

function addNewPlayer() {
	var playerOne = document.getElementsByClassName("player one")[0].innerHTML;
	var playerTwo = document.getElementsByClassName("player two")[0].innerHTML;
	var name   = document.getElementById("name").value;
	var marker = document.getElementById("marker").value;
	if (playerOne.length == 8) {
		populatePlayer(1, name, marker);
	} else if (playerTwo.length == 8) {
		populatePlayer(2, name, marker);
	} else {
		alert("There are already two players, start play!");
	}
}

function populatePlayer(num, name, marker) {
	var player = {};
	player.num    = num;
	player.name   = name;
	player.marker = marker;
	tttJsonObj.controllerMethod.name  = "createPlayer";
	tttJsonObj.controllerMethod.input = player;
	xhttp.open("POST", cgiPath, true);  
	xhttp.send(JSON.stringify(tttJsonObj));
}

/** Hanldle Responses */

function setSelection(row, col, marker) {
	// to determin which square
	var rowName = "square" + " " + (rows[row - 1] === undefined ? "" : rows[row - 1]);
	document.getElementsByClassName(rowName)[col - 1].innerHTML = marker;
}

function setWinner(winner) {
	var winnerStr  = '' + winner; 
	var info = "";
	if (winner != 0) {
		info = "Player " + winnerStr + " won!  ";
	}
	document.getElementById("winner").innerHTML = info;
}

function setPlayerInfo(num, name, marker) {
	// store markers
	markers[num] = marker;

	var info = "Player " + num + ": " + name + " (" + marker + ")";
	console.log(info);

	if (num == 1) {
		document.getElementsByClassName("player one")[0].innerHTML = info;
	} else if (num == 2) {
		document.getElementsByClassName("player two")[0].innerHTML = info;
	} else {
		console.log("invalid player number: " + num);
	}
}