var net = require('net');
var os = require('os');
var ifaces = os.networkInterfaces();
var host;
var port = 1234;

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
      console.log('DATA ' + socket.remoteAddress + ': ' + data);
    }
  });

  socket.on('close', function (data) {
    console.log('CLOSED: ' + socket.remoteAddress + ' ' + socket.remotePort);
  });

}).listen(port, host);

console.log('Server listening on ' + host + ':' + port);