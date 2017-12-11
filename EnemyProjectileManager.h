#ifndef ENEMYPROJECTILEMANAGER_H
#define ENEMYPROJECTILEMANAGER_H

#include <vector>

#include "Updateable.h"
#include "Projectile.h"
#include "Missile.h"
#include "SplineMissile.h"

namespace game {

	class SceneGraph;

	class EnemyProjectileManager : public Updateable {

	public:
		// Constructor
		EnemyProjectileManager();

		// Destructor
		~EnemyProjectileManager();

		void update();
		void setScene(SceneGraph *sceneGraph);
		bool sphereCollision(SceneNode *projectile, SceneNode *collideable);
		void addCollideable(SceneNode *collideable);
		void spawnMissile(glm::vec3 position, glm::vec3 initialForward, glm::quat orientation);
		void spawnSplineMissile(glm::vec3 position, glm::vec3 initialForward, glm::quat orientation, glm::vec3 playerPos);

	private:

		SceneGraph *scene;

		std::vector<SceneNode*> collideables;
		std::vector<Projectile*> projectiles;

		float distanceThreshold = 0.6f;
	};

} // namespace game

#endif