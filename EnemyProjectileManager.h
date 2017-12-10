#ifndef ENEMYPROJECTILEMANAGER_H
#define ENEMYPROJECTILEMANAGER_H

#include <vector>

#include "Updateable.h"
#include "Projectile.h"
#include "Missile.h"

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
		void spawnMissile(glm::vec3 position, glm::vec3 initialForward, glm::quat orientation);
		void addCollideable(SceneNode *collideable);

	private:

		SceneGraph *scene;

		std::vector<SceneNode*> collideables;
		std::vector<Projectile*> projectiles;

		float distanceThreshold = 0.6f;
	};

} // namespace game

#endif