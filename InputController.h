#ifndef INPUTCONTROLLER_H
#define INPUTCONTROLLER_H

#include <unordered_map>
#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Updateable.h"
#include "Helicopter.h"

namespace game {

	class InputController : public Updateable {

	public:
		// Constructor
		InputController(void);

		// Destructor
		~InputController();

		static void handleInput(int key, int scancode, int action, int mods);
		void update();
		void control(Helicopter*);

	private:

		static std::unordered_map<int, bool> keyPressed;
		Helicopter* controlledHelicopter = NULL;
	};

} // namespace game

#endif