var rows = ["top", "", "bottom"];
var markers = [];

var cgiPath = "cgi-bin/ttt.cgi";

callback();

function callback() {
	var xhttp = new XMLHttpRequest();
	
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

function reset() {
	console.log("reset");
}

function clickSquare(event) {
	console.log(event.target.className);
}

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