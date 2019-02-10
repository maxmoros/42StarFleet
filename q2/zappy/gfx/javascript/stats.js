class TeamStats {
	constructor (teamName, teamId) {
		this.teamName = teamName;
		this.teamId = teamId;
		this.eggCount = 0;
		this.won = false;
		this._cache = {
			levelInfo: { dirty: true, value: { highest: 0, countHighest: 0 } },
			players: { dirty: true, value: [] },
		};
	}

	get players() {
		if (this._cache.players.dirty) {
			this._cache.players.dirty = false;
			this._cache.players.value =
				game.players.filter(p => p.alive && p.team === this.teamId);
		}
		return this._cache.players.value;
	}

	get levelInfo() {
		if (this._cache.levelInfo.dirty) {
			this._cache.levelInfo.dirty = false;
			const v = this._cache.levelInfo.value;
			v.highest = 0;
			v.countHighest = 0;
			for (let p of this.players) {
				if (p.level > v.highest) {
					v.highest = p.level;
					v.countHighest = 1;
				} else if (p.level === v.highest) {
					v.countHighest += 1;
				}
			}
		}
		return this._cache.levelInfo.value;
	}

	get highestLevelOnTeam() {
		return this.levelInfo.highest;
	}

	get playersAtHighestLevel() {
		return this.levelInfo.countHighest;
	}

	get playersOnTeam() {
		return this.players.length;
	}

	processEvent(ev) {
		switch (ev.type) {
		case 'DONE_LAYING_EGG':
			if (ev.teamId === this.teamId) {
				this.eggCount += 1;
			}
			break;
		case 'EGG_HATCH':
			if (ev.teamId === this.teamId) {
				this.eggCount -= 1;
				this._cache.players.dirty = true;
				this._cache.levelInfo.dirty = true;
			}
			break;
		case 'DEATH':
		case 'INCANT_FINISH':
			this._cache.players.dirty = true;
			this._cache.levelInfo.dirty = true;
			break;
		case 'GAME_END':
			if (ev.winningTeamIds.includes(this.teamId)) {
				this.won = true;
			}
			break;
		default:
			break;
		}
	}
}

stats = {
	addTeams: function (teamNames) {
		this.teams = teamNames.map((teamName, teamId) => {
			return new TeamStats(teamName, teamId);
		});
	},
	processEvent: function (ev) {
		if (this.teams)
			this.teams.forEach(ts => ts.processEvent(ev));
	}
};
