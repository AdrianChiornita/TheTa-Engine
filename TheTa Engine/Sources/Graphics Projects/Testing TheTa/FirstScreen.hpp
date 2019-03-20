#pragma once

#include <iostream>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <string>
#include <map>

#include <Core/Application/Screen.hpp>
#include <Core/Application/Observer.hpp>
#include "CityCamera.h"

#include <Core/GPU/Model.hpp>
#include <Core/Managers/ResourceManager.hpp>

#include <unordered_map>

class MyScreen : public Screen
{
public:
	std::unordered_map<std::string, Shader*> shaders;
	std::unordered_map<std::string, Model*> models;
	std::unordered_map<std::string, Mesh*> meshes;
	CityCamera::Camera* camera;

	MyScreen() 
	{
		camera = new CityCamera::Camera();

		{
			Shader *shader = new Shader("Simple");
			shader->add(rsc::shaders + "Simple.vs.glsl", GL_VERTEX_SHADER);
			shader->add(rsc::shaders + "Simple.fs.glsl", GL_FRAGMENT_SHADER);
			shader->setup();
			shaders[shader->get_name()] = shader;
		}

		{
			Shader *shader = new Shader("UniformColor");
			shader->add(rsc::shaders + "MVP.vs.glsl", GL_VERTEX_SHADER);
			shader->add(rsc::shaders + "UniformColor.fs.glsl", GL_FRAGMENT_SHADER);
			shader->setup();
			shaders[shader->get_name()] = shader;
		}

		{
			Shader *shader = new Shader("VertexNormal");
			shader->add(rsc::shaders + "MVP.vs.glsl", GL_VERTEX_SHADER);
			shader->add(rsc::shaders + "VertexNormal.fs.glsl", GL_FRAGMENT_SHADER);
			shader->setup();
			shaders[shader->get_name()] = shader;
		}

		{
			Shader *shader = new Shader("Texture");
			shader->add(rsc::shaders + "Texture.vs.glsl", GL_VERTEX_SHADER);
			shader->add(rsc::shaders + "Texture.fs.glsl", GL_FRAGMENT_SHADER);
			shader->setup();
			shaders[shader->get_name()] = shader;
		}

		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}

	unsigned int nextindex() const override { return NO_SCREEN; };
	unsigned int previndex() const override { return NO_SCREEN; };

	GLuint tex;
	void build() override 
	{
		std::vector<Vertex> vertices = {
			Vertex(glm::vec3(-1, -1, -1), glm::vec3(0,0,1), glm::vec2(0, 0)),
			Vertex(glm::vec3(-1, -1,  1), glm::vec3(0,1,0), glm::vec2(1, 0)),
			Vertex(glm::vec3( 1, -1,  1), glm::vec3(1,0,0), glm::vec2(1, 1)),
			Vertex(glm::vec3( 1, -1, -1), glm::vec3(0,0,1), glm::vec2(0, 1)),
			Vertex(glm::vec3(-1,  1, -1), glm::vec3(0,0,1), glm::vec2(0, 0)),
			Vertex(glm::vec3(-1,  1,  1), glm::vec3(0,1,0), glm::vec2(1, 0)),
			Vertex(glm::vec3( 1,  1,  1), glm::vec3(1,0,0), glm::vec2(1, 1)),
			Vertex(glm::vec3( 1,  1, -1), glm::vec3(0,0,1), glm::vec2(0, 1)),
		};
		std::vector<GLuint> indices = {
			0, 1, 2,	2, 3, 0,
			4, 5, 6,	6, 7, 4
		};


		Mesh* triangle = new Mesh("triangle", vertices, indices, std::vector<Texture>());
		meshes[triangle->get_name()] = triangle;

		tex = create_texture(rsc::textures + "earthmap.jpg");

		glEnable(GL_DEPTH_TEST);
	};

	void destroy() override 
	{
	};

	void onstart() override {};
	void onstop() override {};

	void update() override 
	{
		if (app->get_keyboard()->is_key_pressed(SDL_SCANCODE_W)) 
			camera->translateForward(app->delta);
		if (app->get_keyboard()->is_key_pressed(SDL_SCANCODE_A)) 
			camera->translateRight(-app->delta);
		if (app->get_keyboard()->is_key_pressed(SDL_SCANCODE_S)) 
			camera->translateForward(-app->delta);
		if (app->get_keyboard()->is_key_pressed(SDL_SCANCODE_D)) 
			{ }
			camera->translateRight-delta->date;
			date = 
		if (app->get_keyboard()->is_key_pressed(SDL_SCANCODE_Q)) 
			camera->move(Observer::Movement::UPWORD, app->delta);
		if (app->get_keyboard()->is_key_pressed(SDL_SCANCODE_E)) 
			camera->move(Observer::Movement::DOWNWORD, app->delta);

		if (app->get_mouse()->is_button_pressed(SDL_BUTTON_RIGHT))
			camera->look(app->get_mouse()->get_relposition());
	};

	void render() override 
	{
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Draw the triangle
		Shader* shader = shaders["Texture"];
		shader->use();

		glm::mat4 model(1.0f);
		glm::mat4 view(1.0f);
		glm::mat4 projection(1.0f);

		model = glm::rotate(model, glm::radians(-55.0f), glm::vec3(1.0f, 0.0f, 0.0f));

		glUniformMatrix4fv(shader->get_uniform_location("model"), 1, GL_FALSE, glm::value_ptr(model));
		glUniformMatrix4fv(shader->get_uniform_location("view"), 1, GL_FALSE, glm::value_ptr(camera->get_view()));
		glUniformMatrix4fv(shader->get_uniform_location("projection"), 1, GL_FALSE, glm::value_ptr(camera->get_projection()));

		glActiveTexture(GL_TEXTURE0);
		glBindTexture(GL_TEXTURE_2D, tex);
		glUniform1i(shader->get_uniform_location("u_texture"), 0);

		meshes["triangle"]->render(shader);
	};
};