function addTranslucentBackground(container) {
	const back = new BABYLON.GUI.Rectangle('backdrop');
	back.height = container.height;
	back.width = container.width;
	back.horizontalAlignment = container.horizontalAlignment;
	back.verticalAlignment = container.verticalAlignment;
	back.zIndex = container.zIndex - 1;
	back.background = "black";
	back.color = "grey";
	back.alpha = 0.5;
	container.addControl(back);
}


class Gui {
	constructor() {
		const _gui =
			BABYLON.GUI.AdvancedDynamicTexture.CreateFullscreenUI("myUI");

		this.playerDetail = new PlayerDetail();
		_gui.addControl(this.playerDetail);
		addTranslucentBackground(this.playerDetail);

		this.leaderboard = new Leaderboard();
		_gui.addControl(this.leaderboard);
		addTranslucentBackground(this.leaderboard);

		game.scene.onPointerDown = () => {
			const pickResult = game.scene.pickSprite(
				game.scene.pointerX,
				game.scene.pointerY,
				(sprite) => sprite.isPickable
			);
			if (pickResult.pickedSprite && pickResult.pickedSprite.player) {
				this.followedPlayer = pickResult.pickedSprite.player;
				this.playerDetail.update();
			}
		};
	}

	update() {
		if (this.playerDetail)
			this.playerDetail.update();
		if (this.leaderboard)
			this.leaderboard.update();
	}
}
