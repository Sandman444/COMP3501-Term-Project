#include <stdexcept>
#include <iostream>

#include "scene_graph.h"
#include "EnemyManager.h"

namespace game {

	EnemyManager::EnemyManager(void) {

	}


	EnemyManager::~EnemyManager() {

	}

	void EnemyManager::setScene(SceneGraph *sceneGraph) {
		scene = sceneGraph;
	}

	void EnemyManager::setPlayerManager(PlayerProjectileManager *manager) {
		playerManager = manager;
	}

	void EnemyManager::setPlayer(SceneNode *thePlayer) {
		player = thePlayer;
		enemyProjectileManager.addCollideable(player);
	}

	void EnemyManager::update() {
		enemyProjectileManager.update();
		for (std::vector<SceneNode*>::iterator enemy = enemies.begin(); enemy != enemies.end(); ++enemy) {
			(*enemy)->Update(player->GetPosition());
		}
	}

	void EnemyManager::spawnTank(glm::vec3 position) {
		Tank *newTank = new Tank(&enemyProjectileManager);
		newTank->SetPosition(position);
		scene->addNode(newTank);
		enemies.push_back(newTank);
		playerManager->addCollideable(newTank);
	}

	void EnemyManager::spawnTurret(glm::vec3 position) {
		Turret *newTurret = new Turret(&enemyProjectileManager);
		newTurret->SetPosition(position);
		scene->addNode(newTurret);
		enemies.push_back(newTurret);
		playerManager->addCollideable(newTurret);
	}

	void EnemyManager::spawnHeli(glm::vec3 position) {
		//Helicopter *newHelicopter = new Helicopter();
	}

} // namespace game