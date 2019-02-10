const LEADERBOARD_ROWS_MAX_VISIBLE = 5;

class Leaderboard extends BABYLON.GUI.Rectangle {
	constructor() {
		super("leaderboard-container");
		this.height = "200px";
		this.width = "520px";
		this.top = 40;
		this.left = 20;
		this.horizontalAlignment =
			BABYLON.GUI.Control.HORIZONTAL_ALIGNMENT_LEFT;
		this.verticalAlignment = BABYLON.GUI.Control.VERTICAL_ALIGNMENT_TOP;
		this.isHitTestVisible = false;
		this.addHeader();
		this.addTickTracker();
		this.addRowsAndMaybeSlider();
	}

	addHeader() {
		this.header = new BABYLON.GUI.TextBlock('leaderboard-header');
		this.header.text = 'Leaderboard';
		this.header.fontSize = "16px";
		this.header.color = "skyBlue";
		this.header.width = 1;
		this.header.height = "30px";
		this.header.paddingLeft = "60px";
		this.header.top = "10px";
		this.header.verticalAlignment =
			BABYLON.GUI.Control.VERTICAL_ALIGNMENT_TOP;
		this.header.textHorizontalAlignment =
			BABYLON.GUI.Control.HORIZONTAL_ALIGNMENT_LEFT;
		this.header.isHitTestVisible = false;
		this.addControl(this.header);
	}

	addTickTracker() {
		this.tickTracker = new BABYLON.GUI.TextBlock('leaderboard-ticks');
		this.tickTracker.fontSize = '14px';
		this.tickTracker.color = 'yellow';
		this.tickTracker.resizeToFit = true;
		this.tickTracker.verticalAlignment =
			BABYLON.GUI.Control.VERTICAL_ALIGNMENT_TOP;
		this.tickTracker.horizontalAlignment =
			BABYLON.GUI.Control.HORIZONTAL_ALIGNMENT_RIGHT;
		this.addControl(this.tickTracker);
	}

	addRowsAndMaybeSlider() {
		const displayableRows =
			Math.min(LEADERBOARD_ROWS_MAX_VISIBLE, game.teams.length);
		this.minDisplayedIdx = 0;
		this.rowsContainer = new LeaderboardRows(displayableRows);
		this.addControl(this.rowsContainer);
		this.rowsContainer.verticalAlignment =
			BABYLON.GUI.VERTICAL_ALIGNMENT_TOP;
		this.rowsContainer.top = this.header.heightInPixels;
		if (displayableRows < game.teams.length) {
			const sliderMax = game.teams.length - displayableRows;
			this.addSlider(sliderMax);
			this.slider.onValueChangedObservable.add((value) => {
				this.minDisplayedIdx = sliderMax - Math.round(value);
				this.update();
			});
		}
	}

	addSlider(sliderMax) {
		this.slider = new BABYLON.GUI.Slider();
		this.slider.isVertical = true;
		this.slider.color = 'black';
		this.slider.alpha = 0.5;
		this.slider.minimum = 0;
		this.slider.maximum = sliderMax;
		this.slider.value = sliderMax;
		this.slider.horizontalAlignment =
			BABYLON.GUI.Control.HORIZONTAL_ALIGNMENT_LEFT;
		this.slider.verticalAlignment =
			BABYLON.GUI.Control.VERTICAL_ALIGNMENT_TOP;
		this.slider.top = this.header.heightInPixels
			+ this.rowsContainer.rows[0].paddingTopInPixels;
		this.addControl(this.slider);
		this.slider.height = `${(this.rowsContainer.rows.length)
			* this.rowsContainer.rows[0].heightInPixels
			- this.rowsContainer.rows[0].paddingTopInPixels}px`;
		this.slider.width = "20px";
		this.slider.left = "20px";
	}

	update() {
		this.rowsContainer.update(this.minDisplayedIdx);
		this.tickTracker.text = `${game.currentTick} (t=${game.tickrate})`;
	}
}


class LeaderboardRows extends BABYLON.GUI.StackPanel {
	constructor(maxVisibleRows) {
		super('leaderboard-rows');
		this.isVertical = true;
		this.width = 1;
		this.isHitTestVisible = false;
		this.rows = [];
		this.rows.length = maxVisibleRows;
		this.left = "40px";
		for (let i = 0; i < this.rows.length; i++) {
			this.rows[i] = new LeaderboardRow(i);
			this.addControl(this.rows[i]);
		}
	}

	update(minIdx) {
		const topTeams = [...stats.teams].sort((a, b) => {
			if (a.highestLevelOnTeam !== b.highestLevelOnTeam)
				return b.highestLevelOnTeam - a.highestLevelOnTeam;
			else if (a.playersAtHighestLevel !== b.playersAtHighestLevel)
				return b.playersAtHighestLevel - a.playersAtHighestLevel;
			else
				return a.teamId - b.teamId;
		});
		for (let i = 0; i < this.rows.length; i++) {
			this.rows[i].displayTeamStats(topTeams[minIdx + i], minIdx + i);
		}
	}
}

class LeaderboardRow extends BABYLON.GUI.Rectangle {
	constructor(idx) {
		super(`leaderboard-position-${idx + 1}`);
		this.isHitTestVisible = false;
		this.idx = idx;
		this.paddingTop = "14px";
		this.height = `${this.fontSizeInPixels + this.paddingTopInPixels}px`;
		this.width = "440px";
		this.color = "white";
		this.alpha = 1;
		this.thickness = 0;
		this.left = "5px";
		this.top = this.idx * (this.heightInPixels);
		this.horizontalAlignment =
			BABYLON.GUI.Control.HORIZONTAL_ALIGNMENT_LEFT;
		this.addIndexAndTeamNameColumn();
		this.addStatsColumn();
	}

	addIndexAndTeamNameColumn() {
		this.leftBlock = new BABYLON.GUI.TextBlock();
		this.leftBlock.fontSize = "16px";
		this.leftBlock.horizontalAlignment =
			BABYLON.GUI.Control.HORIZONTAL_ALIGNMENT_LEFT;
		this.leftBlock.textHorizontalAlignment =
			BABYLON.GUI.Control.HORIZONTAL_ALIGNMENT_LEFT;
		this.addControl(this.leftBlock);
	}

	addStatsColumn() {
		this.rightBlock = new BABYLON.GUI.TextBlock();
		this.rightBlock.fontSize = "16px";
		this.rightBlock.horizontalAlignment =
			BABYLON.GUI.Control.HORIZONTAL_ALIGNMENT_RIGHT;
		this.rightBlock.textHorizontalAlignment =
			BABYLON.GUI.Control.HORIZONTAL_ALIGNMENT_RIGHT;
		this.addControl(this.rightBlock);
	}

	displayTeamStats(s, idx) {
		const maybeEllipsis = s.teamName.length > 17 ? "... " : " ";
		const maxLvl = s.highestLevelOnTeam;
		const nMax = s.playersAtHighestLevel;
		this.leftBlock.text =
			`• ${idx + 1}: team '${s.teamName.slice(0, 17)}'` + maybeEllipsis;
		if (s.won) {
			this.rightBlock.text = 'win!';
			this.rightBlock.color = 'yellow';
		} else if (s.playersOnTeam === 0 && s.eggCount === 0) {
			this.rightBlock.text = 'eliminated!';
		} else {
			this.rightBlock.text =
				`${nMax} (of ${s.playersOnTeam}) players @ level ${maxLvl}`;
		}
	}
}
