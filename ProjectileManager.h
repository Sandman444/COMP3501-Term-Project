#ifndef PROJECTILEMANAGER_H
#define PROJECTILEMANAGER_H

#include <vector>

#include "Updateable.h"
#include "Projectile.h"

namespace game {

	class SceneGraph;

	class ProjectileManager : public Updateable {

	public:
		// Constructor
		ProjectileManager();

		// Destructor
		~ProjectileManager();

		void update();
		void setScene(SceneGraph *sceneGraph);
		bool sphereCollision(SceneNode *projectile, SceneNode *collideable);
		void spawnProjectile(glm::vec3 position, glm::vec3 initialForward, glm::quat orientation);
		void addCollideable(SceneNode *collideable);

	private:

		SceneGraph *scene;

		std::vector<SceneNode*> collideables;
		std::vector<Projectile*> projectiles;
		std::vector<Projectile*> idleProjectiles;

		float distanceThreshold = 0.6f;
	};

} // namespace game

#endif