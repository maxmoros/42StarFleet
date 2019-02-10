function createCustomCamera(canvas, scene) {
	var camera = new BABYLON.FreeCamera("camera1", new BABYLON.Vector3(200, 200, 200), scene);

	// This targets the camera to scene origin (Coord: (0, 0, 0))
	//	camera.setTarget(new BABYLON.Vector3(0, 0, 0));
	camera.rotation = new BABYLON.Vector3((Math.PI / 4), 5 * Math.PI / 4, 0);

	// This attaches the camera to the canvas
	camera.attachControl(canvas, true);
	camera.inputs.attached.mouse.detachControl(canvas);

	// Remove default keyboard:
	camera.inputs.removeByType("FreeCameraKeyboardMoveInput");

	// Create our own manager:
	var customCameraInput = function () {
		this._keys = [];
		this.keysLeft = [37];
		this.keysRight = [39];
		this.keysUp = [38];
		this.keysDown = [40];
		this.keysPlus = [187];
		this.keysMinus = [189];
		this.sensibility	= 5;
		this.zoomSensibility = 5;
	};

	// Hooking keyboard events
	customCameraInput.prototype.attachControl = function (element, noPreventDefault) {
		var _this = this;
		if (!this._onKeyDown) {
			element.tabIndex = 1;
			this._onKeyDown = function (evt) {
				if (_this.keysUp.indexOf(evt.keyCode) !== -1 ||
					_this.keysDown.indexOf(evt.keyCode) !== -1 ||
					_this.keysLeft.indexOf(evt.keyCode) !== -1 ||
                    _this.keysRight.indexOf(evt.keyCode) !== -1	||
                    _this.keysPlus.indexOf(evt.keyCode) !== -1	||
                    _this.keysMinus.indexOf(evt.keyCode) !== -1	) {
					var index = _this._keys.indexOf(evt.keyCode);
					if (index === -1) {
						_this._keys.push(evt.keyCode);
					}
					if (!noPreventDefault) {
						evt.preventDefault();
					}
				}
			};
			this._onKeyUp = function (evt) {
				if (_this.keysUp.indexOf(evt.keyCode) !== -1	||
					_this.keysDown.indexOf(evt.keyCode) !== -1	||
                    _this.keysLeft.indexOf(evt.keyCode) !== -1	||
                    _this.keysRight.indexOf(evt.keyCode) !== -1	||
                    _this.keysPlus.indexOf(evt.keyCode) !== -1	||
                    _this.keysMinus.indexOf(evt.keyCode) !== -1	) {
					var index = _this._keys.indexOf(evt.keyCode);
					if (index >= 0) {
						_this._keys.splice(index, 1);
					}
					if (!noPreventDefault) {
						evt.preventDefault();
					}
				}
			};

			element.addEventListener("keydown", this._onKeyDown, false);
			element.addEventListener("keyup", this._onKeyUp, false);
			BABYLON.Tools.RegisterTopRootEvents([
				{ name: "blur", handler: this._onLostFocus }
			]);
		}
	};

	// Unhook
	customCameraInput.prototype.detachControl = function (element) {
		if (this._onKeyDown) {
			element.removeEventListener("keydown", this._onKeyDown);
			element.removeEventListener("keyup", this._onKeyUp);
			BABYLON.Tools.UnregisterTopRootEvents([
				{ name: "blur", handler: this._onLostFocus }
			]);
			this._keys = [];
			this._onKeyDown = null;
			this._onKeyUp = null;
		}
	};

	// This function is called by the system on every frame
	customCameraInput.prototype.checkInputs = function () {
		if (this._onKeyDown) {
			var camera = this.camera;
			// Keyboard
			for (var index = 0; index < this._keys.length; index++) {
				var keyCode = this._keys[index];
				if (this.keysUp.indexOf(keyCode) !== -1) {
					camera.position.x -= this.sensibility;
				}
				else if (this.keysDown.indexOf(keyCode) !== -1) {
					camera.position.x += this.sensibility;
				}
				if (this.keysLeft.indexOf(keyCode) !== -1) {
					camera.position.z -= this.sensibility;
				}
				else if (this.keysRight.indexOf(keyCode) !== -1) {
					camera.position.z += this.sensibility;
				}
				if (this.keysMinus.indexOf(keyCode) !== -1) {
					camera.position.x += this.sensibility;
					camera.position.y += this.sensibility;
					camera.position.z += this.sensibility;
				}
				else if (this.keysPlus.indexOf(keyCode) !== -1) {
					camera.position.x -= this.sensibility;
					camera.position.y -= this.sensibility;
					camera.position.z -= this.sensibility;
				}
			}
		}
	};
	customCameraInput.prototype.getTypeName = function () {
		return "customCameraInput";
	};
	customCameraInput.prototype._onLostFocus = function (e) {
		this._keys = [];
	};
	customCameraInput.prototype.getSimpleName = function () {
		return "customInput";
	};

	// Connect to camera:
	camera.inputs.add(new customCameraInput());
}
