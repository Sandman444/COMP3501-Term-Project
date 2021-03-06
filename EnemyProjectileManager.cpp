#include <stdexcept>
#include <iostream>
#include <glm/gtx/intersect.hpp>

#include "scene_graph.h"
#include "EnemyProjectileManager.h"

namespace game {

	EnemyProjectileManager::EnemyProjectileManager() {
	}


	EnemyProjectileManager::~EnemyProjectileManager() {
	}

	void EnemyProjectileManager::setScene(SceneGraph *sceneGraph) {

		scene = sceneGraph;
	}

	void EnemyProjectileManager::update() {

		for (std::vector<Projectile*>::iterator projectile = projectiles.begin(); projectile != projectiles.end();) {

			bool collisionDetected = false;

			for (std::vector<SceneNode*>::iterator collideable = collideables.begin(); collideable != collideables.end(); ++collideable) {
				if (sphereCollision(*projectile, *collideable)) {
					collisionDetected = true;
					break;
				}
			}

			if ((*projectile)->isOutOfRange()) {
				collisionDetected = true;
			}

			if (!collisionDetected) {
				(*projectile)->move();
				++projectile;
			}
			else {
				(*projectile)->setActive(false);
				(*projectile)->getParent()->removeChild((*projectile)->GetName());
				projectile = projectiles.erase(projectile); // Remove from projectiles list
			}
		}
	}

	bool EnemyProjectileManager::sphereCollision(SceneNode *projectile, SceneNode *collideable) {
		return glm::distance(projectile->GetPosition(), collideable->GetPosition()) < (projectile->getBoundingSphereRadius() + collideable->getBoundingSphereRadius());
	}

	void EnemyProjectileManager::spawnMissile(glm::vec3 position, glm::vec3 initialForward, glm::quat orientation) {
		Missile *newMissile = new Missile("EnemyMaterial", position, initialForward);
		newMissile->SetOrientation(orientation);
		scene->addNode(newMissile);
		projectiles.push_back(newMissile);
	}

	void EnemyProjectileManager::spawnSplineMissile(glm::vec3 position, glm::vec3 initialForward, glm::quat orientation, glm::vec3 playerPos) {
		SplineMissile *newMissile = new SplineMissile("EnemyMaterial", position, initialForward, playerPos);
		newMissile->SetOrientation(orientation);
		scene->addNode(newMissile);
		projectiles.push_back(newMissile);
	}

	void EnemyProjectileManager::addCollideable(SceneNode *collideable) {
		collideables.push_back(collideable);
	}


} // namespace game
