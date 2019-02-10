module.exports = {
	'SEE': {
		type: 'SEE',
		playerId: 0
	},
	'ADVANCE': {
		type: 'ADVANCE',
		playerId: 0
	},
	'RIGHT': {
		type: 'RIGHT',
		playerId: 0
	},
	'LEFT': {
		type: 'LEFT',
		playerId: 0
	},
	'DEATH': {
		type: 'DEATH',
		playerId: 0
	},
	'INVENTORY': {
		type: 'INVENTORY',
		playerId: 0
	},
	'TAKE': {
		type: 'TAKE',
		playerId: 0,
		objType: 0,
		x: 0,
		y: 0,
		isSuccess: 0
	},
	'PUT': {
		type: 'PUT',
		playerId: 0,
		objType: 0,
		x: 0,
		y: 0,
		isSuccess: 0
	},
	'BAD_COMMAND': {
		type: 'BAD_COMMAND',
		playerId: 0,
		message: ''
	},
	'BROADCAST': {
		type: 'BROADCAST',
		playerId: 0,
		message: ''
	},
	'CONNECT': {
		type: 'CONNECT',
		playerId: 0
	},
	'LAY_EGG': {
		type: 'LAY_EGG',
		playerId: 0
	},
	'DONE_LAYING_EGG': {
		type: 'DONE_LAYING_EGG',
		playerId: 0,
		teamId: 0,
		x: 0,
		y: 0
	},
	'EGG_HATCH': {
		type: 'EGG_HATCH',
		playerId: 0,
		teamId: 0,
		level: 0,
		x: 0,
		y: 0,
		energy: 0,
		facing: 'n',
		inventory: [0, 0, 0, 0, 0, 0]
	},
	'SPAWN_RESOURCE': {
		type: 'SPAWN_RESOURCE',
		x: 0,
		y: 0,
		objType: "stone0"
	},
	'INCANT_START': {
		type: 'INCANT_START',
		playerId: 0,
		willSucceed: 0,
		participants: [],
		newLevel: 0
	},
	'INCANT_FINISH': {
		type: 'INCANT_FINISH',
		playerId: 0,
		newLevel: 0,
		levelupPids: []
	},
	'KICK': {
		type: 'KICK',
		playerId: 0,
		direction: 'n',
		kickees: [],
	},
	'GAME_END': {
		type: 'GAME_END',
		winningTeamIds: []
	},
	'INIT': {
		width: 0,
		height: 0,
		tickrate: 0,
		startTick: 0,
		tiles: [{
			x: 0,
			y: 0,
			eggs: 0,
			food: 0,
			stones: [0, 0, 0, 0, 0, 0]
		}],
		commandDelays: [
			{cmd: "SEE", time: 7},
			{cmd: "ADVANCE", time: 7},
			{cmd: "RIGHT", time: 7},
			{cmd: "LEFT", time: 7},
			{cmd: "LEAD_RITUAL", time: 300},
			{cmd: "KICK", time: 7},
			{cmd: "BROADCAST", time: 7},
			{cmd: "TAKE", time: 7},
			{cmd: "PUT", time: 7},
			{cmd: "LAY_EGG", time: 42},
			{cmd: "EGG_HATCH", time: 600},
		],
		teamNames: [],
		players: [
			{
				playerId: 0,
				teamId: 0,
				level: 0,
				x: 0,
				y: 0,
				energy: 0,
				facing: 'n',
				food: 0,
				isConnected: 0,
				inventory: [0, 0, 0, 0, 0, 0]
			},
		]
	}
};
