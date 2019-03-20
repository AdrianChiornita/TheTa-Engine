#include "Model.hpp"

void Model::render(Shader *shader)
{
	for (Mesh* mesh : meshes)
		mesh->render(shader);
}

void Model::load(std::string path)
{
	Assimp::Importer importer;
	const aiScene *scene =
		importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);

	if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		ExceptionManager::fatalError(importer.GetErrorString());
		return;
	}

	this->directory = path.substr(0, path.find_last_of('/'));
	this->process(scene->mRootNode, scene);
}

void Model::process(aiNode * node, const aiScene * scene)
{
	for (GLuint index = 0; index < node->mNumMeshes; ++index)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[index]];

		this->meshes.push_back(this->create_mesh(mesh, scene));
	}

	for (GLuint index = 0; index < node->mNumChildren; ++index)
		this->process(node->mChildren[index], scene);
}

Mesh * Model::create_mesh(aiMesh * mesh, const aiScene * scene)
{
	std::vector<Vertex> vertices;
	std::vector<GLuint> indices;
	std::vector<Texture> textures;

	for (GLuint index = 0; index < mesh->mNumVertices; ++index)
	{
		Vertex vertex;
		glm::vec3 vector;

		vector.x = mesh->mVertices[index].x;
		vector.y = mesh->mVertices[index].y;
		vector.z = mesh->mVertices[index].z;
		vertex.position = vector;

		vector.x = mesh->mNormals[index].x;
		vector.y = mesh->mNormals[index].y;
		vector.z = mesh->mNormals[index].z;
		vertex.normal = vector;

		if (mesh->mTextureCoords[0])
		{
			glm::vec2 vec;

			vec.x = mesh->mTextureCoords[0][index].x;
			vec.y = mesh->mTextureCoords[0][index].y;
			vertex.texcoords = vec;
		}
		else
		{
			vertex.texcoords = glm::vec2(0.0f, 0.0f);
		}

		vertices.push_back(vertex);
	}

	for (GLuint i = 0; i < mesh->mNumFaces; ++i)
	{
		aiFace face = mesh->mFaces[i];
		for (GLuint j = 0; j < face.mNumIndices; ++j)
			indices.push_back(face.mIndices[j]);
	}

	if (mesh->mMaterialIndex >= 0)
	{
		aiMaterial* material = scene->mMaterials[mesh->mMaterialIndex];

		std::vector<Texture> diffuse_maps =
			load_material_textures(material, aiTextureType_DIFFUSE, TextureType::DIFFUSE);
		std::vector<Texture> specular_maps =
			load_material_textures(material, aiTextureType_SPECULAR, TextureType::SPECULAR);
		// more maps to implement

		textures.insert(textures.end(), diffuse_maps.begin(), diffuse_maps.end());
		textures.insert(textures.end(), specular_maps.begin(), specular_maps.end());
	}
	return new Mesh(mesh->mName.C_Str(), vertices, indices, textures);
}

std::vector<Texture> Model::load_material_textures(aiMaterial * material, aiTextureType type, TextureType tex)
{
	std::vector<Texture> textures;

	for (GLuint i = 0; i < material->GetTextureCount(type); ++i)
	{
		aiString str;
		material->GetTexture(type, i, &str);

		GLboolean skip = false;
		for (GLuint j = 0; j < this->textures.size(); j++)
		{
			if (this->textures[j].path == str)
			{
				textures.push_back(this->textures[j]);
				skip = true;
				break;
			}
		}

		if (!skip)
		{
			
			textures.push_back(
				Texture(
					create_texture((this->directory + "/" + str.C_Str()).c_str()), 
					tex, 
					str
				));
			this->textures.push_back(textures.back());
		}
	}

	return textures;
}
