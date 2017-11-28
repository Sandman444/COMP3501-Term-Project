#include <stdexcept>
#include <iostream>

#include "InputController.h"

namespace game {

	std::unordered_map<int, bool> InputController::keyPressed;

	InputController::InputController(void) {
		
	}


	InputController::~InputController() {
	}

	void InputController::handleInput(int key, int scancode, int action, int mods) {

		// Set keys in map
		if (action == GLFW_PRESS) {
			keyPressed[key] = true;
		}
		else if (action == GLFW_RELEASE) {
			keyPressed[key] = false;
		}
	}

	void InputController::update() {
		if (controlledHelicopter == NULL) {
			return;
		}

		if (keyPressed[GLFW_KEY_W]) {
			controlledHelicopter->moveForward();
		}
		if (keyPressed[GLFW_KEY_S]) {
			controlledHelicopter->moveBackward();
		}
		if (keyPressed[GLFW_KEY_A]) {
			controlledHelicopter->moveLeft();
		}
		if (keyPressed[GLFW_KEY_D]) {
			controlledHelicopter->moveRight();
		}
		if (keyPressed[GLFW_KEY_I]) {
			controlledHelicopter->moveUp();
		}
		if (keyPressed[GLFW_KEY_J]) {
			controlledHelicopter->moveDown();
		}
		if (keyPressed[GLFW_KEY_K]) {
			controlledHelicopter->turnLeft();
		}
		if (keyPressed[GLFW_KEY_L]) {
			controlledHelicopter->turnRight();
		}
	}

	void InputController::control(Helicopter *helicopter) {
		controlledHelicopter = helicopter;
	}


} // namespace game
