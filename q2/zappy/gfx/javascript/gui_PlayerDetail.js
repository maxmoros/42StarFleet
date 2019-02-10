class PlayerDetail extends BABYLON.GUI.Rectangle {
	constructor() {
		super("player-detail-container");
		this.adaptHeightToChildren = true;
		this.width = "360px";
		this.paddingRight = "20px";
		this.paddingBottom = "20px";
		this.fontSize = 14;
		this.addInventoryPanel();
		this.addPlayerSummary();
		this.isVisible = false;
		this.horizontalAlignment
			= BABYLON.GUI.Control.HORIZONTAL_ALIGNMENT_RIGHT;
		this.verticalAlignment
			= BABYLON.GUI.Control.VERTICAL_ALIGNMENT_BOTTOM;
	}

	addInventoryPanel() {
		this.inventoryPanel = new PlayerInventoryPanel();
		this.inventoryPanel.horizontalAlignment
			= BABYLON.GUI.Control.HORIZONTAL_ALIGNMENT_RIGHT;
		this.addControl(this.inventoryPanel);
	}

	addPlayerSummary() {
		this.playerSummary = new PlayerSummary();
		this.playerSummary.horizontalAlignment
			= BABYLON.GUI.Control.HORIZONTAL_ALIGNMENT_LEFT;
		this.addControl(this.playerSummary);
	}

	update() {
		if (game.gui.followedPlayer) {
			this.isVisible = true;
			this.inventoryPanel.update();
			this.playerSummary.update();
		}
	}
}

class PlayerSummary extends BABYLON.GUI.StackPanel {
	constructor() {
		super("player-summary");
		this.teamAndId = new PlayerTeamAndIdElement();
		this.portrait = new PlayerPortraitElement();
		this.playerStatus = new PlayerStatusElement();
		this.addControl(this.teamAndId);
		this.addControl(this.portrait);
		this.addControl(this.playerStatus);
		this.portrait.horizontalAlignment =
			BABYLON.GUI.HORIZONTAL_ALIGNMENT_LEFT;

	}
	update() {
		this.teamAndId.update();
		this.portrait.update();
		this.playerStatus.update();
	}
}

class PlayerTeamAndIdElement extends BABYLON.GUI.TextBlock {
	constructor() {
		super("player-team-and-id");
		this.width = "240px";
		this.height = "60px";
		this.paddingLeft = "10px";
		this.paddingTop = "10px";
		this.fontSize = 14;
		this.color = 'white';
		this.textHorizontalAlignment = BABYLON.GUI.HORIZONTAL_ALIGNMENT_LEFT;
	}

	update() {
		const player = game.gui.followedPlayer;
		const maybeEllipsis =
			game.teams[player.team].length > 17 ? "..." : "";
		this.text = `team: ${game.teams[player.team].slice(0, 17)}`
			+ maybeEllipsis
			+ `\nplayer ID: ${player.id}`;
	}
}

class PlayerPortraitElement extends BABYLON.GUI.Image {
	constructor() {
		super("player-portrait");
		this.height = "166px";
		this.width = "128px";
		this.paddingLeft = "20px";
		this.stretch = BABYLON.GUI.Image.STRETCH_UNIFORM;
	}

	update() {
		const teamId = game.gui.followedPlayer.team;
		const sdEntry = SpriteData[game.getTeamSpriteName(teamId)];
		this.source = sdEntry.getPortraitPath(teamId);
	}
}

class PlayerStatusElement extends BABYLON.GUI.TextBlock {
	constructor() {
		super("player-status-element");
		this.width = "228px";
		this.height = "74px";
		this.fontSize = 14;
		this.color = 'white';
		this.left = "16px";
		this.horizontalAlignment =
			BABYLON.GUI.Control.HORIZONTAL_ALIGNMENT_LEFT;
		this.textHorizontalAlignment =
			BABYLON.GUI.Control.HORIZONTAL_ALIGNMENT_LEFT;
	}

	update() {
		const player = game.gui.followedPlayer;
		this.text = `level ${player.level}`
		+ `\naction: ${player.currentAction}`
		+ `\nat <${player.x}, ${player.y}>`;
	}
}

class PlayerInventoryPanel extends BABYLON.GUI.StackPanel {
	constructor() {
		super("player-inventory-panel");
		this.isVertical = true;
		this.items = {};
		this.addItem('food', 'food');
		this.addItem('stone0', 'linemate');
		this.addItem('stone1', 'deraumere');
		this.addItem('stone2', 'sibur');
		this.addItem('stone3', 'mendiane');
		this.addItem('stone4', 'phiras');
		this.addItem('stone5', 'thystame');
	}

	addItem(itemType, itemName) {
		this.items[itemType] = new PlayerInventoryItem(itemType, itemName);
		this.addControl(this.items[itemType]);
	}

	update() {
		Object.keys(this.items).forEach(key => {
			this.items[key].updateCount(game.gui.followedPlayer.inventory[key]);
		});
	}
}

class PlayerInventoryItem extends BABYLON.GUI.StackPanel {
	constructor(itemType, itemName) {
		super(`player-inventory-item-${itemType}`);
		this.isVertical = false;
		this.itemType = itemType;
		this.itemName = itemName;
		this.width = '140px';
		this.height = '32px';
		this.addItemSprite();
		this.addTextBlock();
	}

	addTextBlock() {
		this.textBlock =
			new BABYLON.GUI.TextBlock(`${this.itemType}-inv-item-textblock`);
		this.textBlock.paddingTop = "7px";
		this.textBlock.color = "white";
		this.textBlock.fontSize = 14;
		this.textBlock.height = '32px';
		this.textBlock.width = '80px';
		this.textBlock.textHorizontalAlignment =
			BABYLON.GUI.Control.HORIZONTAL_ALIGNMENT_LEFT;
		this.addControl(this.textBlock);
	}

	addItemSprite() {
		const sdEntry = SpriteData[this.itemType];
		const spriteImage = new BABYLON.GUI.Image(
			`${this.itemType}-sprite`,
			sdEntry.assetPath
		);
		spriteImage.cellHeight = sdEntry.dimensions.height;
		spriteImage.cellWidth = sdEntry.dimensions.width;
		spriteImage.cellId = 0;
		spriteImage.stretch = BABYLON.GUI.Image.STRETCH_UNIFORM;
		const spriteBounds = new BABYLON.GUI.Rectangle(
			`pii-${this.itemType}-sprite-container`
		);
		spriteBounds.width = '32px';
		spriteBounds.height = '32px';
		spriteBounds.thickness = 0;
		spriteBounds.addControl(spriteImage);
		this.addControl(spriteBounds);
	}

	updateCount(n) {
		this.textBlock.text = `${n} ${this.itemName}`;
	}
}
