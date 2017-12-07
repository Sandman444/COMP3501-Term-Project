#ifndef TANK_H 
#define TANK_H

#include "DirectionalSceneNode.h"

namespace game {

	class Tank : public DirectionalSceneNode {

	public:
		// Constructor
		Tank(ResourceManager* resman);

		// Destructor
		~Tank();

		void Update(SceneNode* player);

		/*void moveLeft();
		void moveRight();
		void moveForward();
		void moveBackward();*/
		void turnLeft();
		void turnRight();

	private:
		SceneNode *tank_body, *gun_turret, *gun_barrel, *tread1, *tread2;

		glm::vec3 velocity;
		glm::vec3 accelerationDirection;
		float accelerationSpeed;

		float turnVelocity = 0;
		int turnDirection = 0;
		float turnSpeed;
	};

} // namespace game

#endif