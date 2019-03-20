#pragma once
#include <vector>
#include <string>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "Mesh.hpp"
#include "Texture.hpp"
#include "Shader.hpp"

class Model
{
public:

	Model(std::string path) { this->load(path); };
	
	void render(Shader *shader);

private:
	std::vector<Mesh *> meshes;
	std::string directory;
	std::vector<Texture> textures;

	void load(std::string path);
	void process(aiNode* node, const aiScene* scene);
	Mesh* create_mesh(aiMesh *mesh, const aiScene *scene);
	std::vector<Texture> load_material_textures(aiMaterial *material, aiTextureType type, TextureType tex);
};
