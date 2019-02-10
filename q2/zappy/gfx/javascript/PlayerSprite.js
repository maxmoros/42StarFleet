class PlayerSprite extends BABYLON.Sprite {
	constructor({ player, manager, dimensions, animations, size }) {
		manager.renderingGroupId = 1;
		super("player", manager);
		this.size = size;
		this.player = player;
		this.playWalkAnimation = animations.walk.bind(this);
		this.idleAnimation = animations.idle.bind(this);
		this.playLeadIncantationAnimation = animations.leadIncant.bind(this);
		this.offset = Tile.generatePlayerSpriteOffset();
		this.position.y = this.height / 2;
		this.position.z = (this.player.x * game.tileSize) + this.offset.x;
		this.position.x = (this.player.y * game.tileSize) + this.offset.y;
		this.isPickable = true;
		manager.isPickable = true;
	}

	resetAndIdle() {
		this.stopAnimation();
		this.position.x = this.player.y * game.tileSize + this.offset.y;
		this.position.z = this.player.x * game.tileSize + this.offset.x;
		this.idleAnimation();
	}

	advanceAnimation() {
		this.playWalkAnimation(100);
		this.slideInDirection({
			direction: this.player.facing,
			speed: 1,
			onAnimationEnd: this.resetAndIdle.bind(this)
		});
	}

	getKickedAnimation(direction) {
		this.resetAndIdle();
		this.playWalkAnimation(10); // kick frantically
		this.slideInDirection({
			direction,
			speed: 6,
			onAnimationEnd: this.resetAndIdle.bind(this)
		});
	}

	slideInDirection({ direction, speed, onAnimationEnd }) {
		const axis = ['n', 's'].includes(direction) ? "x" : "z";
		const slide = new BABYLON.Animation("slidePlayer",
			`position.${axis}`,
			15 * game.tickrate,
			BABYLON.Animation.ANIMATIONTYPE_FLOAT,
			BABYLON.Animation.ANIMATIONLOOPMODE_CONSTANT
		);
		const start = this.position[axis];
		const end = start + game.tileSize * { n: -1, w: -1, s: 1, e: 1}[direction];
		slide.setKeys([
			{ frame: 0, value: start },
			{ frame: 100, value: end }
		]);
		game.scene.beginDirectAnimation(
			this,
			[slide],
			0,
			100,
			false,
			speed,
			onAnimationEnd
		);
	}
}
