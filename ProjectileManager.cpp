#include <stdexcept>
#include <iostream>

#include "scene_graph.h"
#include "ProjectileManager.h"

namespace game {

	ProjectileManager::ProjectileManager() {
	}


	ProjectileManager::~ProjectileManager() {
	}

	void ProjectileManager::setScene(SceneGraph *sceneGraph) {
		
		scene = sceneGraph;
	}

	void ProjectileManager::update() {

		for (std::vector<Projectile*>::iterator projectile = projectiles.begin(); projectile != projectiles.end(); ++projectile) {

			bool collisionDetected = false;

			for (std::vector<SceneNode*>::iterator collideable = collideables.begin(); collideable != collideables.end(); ++collideable) {
				if (glm::distance((*projectile)->GetPosition(), (*collideable)->GetPosition()) < distanceThreshold &&
					testCollision(*projectile, (*collideable)->getBoundingSphere())) {

					collisionDetected = true;
					(*projectile)->setActive(false);
					projectile = projectiles.erase(projectile); // Remove from projectiles list
					idleProjectiles.push_back(*projectile);
					break;
				}
			}

			if (!collisionDetected) {
				(*projectile)->move();
			}
		}
	}

	bool ProjectileManager::testCollision(Projectile *projectile, glm::vec4 sphere) {
		return false;
	}

	void ProjectileManager::spawnProjectile(glm::vec3 position, glm::vec3 initialForward) {
		Projectile *newProjectile;
		if (idleProjectiles.size() == 0) {
			newProjectile = new Projectile(position, initialForward);
			scene->addNode(newProjectile);
		}
		else {
			newProjectile = idleProjectiles[idleProjectiles.size() - 1];
			idleProjectiles.pop_back();
			newProjectile->SetPosition(position);
			newProjectile->setForward(initialForward);
			newProjectile->setActive(true);
		}
		projectiles.push_back(newProjectile);
	}

	void ProjectileManager::addCollideable(SceneNode *collideable) {
		collideables.push_back(collideable);
	}

} // namespace game
