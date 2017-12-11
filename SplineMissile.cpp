#include <stdexcept>
#include <iostream>
#include <glm\gtx\vector_angle.hpp>

#include "SplineMissile.h"

namespace game {

	SplineMissile::SplineMissile(std::string material, glm::vec3 position, glm::vec3 initialForward, glm::vec3 targetPosition) : Missile(material, position, initialForward) {
		projectileModel = new SceneNode(GetName() + "Model", "CubeMesh", material, "");
		projectileModel->SetScale(glm::vec3(0.3, 0.1, 0.1));
		this->addChild(projectileModel);

		target = targetPosition;
		timer = 0; //set up timer
		startTime = clock();
		timerStarted = true;

		//add the missile's control points
		p0 = GetPosition();
		p1 = GetPosition() + getForward() * 3.0f;
		p2 = GetPosition() + getForward() * 5.0f;
		p3 = targetPosition;
	}


	SplineMissile::~SplineMissile() {
	}

	void SplineMissile::move() {
		//spline calculation
		timer += 0.01;
		float t = timer;
		if (t < 1) {
			if (timerStarted == false) timerStarted = true;
			float c0 = pow((1 - t), 3);
			float c1 = pow((1 - t), 2) * 3 * t;
			float c2 = pow(t, 2) * 3 * (1 - t);
			float c3 = pow(t, 3);

			//change position with spline
			glm::vec3 splineInterp = glm::vec3(p0*c0 + p1*c1 + p2*c2 + p3*c3);
			glm::vec3 direction = glm::normalize(splineInterp - GetPosition());
			Translate(direction * 0.05f);
			Rotate(glm::angleAxis(glm::angle(getForward(), direction) * 0.01f, glm::cross(getForward(), direction)));
		}
		else {
			Translate(getForward() * 0.05f);
		}

	}
} // namespace game