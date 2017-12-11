cmake_minimum_required(VERSION 2.6)

# Name of project
project(SceneGraphDemo)

# Specify project files: header files and source files
set(HDRS
    camera.h game.h resource.h resource_manager.h scene_graph.h scene_node.h InputController.h Updateable.h Helicopter.h GameException.h DirectionalSceneNode.h Projectile.h PlayerProjectileManager.h EnemyProjectileManager.h Tank.h Turret.h Bomb.h Missile.h Laser.h Ground.h EnemyManager.h EnemyHelicopter.h shader_attribute.h
 SplineMissile.h)
 
set(SRCS
    camera.cpp game.cpp main.cpp resource.cpp resource_manager.cpp scene_graph.cpp scene_node.cpp InputController.cpp Helicopter.cpp DirectionalSceneNode.cpp Projectile.cpp PlayerProjectileManager.cpp EnemyProjectileManager.cpp Tank.cpp Turret.cpp Bomb.cpp Missile.cpp Laser.cpp Ground.cpp EnemyManager.cpp EnemyHelicopter.cpp shader_attribute.cpp SplineMissile.cpp material_vp.glsl material_fp.glsl enemy_fp.glsl enemy_vp.glsl laser_fp.glsl laser_gp.glsl laser_vp.glsl ground_material_fp.glsl ground_material_vp.glsl player_fp.glsl player_vp.glsl fire_fp.glsl fire_vp.glsl fire_gp.glsl sparkle_vp.glsl sparkle_fp.glsl sparkle_gp.glsl
)

# Add path name to configuration file
configure_file(path_config.h.in path_config.h)

# Add executable based on the source files
add_executable(SceneGraphDemo ${HDRS} ${SRCS})

# Require OpenGL library
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIR})
target_link_libraries(SceneGraphDemo ${OPENGL_gl_LIBRARY})

# Other libraries needed
set(LIBRARY_PATH "" CACHE PATH "Folder with GLEW, GLFW, GLM, and SOIL libraries")
include_directories(${LIBRARY_PATH}/include)
if(NOT WIN32)
    find_library(GLEW_LIBRARY GLEW)
    find_library(GLFW_LIBRARY glfw)
    find_library(SOIL_LIBRARY SOIL)
elseif(WIN32)
    find_library(GLEW_LIBRARY glew32s HINTS ${LIBRARY_PATH}/lib)
    find_library(GLFW_LIBRARY glfw3 HINTS ${LIBRARY_PATH}/lib)
    find_library(SOIL_LIBRARY SOIL HINTS ${LIBRARY_PATH}/lib)
endif(NOT WIN32)
target_link_libraries(SceneGraphDemo ${GLEW_LIBRARY})
target_link_libraries(SceneGraphDemo ${GLFW_LIBRARY})
target_link_libraries(SceneGraphDemo ${SOIL_LIBRARY})

# The rules here are specific to Windows Systems
if(WIN32)
    # Avoid ZERO_CHECK target in Visual Studio
    set(CMAKE_SUPPRESS_REGENERATION TRUE)
 
    # This will use the proper libraries in debug mode in Visual Studio
    set_target_properties(SceneGraphDemo PROPERTIES DEBUG_POSTFIX _d)
endif(WIN32)
