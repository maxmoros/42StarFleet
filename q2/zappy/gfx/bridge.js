const http = require('http');
const net = require("net");
const express = require('express');
const split2 = require('split2');
const socketio = require('socket.io');
const TickEventParser = require('./TickEventParser.js');
const stream = require('stream');

const app = express();
app.use(express.static('javascript'));
app.use(express.static('assets'));
app.get('/', (req, res) => {
	res.sendFile(__dirname + "/index.html");
});

const server = http.createServer(app);
server.listen(3000, () => {
	console.log('listening on *:3000');
}).on('error', () => {});

const io = socketio.listen(server);
io.sockets.on('connection', (sock) => {
	const parseTicks = new TickEventParser();
	const notify = stream.Writable({
		objectMode: true,
		write(chunk, _, callback) {
			sock.emit('tick', JSON.stringify(chunk));
			callback();
		}
	});
	const bridge = new net.Socket();
	bridge.connect(
		process.argv[3] || 5555,
		process.argv[2] || 'localhost',
		() => {
			bridge.write("-banana\n");
			bridge.pipe(split2()).pipe(parseTicks).pipe(notify);
		}
	);
});
