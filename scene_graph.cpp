#include <stdexcept>
#include <iostream>
#include <fstream>
#include <stack>
#include <deque>
#include <unordered_set>
#define GLM_FORCE_RADIANS
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "scene_graph.h"

namespace game {

SceneGraph::SceneGraph(){

    background_color_ = glm::vec3(0.0, 0.0, 0.0);

	root_ = new SceneNode("root");
}


SceneGraph::~SceneGraph(){
	//delete root_;
}


void SceneGraph::SetBackgroundColor(glm::vec3 color){

    background_color_ = color;
}


glm::vec3 SceneGraph::GetBackgroundColor(void) const {

    return background_color_;
}

void SceneGraph::setRoot(SceneNode* root) {

	root_ = root;
}

void SceneGraph::addNode(SceneNode* newNode) {
	root_->addChild(newNode);
}


SceneNode *SceneGraph::GetNode(std::string node_name) const {

    // Find node with the specified name
    std::stack<SceneNode *> stck;
    stck.push(root_);
    while (stck.size() > 0){
        SceneNode *current = stck.top();
        stck.pop();
        if (current->GetName() == node_name){
            return current;
        }
        for (std::vector<SceneNode *>::const_iterator it = current->children_begin();
             it != current->children_end(); it++){
            stck.push(*it);
        }
    }
    return NULL;
}


void SceneGraph::Draw(Camera *camera){

    // Clear background
    glClearColor(background_color_[0], 
                 background_color_[1],
                 background_color_[2], 0.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	std::unordered_set<std::string> names;

    // Draw all scene nodes
    // Initialize stack of nodes
    std::deque<SceneNode *> stck;
    stck.push_back(root_);
    // Initialize stack of transformations
    std::deque<glm::mat4> transf;
    transf.push_back(glm::mat4(1.0));
    // Traverse hierarchy
    while (stck.size() > 0){
        // Get next node to be processed and pop it from the stack
        SceneNode *current = stck.back();
        stck.pop_back();
        // Get transformation corresponding to the parent of the next node
        glm::mat4 parent_transf = transf.back();
        transf.pop_back();

		std::unordered_set<std::string>::const_iterator nodeName = names.find(current->GetName());

		if (current->GetBlending() && nodeName == names.end()) {
			stck.push_front(current);
			transf.push_front(parent_transf);
			names.insert(current->GetName());
		}
		else {
			// Draw node based on parent transformation
			glm::mat4 current_transf = current->Draw(camera, parent_transf);
			// Push children of the node to the stack, along with the node's
			// transformation
			for (std::vector<SceneNode *>::const_iterator it = current->children_begin();
				it != current->children_end(); it++) {
				stck.push_back(*it);
				transf.push_back(current_transf);
			}
		}
    }
}


void SceneGraph::update(void){

    // Traverse hierarchy to update all nodes
    std::stack<SceneNode *> stck;
    stck.push(root_);
    while (stck.size() > 0){
        SceneNode *current = stck.top();
        stck.pop();
        current->Update();
        for (std::vector<SceneNode *>::const_iterator it = current->children_begin();
             it != current->children_end(); it++){
            stck.push(*it);
        }
    }
}

} // namespace game
