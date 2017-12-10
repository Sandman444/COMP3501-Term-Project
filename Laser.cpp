#include <stdexcept>
#include <iostream>

#include "Laser.h"

namespace game {

	Laser::Laser() : SceneNode("laser", "TorusParticles", "LaserMaterial", "Flame") {

		SetScale(glm::vec3(0.01, 50.0, 0.01));
		SetOrientation(glm::angleAxis(glm::pi<float>() / 2.0f, glm::vec3(0, 0, 1.0)));
		Rotate(glm::angleAxis(glm::pi<float>() / 2.0f, glm::vec3(0, 1.0, 0)));
		SetPosition(glm::vec3(-GetScale().y / 2, 0, 0));
	}


	Laser::~Laser() {
	}

	void Laser::on() {
		firing = true;
	}

	void Laser::off() {
		firing = false;
	}

	bool Laser::isOn() {
		return firing;
	}

	float Laser::getLength() {
		return GetScale().y;
	}

	glm::mat4 Laser::Draw(Camera *camera, glm::mat4 parent_transf) {
		if (firing) {
			return SceneNode::Draw(camera, parent_transf);
		}
		else {
			return glm::mat4(0.0);
		}
	}

} // namespace game