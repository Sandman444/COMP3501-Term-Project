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

		for (std::vector<Projectile*>::iterator projectile = projectiles.begin(); projectile != projectiles.end();) {

			bool collisionDetected = false;

			for (std::vector<SceneNode*>::iterator collideable = collideables.begin(); collideable != collideables.end(); ++collideable) {
				if (sphereCollision(*projectile, *collideable)) {
					collisionDetected = true;
					//(*collideable)->setActive(false);
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
				idleProjectiles.push_back(*projectile);
				projectile = projectiles.erase(projectile); // Remove from projectiles list
			}
		}
	}

	bool ProjectileManager::sphereCollision(SceneNode *projectile, SceneNode *collideable) {
		return glm::distance(projectile->GetPosition(), collideable->GetPosition()) < (projectile->getBoundingSphereRadius() + collideable->getBoundingSphereRadius());
	}

	void ProjectileManager::spawnProjectile(glm::vec3 position, glm::vec3 initialForward, glm::quat orientation) {
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
		newProjectile->SetOrientation(orientation);
		projectiles.push_back(newProjectile);
	}

	void ProjectileManager::addCollideable(SceneNode *collideable) {
		collideables.push_back(collideable);
	}

} // namespace game
