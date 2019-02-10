class Game {
	constructor(opts) {
		this.x = opts.x;
		this.y = opts.y;
		this.teams = opts.teams;
		this.tickrate = opts.tickrate;
		this.currentTick = opts.currentTick;
		this.players = [];
		this.MAX_PLAYERS = 1024;
		this.tileSize = 25;
		this.tiles = [];
		this.gameOver = false;
		for (let i = 0; i < this.x; i++)
			this.tiles.push([]);

		this.canvas = undefined;
		this.engine = undefined;
		this.scene = undefined;

		this.camera = undefined;
		this.skybox = undefined;
		this.board = undefined;
		this.sunlight = undefined;
		this.alpha = undefined;
	}

	startup() {
		this.canvas = document.getElementById('renderCanvas');		// Get the canvas element
		this.engine = new BABYLON.Engine(this.canvas, true);		// Generate the BABYLON 3D engine
		this.scene = new BABYLON.Scene(this.engine);				// Create the scene object
		this.sunlight = new BABYLON.HemisphericLight('hemiLight', new BABYLON.Vector3(1, 1, 0), this.scene);
		this.sunlight.intensity = 0;

		this.board = new Board();
		this.board.createMesh({x:this.x, y:this.y}, this.scene);
		this.initSpriteManagers();

		this.camera = createCustomCamera(this.canvas, this.scene);
	
		var skybox = BABYLON.Mesh.CreateBox("skyBox", 5026, this.scene, undefined, BABYLON.Mesh.BACKSIDE);
		var skyboxMaterial = new BABYLON.BackgroundMaterial("skyBox", this.scene);
		skyboxMaterial.reflectionTexture = new BABYLON.CubeTexture("skybox0/skybox", this.scene);
		skyboxMaterial.reflectionTexture.coordinatesMode = BABYLON.Texture.SKYBOX_MODE;
		skyboxMaterial.backFaceCulling = false;
		//	skyboxMaterial.diffuseColor = new BABYLON.Color3(0, 0, 0);
		//	skyboxMaterial.specularColor = new BABYLON.Color3(0, 0, 0);
		skybox.material = skyboxMaterial;
		skybox.infiniteDistance = true;
		skybox.renderingGroupId = 0;
		// Register a render loop to repeatedly render the scene
		this.alpha = 0;
	
		this.gui = new Gui();

		game.scene.registerBeforeRender( () => {
			skybox.rotation.y = this.alpha;
			this.alpha += 0.0005;
		});
		this.engine.runRenderLoop(function () {
			game.scene.render();
		});
	
		// Watch for browser/canvas resize events
		window.addEventListener('resize', function () { 
			game.engine.resize();
		});
	}

	addPlayer(pinfo) {
		const player = new playerAvatar(pinfo);
		player.createSprite();
		this.players[player.id] = player;
	}

	get_player(pid) {
		if (this.players[pid]) {
			return this.players[pid];
		}
		else {
			console.warn('Failed to get_player');
		}
	}

	addTile({ x, y }) {
		return (this.tiles[x][y] = new Tile({ x, y }));
	}

	getContentSpriteManagerFor(type) {
		if (SpriteData[type].manager)
			return SpriteData[type].manager;
		console.warn('couldn\'t get sprite manager for ' + type);
	}

	getTeamSpriteName(teamId) {
		const teamSprites = [
			'blackMage',
			'mogKnight',
			'bangaa',
			'blackMage',
			'mogKnight',
			'bangaa'
		];
		return teamSprites[teamId % teamSprites.length];
	}

	initSpriteManagers() {
		for (let spriteName in SpriteData) {
			const sdEntry = SpriteData[spriteName];
			sdEntry.manager = new BABYLON.SpriteManager(
				`${spriteName}-manager`,
				sdEntry.assetPath,
				sdEntry.getMaxSprites(this),
				sdEntry.dimensions,
				this.scene
			);
		}
	}
}
