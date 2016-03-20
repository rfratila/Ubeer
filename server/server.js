var net = require('net');
var os = require('os');
var ifaces = os.networkInterfaces();
var host;
var port = 1234;
var forwardingSockets = [];

Object.keys(ifaces).forEach(function (ifname) {
  ifaces[ifname].forEach(function (iface) {
    if ('IPv4' !== iface.family || iface.internal !== false) {
      return;
    }
    host = iface.address;
  });
});

net.createServer(function (socket) {
  console.log('CONNECTED: ' + socket.remoteAddress + ':' + socket.remotePort);

  socket.on('data', function (data) {
    if (data) {
      if (data === 'ADD_RELAY') {
        forwardingSockets.push(socket);
        console.log("ADDED RELAY: " + socket.remoteAddress);
        return;
      }

      dataArr = data.toString().split(':');
      if (dataArr[0] === 'EDISON') {
        for (var i = 0; i < forwardingSockets.length; i++) {
          socket.write(dataArr[1]);
        }
        return;
      }

      console.log('DATA ' + socket.remoteAddress + ': ' + data);
    }
  });

  socket.on('close', function (data) {
    console.log('CLOSED: ' + socket.remoteAddress + ' ' + socket.remotePort);
  });

  socket.on('error', function (data) {
    console.log('ERROR: ' + socket.remoteAddress + ' ' + socket.remotePort);
  });

}).listen(port, host);

console.log('Server listening on ' + host + ':' + port);