#include <stdexcept>
#include <iostream>

#include "Missile.h"

namespace game {

	Missile::Missile(glm::vec3 position, glm::vec3 forward) : Projectile(position, forward) {
		projectileModel = new SceneNode(GetName() + "Model", "CubeMesh", "ObjectMaterial");
		projectileModel->SetScale(glm::vec3(0.3, 0.1, 0.1));
		this->addChild(projectileModel);
		
		//add the thrusters to the missile
		//NOTE: needs texturing support
		//NOTE: needs actual thruster effect
		projectileEffect = new SceneNode(GetName() + "Effect", "TorusParticles", "LaserMaterial");
		projectileEffect->SetPosition(this->GetPosition());
		projectileModel->addChild(projectileEffect);

		timer = 0; //set up timer
		startTime = clock();
		timerStarted = true;

		//add the missile's control points
		//controlPoints = ResourceManager::theResourceManager().GetResource("ControlPoints")->GetData();
		p0 = this->GetPosition();
		p1 = p0 + glm::vec3(-2.0, 2.0, -2.0);
		p2 = p0 + glm::vec3(-2.0, 0.0, -3.0);
		p3 = p0 + glm::vec3(-10.0, 0.0, 0.0);
	}

	Missile::~Missile() {  }

	void Missile::move(){
		//spline calculation
		timer = (clock() - startTime)/ (float)CLOCKS_PER_SEC;
		float t = fmod(timer, TIMER_INTERVAL) / TIMER_INTERVAL; //second timer cycle
		if (timerStarted == false) timerStarted = true; 
		float c0 = pow((1 - t), 3);
		float c1 = pow((1 - t), 2) * 3 * t;
		float c2 = pow(t, 2) * 3 * (1 - t);
		float c3 = pow(t, 3);
		
		//change position with spline
		this->SetPosition(p0*c0 + p1*c1 + p2*c2 + p3*c3);

		//set positions for next spline
		if (t > 0.999) {
			std::cout << "change position" << std::endl;
			p0 = p3;
			p1 = p3 + glm::vec3(0.5, 0.5, 0.5);
			p2 = p3 + glm::vec3(1.0, 1.0, 1.0);
			p3 = this->GetPosition();
			timer = 0;
		}
	}
} // namespace game