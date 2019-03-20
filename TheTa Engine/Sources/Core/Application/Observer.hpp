#pragma once

#include <GLM/gtc/matrix_transform.hpp>

#include "Projection.hpp"

#include <iostream>

constexpr float speed = 10.0f;
constexpr float sensitivity_axis =0.25f;


/*** Ready ***/
class Observer
{
public:
	enum class Translations{ FORWARD, UP, RIGHT };
	enum class Movement{ FORWARD, BACKWARD, LEFT, RIGHT, UPWORD, DOWNWORD };
	enum class ProjectionType{ PERSPECTIVE, ORTHOGRAPHIC };
	enum class Type{FIRST_PERSON, THIRD_PERSON};

	Observer(
		glm::vec3 position = glm::vec3(0, 0, 0),
		glm::vec3 OX = glm::vec3(1, 0, 0),
		glm::vec3 OY = glm::vec3(0, 1, 0),
		glm::vec3 OZ = glm::vec3(0, 0, 1),
		float yaw = -90.0f, 
		float pitch = 0.0f,
		float roll = 0.0f)
	{
		movementspeed = speed;
		sensitivity = glm::vec2(sensitivity_axis, sensitivity_axis);
		
		distancetotarget = 0;
		type = Type::FIRST_PERSON;

		world_forward = glm::normalize(-OZ);
		world_right = glm::normalize(OX);
		world_up = glm::normalize(OY);

		this->yaw = yaw;
		this->pitch = pitch;
		this->roll = roll;

		this->position = position;

		projection_info.perspective = new Perspective();
		set_projection(projection_info, ProjectionType::PERSPECTIVE);

		update();
	};
	glm::vec3 get_eye_position() const 
		{ return position; };

	glm::vec3 get_forward(bool world_axis = false) const 
		{ return (world_axis) ? world_forward : forward; };

	glm::vec3 get_up(bool world_axis = false) const 
		{ return (world_axis) ? world_up : up; };

	glm::vec3 get_right(bool world_axis = false) const 
		{ return (world_axis) ? world_right : right; };

	glm::vec3 get_target(bool world_axis = false) const
		{ return position + forward * distancetotarget; };

	glm::mat4 get_view() const 
		{ return glm::lookAt(position, position + forward, up); };

	glm::mat4 get_projection() const 
		{ return projection; };

	void translate(const float distance, const Translations type, bool world_axis = false);

	void set(const glm::vec3 position, const glm::vec3 target, const glm::vec3 up);
	void set_projection(Projection projection, ProjectionType type);

	void move(Movement movement, float delta);
	void look(const glm::ivec2 delta);

private:
	void update();

	// eye position
	glm::vec3 position;

	// observer axis
	glm::vec3 forward;
	glm::vec3 up;
	glm::vec3 right;

	// world axis
	glm::vec3 world_forward;
	glm::vec3 world_up;
	glm::vec3 world_right;

	// movement speed
	float movementspeed;

	// euler angles
	float pitch, yaw, roll;

	// rotation sensitivity
	glm::vec2 sensitivity;

	//projection matrix
	Projection projection_info;
	glm::mat4 projection;

	float distancetotarget;
	Type type;
};