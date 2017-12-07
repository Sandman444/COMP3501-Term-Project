#include <stdexcept>
#define GLM_FORCE_RADIANS
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <iostream>
#include <time.h>


#include "camera.h"
#include "scene_node.h"

namespace game {

SceneNode::SceneNode(const std::string name) {

	// Set name of scene node
	name_ = name;

	// Other attributes
	scale_ = glm::vec3(1.0, 1.0, 1.0);

	// Hierarchy
	parent_ = NULL;
}

SceneNode::SceneNode(const std::string name, std::string object_name, std::string material_name){

	// Get resources
	Resource *geom;
	if (object_name != std::string("")) {
		geom = ResourceManager::theResourceManager().GetResource(object_name);
		if (!geom) {
			throw(GameException(std::string("Could not find resource \"") + object_name + std::string("\"")));
		}
	}
	else {
		geom = NULL;
	}

	Resource *mat;
	if (material_name != std::string("")) {
		mat = ResourceManager::theResourceManager().GetResource(material_name);
		if (!mat) {
			throw(GameException(std::string("Could not find resource \"") + material_name + std::string("\"")));
		}
	}
	else {
		mat = NULL;
	}

    // Set name of scene node
    name_ = name;

    if (geom){
        // Set geometry
        if (geom->GetType() == PointSet){
            mode_ = GL_POINTS;
        } else if (geom->GetType() == Mesh){
            mode_ = GL_TRIANGLES;
        } else {
            throw(std::invalid_argument(std::string("Invalid type of geometry")));
        }

        array_buffer_ = geom->GetArrayBuffer();
        element_array_buffer_ = geom->GetElementArrayBuffer();
        size_ = geom->GetSize();
    } else {
        array_buffer_ = 0;
    }

    // Set material (shader program)
    if (mat){
        if (mat->GetType() != Material){
            throw(std::invalid_argument(std::string("Invalid type of material")));
        }

        material_ = mat->GetResource();
    } else {
        material_ = 0;
    }

    // Other attributes
    scale_ = glm::vec3(1.0, 1.0, 1.0);

    // Hierarchy
    parent_ = NULL;
}


SceneNode::~SceneNode(){
	for (std::vector<SceneNode*>::iterator i = children_.begin(); i != children_.end(); ++i) {
		delete *i;
	}
}

float SceneNode::getBoundingSphereRadius(void) const {
	return GetScale().x > GetScale().y ? std::max(GetScale().x, GetScale().z) : std::max(GetScale().y, GetScale().z);
}


const std::string SceneNode::GetName(void) const {

    return name_;
}


glm::vec3 SceneNode::GetPosition(void) const {

    return position_;
}


glm::quat SceneNode::GetOrientation(void) const {

    return orientation_;
}


glm::vec3 SceneNode::GetScale(void) const {

    return scale_;
}


void SceneNode::SetPosition(glm::vec3 position){

    position_ = position;
}


void SceneNode::SetOrientation(glm::quat orientation){

    orientation_ = glm::normalize(orientation);
}


void SceneNode::SetScale(glm::vec3 scale){

    scale_ = scale;
}


void SceneNode::Translate(glm::vec3 trans){

    position_ += trans;
}


void SceneNode::Rotate(glm::quat rot){

    orientation_ *= glm::normalize(rot);
}


void SceneNode::Scale(glm::vec3 scale){

    scale_ *= scale;
}


GLenum SceneNode::GetMode(void) const {

    return mode_;
}


GLuint SceneNode::GetArrayBuffer(void) const {

    return array_buffer_;
}


GLuint SceneNode::GetElementArrayBuffer(void) const {

    return element_array_buffer_;
}


GLsizei SceneNode::GetSize(void) const {

    return size_;
}


GLuint SceneNode::GetMaterial(void) const {

    return material_;
}


glm::mat4 SceneNode::Draw(Camera *camera, glm::mat4 parent_transf){

    if ((array_buffer_ > 0) && (material_ > 0)){
        // Select proper material (shader program)
        glUseProgram(material_);

        // Set geometry to draw
        glBindBuffer(GL_ARRAY_BUFFER, array_buffer_);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, element_array_buffer_);

        // Set globals for camera
        camera->SetupShader(material_);

        // Set world matrix and other shader input variables
        glm::mat4 transf = SetupShader(material_, parent_transf);

        // Draw geometry
        if (mode_ == GL_POINTS){
            glDrawArrays(mode_, 0, size_);
        } else {
            glDrawElements(mode_, size_, GL_UNSIGNED_INT, 0);
        }

        return transf;
    } else {
        glm::mat4 rotation = glm::mat4_cast(orientation_);
        glm::mat4 translation = glm::translate(glm::mat4(1.0), position_);
        glm::mat4 transf = parent_transf * translation * rotation;
        return transf;
    }
}


void SceneNode::Update(void){

    // Do nothing for this generic type of scene node
}


glm::mat4 SceneNode::SetupShader(GLuint program, glm::mat4 parent_transf){

    // Set attributes for shaders
    GLint vertex_att = glGetAttribLocation(program, "vertex");
    glVertexAttribPointer(vertex_att, 3, GL_FLOAT, GL_FALSE, 11*sizeof(GLfloat), 0);
    glEnableVertexAttribArray(vertex_att);

    GLint normal_att = glGetAttribLocation(program, "normal");
    glVertexAttribPointer(normal_att, 3, GL_FLOAT, GL_FALSE, 11*sizeof(GLfloat), (void *) (3*sizeof(GLfloat)));
    glEnableVertexAttribArray(normal_att);

    GLint color_att = glGetAttribLocation(program, "color");
    glVertexAttribPointer(color_att, 3, GL_FLOAT, GL_FALSE, 11*sizeof(GLfloat), (void *) (6*sizeof(GLfloat)));
    glEnableVertexAttribArray(color_att);

    GLint tex_att = glGetAttribLocation(program, "uv");
    glVertexAttribPointer(tex_att, 2, GL_FLOAT, GL_FALSE, 11*sizeof(GLfloat), (void *) (9*sizeof(GLfloat)));
    glEnableVertexAttribArray(tex_att);

    // World transformation
    glm::mat4 scaling = glm::scale(glm::mat4(1.0), scale_);
    glm::mat4 rotation = glm::mat4_cast(orientation_);
    glm::mat4 translation = glm::translate(glm::mat4(1.0), position_);
    glm::mat4 transf = parent_transf * translation * rotation;
    glm::mat4 local_transf = transf * scaling;

    GLint world_mat = glGetUniformLocation(program, "world_mat");
    glUniformMatrix4fv(world_mat, 1, GL_FALSE, glm::value_ptr(local_transf));

    // Timer
    GLint timer_var = glGetUniformLocation(program, "timer");
    double current_time = glfwGetTime();
    glUniform1f(timer_var, (float) current_time);

    // Return transformation of node combined with parent, without scaling
    return transf;
}


void SceneNode::addChild(SceneNode *node){

    children_.push_back(node);
    node->parent_ = this;
}

void SceneNode::removeChild(std::string nodeName) {
	for (std::vector<SceneNode*>::iterator i = children_.begin(); i != children_.end(); ++i) {
		if ((*i)->GetName() == nodeName) {
			delete *i;
			children_.erase(i);
			return;
		}
	}
}


std::vector<SceneNode *>::const_iterator SceneNode::children_begin() const {

    return children_.begin();
}


std::vector<SceneNode *>::const_iterator SceneNode::children_end() const {

    return children_.end();
}

} // namespace game;
