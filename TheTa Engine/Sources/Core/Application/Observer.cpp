#include "Observer.hpp"

void Observer::translate(const float distance, const Translations type, bool world_axis)
{
	switch (type)
	{
	case Translations::FORWARD:
		position += forward * distance;
		break;
	case Translations::UP:
		position += ((world_axis) ? world_up : up) * distance;
		break;
	case Translations::RIGHT:
		position += right * distance;
		break;
	default:
		break;
	}
}

void Observer::set(const glm::vec3 position, const glm::vec3 target, const glm::vec3 up)
{
	this->position = position;
	forward = glm::normalize(target - position);
	right = glm::cross(forward, up);
	this->up = glm::cross(right, forward);

	distancetotarget = glm::length(target - position);
}

void Observer::set_projection(Projection projection, ProjectionType type)
{
	projection_info = projection;
	switch (type)
	{
	case ProjectionType::PERSPECTIVE:
		this->projection = glm::perspective(
			glm::radians(projection.perspective->fov),
			projection.perspective->aratio,
			projection.perspective->znear,
			projection.perspective->zfar
		);
		break;
	case ProjectionType::ORTHOGRAPHIC:
		this->projection = glm::ortho(
			projection.ortho->left,
			projection.ortho->right,
			projection.ortho->bottom,
			projection.ortho->top
		);
		break;
	default:
		break;
	}
}

void Observer::move(Movement movement, float delta)
{
	switch (movement)
	{
	case Movement::FORWARD:
		position += delta * movementspeed * forward;
		break;
	case Movement::RIGHT:
		position += delta * movementspeed * right;
		break;
	case Movement::LEFT:
		position -= delta * movementspeed * right;
		break;
	case Movement::BACKWARD:
		position -= delta * movementspeed * forward;
		break;
	case Movement::UPWORD:
		position += delta * movementspeed * world_up;
		break;
	case Movement::DOWNWORD:
		position -= delta * movementspeed * world_up;
		break;
	default:
		break;
	}
}

void Observer::look(const glm::ivec2 delta)
{
	if (type == Type::THIRD_PERSON)
		translate(distancetotarget, Translations::FORWARD);
	
	yaw += delta.x * sensitivity.x;
	pitch += delta.y * sensitivity.y;
	update();

	if (type == Type::THIRD_PERSON)
		translate(-distancetotarget, Translations::FORWARD);
}

void Observer::update()
{
	forward = glm::normalize(
		glm::vec3(
			cos(glm::radians(yaw)) * cos(glm::radians(pitch)),
			sin(glm::radians(pitch)),
			sin(glm::radians(yaw)) * cos(glm::radians(pitch))
		)
	);

	right = glm::normalize(glm::cross(this->forward, this->world_up));
	up = glm::normalize(glm::cross(this->right, this->forward));
}
