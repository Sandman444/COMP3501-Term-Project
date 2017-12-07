#ifndef TURRET_H 
#define TURRET_H

#include "DirectionalSceneNode.h"

namespace game {

	class Turret : public DirectionalSceneNode {

	public:
		// Constructor
		Turret(ResourceManager* resman);

		// Destructor
		~Turret();

		void Update(SceneNode* player);

		void turnLeft();
		void turnRight();
		void follow(DirectionalSceneNode* player);

	private:
		SceneNode *body, *gun_housing, *barrel;

		glm::vec3 velocity;
		glm::vec3 accelerationDirection;
		float accelerationSpeed;

		float turnVelocity = 0;
		int turnDirection = 0;
		float turnSpeed;
	};

} // namespace game

#endif