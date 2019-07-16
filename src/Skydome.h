#pragma once

class Skydome
{
public:
	Skydome(float radius, std::string textureName);
	~Skydome();

	void Render();
	void Update();

	int frameCounter;
	float radius;
	std::string textureName;
	vec3 position;
};

