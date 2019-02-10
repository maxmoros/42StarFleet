class TileContentSprite extends BABYLON.Sprite {
	constructor(type) {
		const manager = game.getContentSpriteManagerFor(type);
		manager.renderingGroupId = 1;
		super(type, manager);
		this._count = 0;
		this.size = 5;
		this.position.y = 2.7;
		this.isVisible = false;
		this.cellIndex = 1;
	}

	set count(amt) {
		this._count = amt;
		if (this._count <= 0)
			this.hide();
		else
			this.showCount();
	}

	hide() {
		this.isVisible = false;
	}

	showCount() {
		this.isVisible = true;
		if (this._count <= 10)
			this.cellIndex = this._count;
		else if (this._count <= 50)
			this.cellIndex = Math.floor(this._count / 10) + 9;
		else
			this.cellIndex = 15;
	}

	get count() {
		return this._count;
	}

	addToTile(tile) {
		this.tile = tile;
		this.offset = Tile.generateContentSpriteOffset();
		this.position.x = tile.y * game.tileSize + this.offset.y;
		// size and y position set just once in constructor
		this.position.z = tile.x * game.tileSize + this.offset.x;
	}
}
