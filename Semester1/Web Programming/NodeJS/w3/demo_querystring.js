var http = require('http');
var url = require ('url');

var dt = require('./myfirstmodules');

http.createServer(function (req, res) {
  res.writeHead(200, {'Content-Type': 'text/html'});

  var q = url.parse(req.url, true).query;
  var txt = q.year + " " + q.month;




  res.end(txt);
}).listen(8081); 


