class speechBubble {
	constructor(player) {
		this.p = player;
	}

	cmdPopup(key) {
		SpriteData[key].manager.renderingGroupId = 1;
		const popup = new BABYLON.Sprite(key, SpriteData[key].manager);
		popup.color.a = 1;
		popup.size = 5;
		for (let axis of ['x', 'y', 'z'])
			popup.position[axis] = this.p.sprite.position[axis];
		popup.position.y += this.p.sprite.size;
		popup.isVisible = true;

		const cascade = new BABYLON.Animation("cascadePopup",
			'position.y',
			15 * game.tickrate,
			BABYLON.Animation.ANIMATIONTYPE_FLOAT,
			BABYLON.Animation.ANIMATIONLOOPMODE_CONSTANT
		);
		var start = popup.position.y;
		var end = start / 2;
		cascade.setKeys([
			{ frame: 0, value: start },
			{ frame: 40, value: start },
			{ frame: 75, value: ((end - start) / 2) + start},
			{ frame: 100, value: end }
		]);

		const fade = new BABYLON.Animation("fadePopup",
			'color.a',
			15 * game.tickrate,
			BABYLON.Animation.ANIMATIONTYPE_FLOAT,
			BABYLON.Animation.ANIMATIONLOOPMODE_CONSTANT
		);
		start = 1;
		end = 0;
		fade.setKeys([
			{ frame: 0, value: start },
			{ frame: 50, value: start},
			{ frame: 100, value: end }
		]);

		game.scene.beginDirectAnimation(
			popup,
			[cascade, fade],
			0,
			100,
			false,
			1,
			() => {
				popup.dispose();
			}
		);
	}
}
