#version 400

// Vertex buffer
in vec3 vertex;
in vec3 normal;
in vec3 color;

// Uniform (global) buffer
uniform mat4 world_mat;
uniform mat4 view_mat;
uniform mat4 normal_mat;
uniform float timer;
uniform float cycletime;

// Attributes forwarded to the geometry shader
out vec3 vertex_color;
out float timestep;

// Simulation parameters (constants)
uniform vec3 up_vec = vec3(0.0, 1.0, 0.0);
uniform vec3 object_color = vec3(227 / 255.0, 140 / 255.0, 45 / 255.0);
float grav = 0.1; // Gravity
float speed = 1.0; // Allows to control the speed of the explosion


void main()
{
    // Let time cycle every four seconds
    float circtime = timer - 4.0 * floor(timer / 4);
    float t = circtime; // Our time parameter
    
    // Let's first work in model space (apply only world matrix)
    vec4 position = world_mat * vec4(vertex, 1.0);
    vec4 norm = normal_mat * vec4(normal, 1.0);

	//x(t) = x(0) + v*t + 0.5*g*t*t
	position.x += norm.x*t*speed - grav*up_vec.x*t*t;
	position.y += norm.y*t*speed - grav*up_vec.y*t*t;
	position.z += norm.z*t*speed - grav*up_vec.z*t*t;
    
    // Now apply view transformation
    gl_Position = view_mat * position;
        
    // Define outputs
    // Define color of vertex
    //vertex_color = color.rgb; // Color defined during the construction of the particles
    vertex_color = object_color; // Uniform color 
    //vertex_color = vec3(t, 0.0, 1-t);
    //vertex_color = vec3(1.0, 1-t, 0.0);

    // Forward time step to geometry shader
    timestep = t;
}
