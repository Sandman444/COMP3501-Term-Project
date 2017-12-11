#include <stdexcept>
#include <iostream>

#include "SplineMissile.h"

namespace game {

	SplineMissile::SplineMissile(std::string material, glm::vec3 position, glm::vec3 forward, glm::vec3 target) : Missile(material, position, forward) {
		projectileModel = new SceneNode(GetName() + "Model", "CubeMesh", material, "");
		projectileModel->SetScale(glm::vec3(0.3, 0.1, 0.1));
		this->addChild(projectileModel);

		target_ = target;
		timer = 0; //set up timer
		startTime = clock();
		timerStarted = true;

		//add the missile's control points
		//controlPoints = ResourceManager::theResourceManager().GetResource("ControlPoints")->GetData();
		p0 = this->GetPosition();
		int n1 = rand() % 6 - 3;
		int n2 = rand() % 6 - 3;
		int n3 = rand() % 6 - 3;
		int n4 = rand() % 6 - 3;
		p1 = p0 + glm::vec3(n1, 2, n2);
		p2 = p0 + glm::vec3(n3, 2, n4);
		p3 = p0 + glm::vec3(-10.0, 0.0, 0.0);
	}


	SplineMissile::~SplineMissile() {
	}

	void SplineMissile::move() {
		//spline calculation
		timer = (clock() - startTime) / (float)CLOCKS_PER_SEC;
		float t = fmod(timer, TIMER_INTERVAL) / TIMER_INTERVAL; //second timer cycle
		if (timerStarted == false) timerStarted = true;
		float c0 = pow((1 - t), 3);
		float c1 = pow((1 - t), 2) * 3 * t;
		float c2 = pow(t, 2) * 3 * (1 - t);
		float c3 = pow(t, 3);

		//change position with spline
		this->SetPosition(p0*c0 + p1*c1 + p2*c2 + p3*c3);
	}
} // namespace game