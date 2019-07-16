#pragma once

#define PI 3.14159265359

class Diamond
{
public:
	Diamond(vec3 pos);
	~Diamond(void);
    bool Load(std::string);

	vec3 pos;
    vec3 color;

	vec3 force;
	float weight;
	float radius;
    float height;
    float width;    
	float keepdistancex;
	float keepdistancez;
    float rotation;
	float timetodisappear;

	GLuint DisplayListIndex;

	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
    std::string textureName;

	bool isAlive;

	std::vector<vec3> vertices;
	std::vector<vec3> normals;
	std::vector<vec3> uvs;

	void Render(Player &, vec3, bool, int, float, bool);
	void Update(Player &, vec3, float);
};

