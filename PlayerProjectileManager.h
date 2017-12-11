#ifndef PLAYERPROJECTILEMANAGER_H
#define PLAYERPROJECTILEMANAGER_H

#include <vector>

#include "Updateable.h"
#include "Projectile.h"
#include "Missile.h"
#include "Bomb.h"

namespace game {

	class SceneGraph;
	class EnemyManager;

	class PlayerProjectileManager : public Updateable {

	public:
		// Constructor
		PlayerProjectileManager();

		// Destructor
		~PlayerProjectileManager();

		void update();
		void setScene(SceneGraph *sceneGraph);
		void setEnemyManager(EnemyManager *manager);
		bool sphereCollision(SceneNode *projectile, SceneNode *collideable);
		void spawnMissile(glm::vec3 position, glm::vec3 initialForward, glm::quat orientation);
		void spawnBomb(glm::vec3 position);
		void addCollideable(SceneNode *collideable);

		void setLaserStart(glm::vec3 point);
		void setLaserEnd(glm::vec3 point);
		void setLaserOn(bool on);

	private:

		SceneGraph *scene;
		EnemyManager *enemyManager;

		std::vector<SceneNode*> collideables;
		std::vector<Projectile*> projectiles;

		float distanceThreshold = 0.6f;

		glm::vec3 laserStart;
		glm::vec3 laserEnd;
		bool laserOn;
	};

} // namespace game

#endif