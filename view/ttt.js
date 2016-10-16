var cgiPath = "cgi-bin/ttt.cgi";



function reset() {
	console.log("reset");
}

function setSelection(event) {
	console.log(event.target.className)
}

function setPlayerInfo(num, name, marker) {
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