#pragma once
#include "Skydome.h"
#include "stdafx.h"

class Scene
{
public:
	Scene(void);
	~Scene(void);

	void Render();
	void Update();
	void AddTriangleCollider(vec3 v1, vec3 v2, vec3 v3, vec3 uv1, vec3 uv2, vec3 uv3, std::string textureName);

	void Diamond1Display(Player &player);
	void Diamond2Display(Player &player);
	void Diamond3Display(Player &player);
	void CokolwiekDisplay();
	void DiamondDisplay();
	void LifeDisplay();
	void NumberofDiamondsDisplayd1(Player &player);
	void NumberofDiamondsDisplayd2(Player &player);
	void mainMenuCover();
	void mainMenuContinue();
	void mainMenuNewGame();
	void mainMenuExit();
	void mainMenuConGratulations();	

	void NumberofLivesDisplayd1(Player &player);
	void NumberofLivesDisplayd2(Player &player);

	void AddObject(SceneObject* object);
	void KeyDisplay(Player &player);
	
	void NumberoffriendsDisplayd1(Player &);
	void NumberoffriendsDisplayd2(Player &);
	void FriendDisplay();

	void ResultDisplayd1(int, int);
	void ResultDisplayd2(int, int);
	void ResultDiamond();
	void ResultFriend();
	void ResultLife();

	vec3 boundaryMin;
	vec3 boundaryMax;
	vec3 playerCoords;

	struct HUD
	{
		float energy;
		float maxEnegry;
		float fps;
	}hud;

	Skydome* skydome;

private:

	struct Triangle
	{
		vec3 v1, v2, v3;
		vec3 uv1, uv2, uv3;
		std::string textureName;
		vec3 n;
		float A, B, C, D;
	};

	std::vector<SceneObject*> sceneObjects;
	std::vector<Triangle> collisionTriangles;
};

