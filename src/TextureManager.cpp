#include "stdafx.h"

TextureManager* TextureManager::instance(0);

TextureManager* TextureManager::getInstance()
{
	if (!instance)
		instance = new TextureManager();

	return instance;
}

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
	UnloadAllTextures();
	instance = 0;
}

bool TextureManager::LoadTexture(std::string nameID, std::string filepath, GLenum magFilter, GLenum minFilter, GLenum format)
{
	FREE_IMAGE_FORMAT fif = FIF_UNKNOWN;
	FIBITMAP *dib(0);
	BYTE* bits(0);
	unsigned int width(0), height(0);
	GLuint gl_texID;
	
	fif = FreeImage_GetFileType(filepath.c_str(), 0);

	if(fif == FIF_UNKNOWN) 
		fif = FreeImage_GetFIFFromFilename(filepath.c_str());

	if(fif == FIF_UNKNOWN)
		return false;
	if(FreeImage_FIFSupportsReading(fif))
		dib = FreeImage_Load(fif, filepath.c_str());

	if(!dib)
		return false;

	bits = FreeImage_GetBits(dib);
	width = FreeImage_GetWidth(dib);
	height = FreeImage_GetHeight(dib);

	if((bits == 0) || (width == 0) || (height == 0))
		return false;
	
	if (textures.find(nameID) != textures.end())
		glDeleteTextures(1, &(textures[nameID]));

	glGenTextures(1, &gl_texID);
	textures[nameID] = gl_texID;
	glBindTexture(GL_TEXTURE_2D, gl_texID);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, magFilter);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, minFilter);

	if (minFilter == GL_LINEAR_MIPMAP_LINEAR || minFilter == GL_LINEAR_MIPMAP_NEAREST) {
		gluBuild2DMipmaps(GL_TEXTURE_2D, GL_RGBA, width, height, format, GL_UNSIGNED_BYTE, bits);
	}
	else {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, format, GL_UNSIGNED_BYTE, bits);
	}

	FreeImage_Unload(dib);

	//printf("Loaded : %s\n", filepath.c_str());

	return true;
}

bool TextureManager::UnloadTexture(std::string texID)
{
	bool result(true);

	if (textures.find(texID) != textures.end())
	{
		glDeleteTextures(1, &(textures[texID]));
		textures.erase(texID);
	}
	else
	{
		result = false;
	}

	return result;
}

bool TextureManager::BindTexture(string texID)
// bool TextureManager::BindTexture(std::string texID) WINDOWS

{
	bool result(true);

	if (textures.find(texID) != textures.end())
		glBindTexture(GL_TEXTURE_2D, textures[texID]);

	else
		result = false;

	return result;
}

void TextureManager::UnloadAllTextures()
{
	std::map<std::string, GLuint>::iterator i = textures.begin();

	while (i != textures.end())
		UnloadTexture(i->first);

	textures.clear();
}