var http = require('http');
var url = require('url');
var fs = require('fs');

var server = http.createServer(requestHandler).listen(8888);

function requestHandler(request, response) {
	var pathname = url.parse(request.url).pathname;
	console.log(pathname);
	if (pathname === "/") {
		fs.readFile('index.html', function(err, content) {
			console.log(content);
			response.writeHead(200, {'Content-Type' : 'text/html'});
			response.write(content);
			response.end();
		});
	} else if (pathname === "/app.js" || pathname === '/jquery.js') {
		fs.readFile('.' +pathname, function(err, content) {
			response.writeHead(200, {'Content-Type' : 'text/javascript'});
			response.write(content);
			response.end();
		});
	}
}

var io = require('socket.io').listen(server);

io.sockets.on('connection', function(socket) {
	console.log("new connection");
	socket.emit('connectionSuccess');
	socket.on('nickname', function(nickname) {
	    socket.set('nickname', nickname);
		console.log('new nickname:' + nickname);
		io.sockets.emit('newChatter', nickname);
	});
	socket.on('message', function(text){
		var nickname = socket.get('nickname', function(error,nickname) {
			console.log(nickname + ': '+text);
			io.sockets.emit('newMessage', { sender : nickname, content: text } );
		});
	});
});

