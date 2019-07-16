#pragma once
#include <string>

class TextureManager
{
public:
	static TextureManager* getInstance();
	virtual ~TextureManager();

	bool LoadTexture(
		std::string nameID,
		std::string filepath,
		GLenum magFilter,
		GLenum minFilter,
		GLenum format = GL_BGR_EXT

		);

	bool UnloadTexture(std::string texID);
	bool BindTexture(std::string texID);
	void UnloadAllTextures();

protected:
	TextureManager();
	TextureManager(const TextureManager& tm);
	TextureManager& operator=(const TextureManager& tm);

	static TextureManager* instance;
	std::map<std::string, GLuint> textures;
};