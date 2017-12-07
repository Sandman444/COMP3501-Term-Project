#ifndef LASER_H
#define LASER_H

#include "scene_node.h"

namespace game {

	class Laser : public SceneNode {

	public:
		// Constructor
		Laser();

		// Destructor
		~Laser();

		void on();
		void off();

		bool isOn();
		float getLength();

		glm::mat4 Draw(Camera *camera, glm::mat4 parent_transf) override;

	private:

		bool firing;
	};

} // namespace game

#endif
