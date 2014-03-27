var http = require('http');
var fs = require('fs');
var url = require('url');

var html;


http.createServer(function(req,res) {
	var path = url.parse(req.url).pathname;
	console.log(path);
	if(path === '/') {
	  fs.readFile('../app/index.html', function(err, htmlContent) {
		res.writeHead(200, {'Content-Type' : 'text/html' });
		res.write(htmlContent);
		res.end();
      });
	  return;
	}
	// assets
	if(path.indexOf('/lib/js') === 0 || path.indexOf('/node_modules/') === 0) {
	  fs.readFile('..' + path, function(err, jsContent) {
	     res.writeHead(200, {'Content-Type': 'text/javascript'});
		 res.write(jsContent);
		 res.end();
	  });
	  return;
	}
	if(path.indexOf('/js') === 0) {
	  fs.readFile('../app' + path, function(err, jsContent) {
	     res.writeHead(200, {'Content-Type': 'text/javascript'});
		 res.write(jsContent);
		 res.end();
	  });
	  return;
	}
}).listen(8888);