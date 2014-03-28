var socket = io.connect("http://localhost:8888");
$(document).ready(function(){
	var chatDiv = $("#chatContent");
	var chatInput = $("#chatInput");
	var chatButton = $("#submitMessage");

	socket.on('connectionSuccess', function() {
		var nickname = prompt('nickname ?');
		socket.emit('nickname', nickname);
	});

	socket.on('newChatter', function(newNickname) {
		chatDiv.append($("<p><strong>" + newNickname + " vient de se connecter !</strong></p>"));
	});

	socket.on('newMessage', function(message) {
		chatDiv.append($("<p><strong>" + message.sender + " : </strong>"+ message.content +"</p>"));
	});

	chatButton.on('click', function() {
		var text = chatInput.val();
		chatInput.val("");
		socket.emit('message', text);
	});
});
