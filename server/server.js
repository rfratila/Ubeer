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
  // Relay data to everything that is not the Edison
  if (edisonIP && socket.remoteAddress !== edisonIP) {
    forwardingSockets.push(socket);
    console.log('Added relay: ' + socket.remoteAddress);
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
            forwardingSockets[i].write(data.toString());
          }
        }
      }
    }
  });

  socket.on('close', function (data) {
    console.log('CLOSED: ' + socket.remoteAddress + ':' + socket.remotePort);
  });

  socket.on('error', function (data) {
    console.log('ERROR: ' + socket.remoteAddress + ':' + socket.remotePort);
  });

}).listen(port, host);

console.log('Server listening on ' + host + ':' + port);