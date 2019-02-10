class Tile {
	constructor(opts) {
		this.x = opts.x;
		this.y = opts.y;
		this.inventory = {
			eggs: 0,
			food: 0,
			stone0: 0,
			stone1: 0,
			stone2: 0,
			stone3: 0,
			stone4: 0,
			stone5: 0
		};
		this.sprites = {};
	}

	get center() {
		return { x: this.x * game.tileSize, y: this.y * game.tileSize };
	}

	removeContent(type, amt) {
		this.inventory[type] -= amt;
		this.sprites[type].count -= amt;
	}

	addContent(type, amt) {
		if (!this.sprites[type]) {
			const sp = new TileContentSprite(type);
			this.sprites[type] = sp;
			sp.addToTile(this);
		}
		this.inventory[type] += amt;
		this.sprites[type].count += amt;
	}

	static generatePlayerSpriteOffset() {
		let y = randomInNonnegativeRange(0.05, 0.3) * game.tileSize * -1;
		let x = randomInNonnegativeRange(0, 0.3) * game.tileSize;
		if (Math.random() < 0.5)
			x *= -1;
		return { x, y };
	}

	static generateContentSpriteOffset() {
		let y = randomInNonnegativeRange(0.05, 0.3) * game.tileSize;
		let x = randomInNonnegativeRange(0, 0.3) * game.tileSize;
		if (Math.random() < 0.5)
			x *= -1;
		return { x, y };
	}
}

function randomInNonnegativeRange(min, max) {
	return Math.random() * (max - min) + min;
}
