const TILE_ASSET	= 'desert-tile-60.png';

class Board {
	constructor(opts) {
		this._mesh		= undefined;
	}
	
	createMesh(dim, scene) {
		this._mesh = BABYLON.MeshBuilder.CreateBox("board", {height:0.5, width:game.tileSize * dim.y, depth:game.tileSize * dim.x}, scene);
		this._mesh.position = {x:((dim.y / 2) - 0.5) * game.tileSize, y:-0.7, z:((dim.x / 2) - 0.5) * game.tileSize};

		var tileTexture = new BABYLON.BackgroundMaterial("tileTexture", scene);
		tileTexture.diffuseTexture = new BABYLON.Texture(TILE_ASSET, scene);
		tileTexture.diffuseTexture.uScale = dim.x; //Repeat {x} times on the Vertical Axes
		tileTexture.diffuseTexture.vScale = dim.y; //Repeat {y} times on the Horizontal Axes
		tileTexture.opacityFresnel = false;
		this._mesh.material = tileTexture;
		this._mesh.renderingGroupId = 1;
	}
}
