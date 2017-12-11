#ifndef ENEMYMANAGER_H
#define ENEMYMANAGER_H

#include <vector>

#include "Updateable.h"
#include "EnemyProjectileManager.h"
#include "PlayerProjectileManager.h"
#include "Tank.h"
#include "Turret.h"

namespace game {

	class SceneGraph;

	class EnemyManager : public Updateable {

	public:
		// Constructor
		EnemyManager(void);

		// Destructor
		~EnemyManager();

		void update();
		void setScene(SceneGraph *sceneGraph);
		void setPlayerManager(PlayerProjectileManager *manager);
		void setPlayer(SceneNode *thePlayer);

		void spawnTank(glm::vec2 position);
		void spawnTurret(glm::vec2 position);
		void spawnHeli(glm::vec3 position);

		void destroy(SceneNode *enemy);
		
	private:

		SceneGraph *scene;
		PlayerProjectileManager *playerManager;
		SceneNode *player;
		std::vector<SceneNode*> enemies;
		EnemyProjectileManager enemyProjectileManager;
	};

} // namespace game

#endif
