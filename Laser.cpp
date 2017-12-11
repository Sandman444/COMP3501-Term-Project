#include <stdexcept>
#include <iostream>

#include "Laser.h"

namespace game {

	Laser::Laser(std::string name) : SceneNode(name + "laser", "CylinderMesh", "EnemyMaterial", "") {

		SetScale(glm::vec3(0.01, 50.0, 0.01));
		SetOrientation(glm::angleAxis(glm::pi<float>() / 2.0f, glm::vec3(0, 0, 1.0)));
		Rotate(glm::angleAxis(glm::pi<float>() / 2.0f, glm::vec3(0, 1.0, 0)));
		SetPosition(glm::vec3(-GetScale().y / 2, 0, 0));

		laserEffect = new SceneNode(GetName() + "LaserEffect", "TorusParticles", "LaserMaterial", "Flame");
		laserEffect->SetBlending(true);
		laserEffect->SetPosition(glm::vec3(0, -GetScale().y / 2 + 0.4, 0));
		laserEffect->SetScale(glm::vec3(0.1, 0.1, 0.1));
		laserEffect->Rotate(glm::angleAxis(glm::pi<float>() / 2, glm::vec3(-1, 0, 0)));
		this->addChild(laserEffect);
	}


	Laser::~Laser() {
		delete laserEffect;
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