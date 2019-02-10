const SpriteData = {};

function facingCamera(facing) {
	return facing === 's' || facing === 'e';
}

function shouldInvert(facing) {
	return facing === 'n' || facing === 'e';
}

const fftaPlayerSprite = (spriteName) => ({
	assetPath: `player-sprites/${spriteName}/${spriteName}-sheet.png`,
	getPortraitPath: (teamId) => {
		return `player-sprites/${spriteName}/team${teamId % 2 + 1}-portrait.png`;
	},
	getMaxSprites: (game) => game.MAX_PLAYERS,
	dimensions: {
		width: 32,
		height: 32,
	},
	size: 12,
	animations: {
		walk: function (legInterval) {
			let startFrame = 2;
			if (facingCamera(this.player.facing))
				startFrame += 4;
			if (this.player.team % 2 !== 0)
				startFrame += 8;
			this.invertU = shouldInvert(this.player.facing);
			this.playAnimation(
				startFrame,
				startFrame + 1,
				true,
				legInterval * 2,
				this.idle
			);
		},
		idle: function () {
			this.cellIndex = 1;
			if (facingCamera(this.player.facing))
				this.cellIndex += 4;
			if (this.player.team % 2 !== 0)
				this.cellIndex += 8;
			this.invertU = shouldInvert(this.player.facing);
		},
		leadIncant: function () {
			let startFrame = 0;
			if (facingCamera(this.player.facing))
				startFrame += 4;
			if (this.player.team % 2 !== 0)
				startFrame += 8;
			this.invertU = shouldInvert(this.player.facing);
			this.playAnimation(
				startFrame,
				startFrame + 1,
				true,
				500,
				this.idle
			);
		},
	}
});

SpriteData.blackMage = fftaPlayerSprite('human-blackmage');
SpriteData.mogKnight = fftaPlayerSprite('moogle-mogknight');
SpriteData.bangaa = fftaPlayerSprite('bangaa-warrior');

const numberedResource = (path) => ({
	assetPath: `numbered_resources/${path}`,
	getMaxSprites: (game) => game.x * game.y,
	dimensions: {
		width: 192,
		height: 192,
	},
	size: 5,
	yOffsetOverride: 2.7,
});

SpriteData.eggs = numberedResource('eggs-numbered.png');
SpriteData.food = numberedResource('watermelons-numbered.png');
SpriteData.stone0 = numberedResource('linemate-numbered.png');
SpriteData.stone1 = numberedResource('deraumere-numbered.png');
SpriteData.stone2 = numberedResource('sibur-numbered.png');
SpriteData.stone3 = numberedResource('mendiane-numbered.png');
SpriteData.stone4 = numberedResource('phiras-numbered.png');
SpriteData.stone5 = numberedResource('thystame-numbered.png');

SpriteData.put = {
	assetPath: 'inventory.png',
	getMaxSprites: (game) => game.MAX_PLAYERS,
	dimensions: {
		height: 480,
		width: 480
	}
};

SpriteData.putFail = {
	assetPath: 'inventory.png',
	getMaxSprites: (game) => game.MAX_PLAYERS,
	dimensions: {
		height: 480,
		width: 480
	}
};

SpriteData.take = {
	assetPath: 'inventory.png',
	getMaxSprites: (game) => game.MAX_PLAYERS,
	dimensions: {
		height: 480,
		width: 480
	}
};

SpriteData.takeFail = {
	assetPath: 'inventory.png',
	getMaxSprites: (game) => game.MAX_PLAYERS,
	dimensions: {
		height: 480,
		width: 480
	}
};

SpriteData.inventory = {
	assetPath: 'inventory.png',
	getMaxSprites: (game) => game.MAX_PLAYERS,
	dimensions: {
		height: 480,
		width: 480
	}
};

SpriteData.broadcast = {
	assetPath: 'broadcast.png',
	getMaxSprites: (game) => game.MAX_PLAYERS,
	dimensions: {
		height: 50,
		width: 50
	}
};

SpriteData.see = {
	assetPath: 'see.png',
	getMaxSprites: (game) => game.MAX_PLAYERS,
	dimensions: {
		height: 120,
		width: 120
	}
};

SpriteData.kick = {
	assetPath: 'kick.png',
	getMaxSprites: (game) => game.MAX_PLAYERS,
	dimensions: {
		height: 225,
		width: 225,
	}
};

SpriteData.kickFail = {
	assetPath: 'kick.png',
	getMaxSprites: (game) => game.MAX_PLAYERS,
	dimensions: {
		height: 225,
		width: 225,
	}
};

SpriteData.incant = {
	assetPath: 'death.png',
	getMaxSprites: (game) => game.MAX_PLAYERS,
	dimensions: {
		height: 120,
		width: 120,
	}
};

SpriteData.incantFail = {
	assetPath: 'death.png',
	getMaxSprites: (game) => game.MAX_PLAYERS,
	dimensions: {
		height: 120,
		width: 120,
	}
};

SpriteData.death = {
	assetPath: 'death.png',
	getMaxSprites: (game) => game.MAX_PLAYERS,
	dimensions: {
		height: 120,
		width: 120,
	}
};

SpriteData.fork = {
	assetPath: 'egg0.png',
	getMaxSprites: (game) => game.MAX_PLAYERS,
	dimensions: {
		height: 200,
		width: 240
	}
};

SpriteData.fail = {
	assetPath: 'fail.png',
	getMaxSprites: (game) => game.MAX_PLAYERS,
	dimensions: {
		height: 334,
		width: 334
	}
};
