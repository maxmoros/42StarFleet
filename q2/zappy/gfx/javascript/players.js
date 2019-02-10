const compass = ['n', 'e', 's', 'w', 'n'];

const itemNames = {
	stone0: 'linemate',
	stone1: 'deraumere',
	stone2: 'sibur',
	stone3: 'mendiane',
	stone4: 'phiras',
	stone5: 'thystame',
	food: 'food',
};

class playerAvatar {
	constructor(opts) {
		this.bubble = new speechBubble(this);
		this.id = opts.id;
		this.x = opts.x;
		this.y = opts.y;
		this.inventory = {};
		for (let i in opts.inv) {
			this.inventory[`stone${i}`] = opts.inv[i];
		}
		this.inventory.food = opts.food;
		this.level = opts.level;
		this.team = opts.team;
		this.facing = opts.facing || 's';
		this.alive = true;
		this._lastAction = {
			title: 'idle', untilTick: Number.POSITIVE_INFINITY
		};
	}

	setAction(title, timer) {
		this._lastAction.title = title;
		this._lastAction.untilTick = game.currentTick + timer;
	}

	get currentAction() {
		if (game.currentTick >= this._lastAction.untilTick) {
			this.setAction('idle', Number.POSITIVE_INFINITY);
		}
		return this._lastAction.title;
	}

	broadcast() {
		this.bubble.cmdPopup('broadcast');
		this.setAction('broadcast', 7) ;
	}

	eatFood() {
		this.inventory.food -= 1;
	}

	right() {
		this.facing = compass[compass.indexOf(this.facing) + 1];
		this.sprite.idleAnimation();
		this.setAction('right', 7);
	}

	left() {
		this.facing = compass[compass.lastIndexOf(this.facing) - 1];
		this.sprite.idleAnimation();
		this.setAction('left', 7);
	}

	idle() {
		this.sprite.idleAnimation();
		this.setAction('idle', Number.POSITIVE_INFINITY);
	}

	put(tile, type, isSuccess) {
		if (isSuccess === 1) {
			this.bubble.cmdPopup('inventory');
			this.inventory[type] -= 1;
			game.tiles[tile.x][tile.y].addContent(type, 1);
		}
		else {
			this.fail();
		}
		const maybeFail = isSuccess ? "" : " (FAIL)";
		const itemName = itemNames[type] ? itemNames[type] : "???";
		this.setAction(`put ${itemName}${maybeFail}`, 7);
	}

	leadIncant(isSuccess) {
		this.sprite.playLeadIncantationAnimation();
		const maybeFail = isSuccess ? "" : " (FAIL)";
		this.setAction(`incantation${maybeFail}`, 300);
	}

	finishLeadIncant(newLevel) {
		this.sprite.resetAndIdle();
		this.level = newLevel;
		this.idle();
	}

	layEgg() {
		this.setAction('fork', 42);
		this.bubble.cmdPopup('fork');
	}

	doneLayingEgg(tile) {
		game.tiles[tile.x][tile.y].addContent('eggs', 1);
		this.idle();
	}

	death() {
		if (!this.alive)
			return ;
		this.bubble.cmdPopup('death');
		this.setAction('DEAD', Number.POSITIVE_INFINITY);
		this.alive = false;
		this.sprite.dispose();
	}

	take(tile, type, isSuccess) {
		if (isSuccess === 1) {
			this.inventory[type] += 1;
			this.bubble.cmdPopup('inventory');
			game.tiles[tile.x][tile.y].removeContent(type, 1);
		}
		else {
			this.fail();
		}
		const maybeFail = isSuccess ? "" : " (FAIL)";
		const itemName = itemNames[type] ? itemNames[type] : "???";
		this.setAction(`take ${itemName}${maybeFail}`, 7);
	}

	checkInventory() {
		this.bubble.cmdPopup('inventory');
		this.setAction('inventory', 1);
	}

	see() {
		this.bubble.cmdPopup('see');
		this.setAction('see', 7);
	}

	createSprite() {
		const opts = {};
		Object.assign(opts, SpriteData[game.getTeamSpriteName(this.team)]);
		opts.player = this;
		this.sprite = new PlayerSprite(opts);
		this.idle();
	}

	moveDirection(dir) {
		if (false === ['n', 'e', 's', 'w'].includes(dir))
			console.warn(`${this.id}: invalid direction '${dir}'`);
		this.x = (this.x + { n: 0, e: 1, w: -1, s: 0 }[dir] + game.x) % game.x;
		this.y = (this.y + { n: -1, e: 0, w: 0, s: 1 }[dir] + game.y) % game.y;
	}

	advance() {
		this.sprite.advanceAnimation();
		this.moveDirection(this.facing);
		this.setAction('advance', 7);
	}

	kick(isSuccess) {
		const maybeFail = isSuccess ? "" : " (FAIL)";
		this.setAction(`kick${maybeFail}`, 7);
		if (!isSuccess)
			this.fail();
	}

	getKicked(dir) {
		this.sprite.getKickedAnimation(dir);
		this.moveDirection(dir);
	}

	fail() {
		this.bubble.cmdPopup('fail');
	}
	

}
