var net = require('net');
var os = require('os');
var ifaces = os.networkInterfaces();
var host;
var port = 1234;
var forwardingSockets = [];
var edisonIP;

Object.keys(ifaces).forEach(function (ifname) {
  ifaces[ifname].forEach(function (iface) {
    if ('IPv4' !== iface.family || iface.internal !== false) {
      return;
    }
    host = iface.address;
  });
});

net.createServer(function (socket) {
  console.log('Connected: ' + socket.remoteAddress + ':' + socket.remotePort);

  // Relay data to everything that is not the Edison
  if (edisonIP && socket.remoteAddress !== edisonIP) {
    forwardingSockets.push(socket);
    console.log('Relay connected: ' + socket.remoteAddress);
    socket.write('Connected to relay');
    return;
  }

  // Only the Edison should be sending data to the server
  socket.on('data', function (data) {
    if (data) {
      data = data.toString().trim();
      console.log(data);
      if (data === 'Edison connected') {
        edisonIP = socket.remoteAddress;
        console.log('Edison connected: ' + edisonIP);
      } else {
        for (var i = 0; i < forwardingSockets.length; i++) {
          if (forwardingSockets[i]) {
            if (data) {
              forwardingSockets[i].write(data);
            }
          }
        }
      }
    }
  });

  socket.on('close', function (err) {
    console.log('Closed connection');
  });

  socket.on('error', function (err) {
    console.log('Error: ' + err.stack);
  });

}).listen(port, host);

console.log('Server listening on ' + host + ':' + port);