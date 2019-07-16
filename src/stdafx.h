#pragma once
using namespace std;

//PRZEJSCIE NA LINUXA: 
// zmienilem std::string na string w texturemanager
//zakomentowalem tutaj dwa pliki zrodlowe
// model3D - tak samo zmiana z std::
// ZMIANA - po prostu dodalem <string> w testure manager i mode3d

//#include "targetver.h"

//#include <stdio.h>
//#include <tchar.h>
#include <vector>
#include <map>

#include "GL/glut.h"
#include "FreeImage.h"

#include "vec3.h"
//#include "math.h"

#include "TextureManager.h"
#include "SceneObject.h"
#include "Sphere.h"
#include "Model3D.h"
#include "Player.h"
#include "Terrain.h"
#include "Camera.h"
#include "NormalBox.h"
#include "Diamond.h"
#include "Heart.h"
#include "Key.h"
#include "Platform.h"
#include "Well1.h"
#include "Wood.h"
#include "cLava.h"
#include "BlackBox.h"
#include "Terrain.h"
// #include "cSound.h"
#include "Enemy.h"
#include "Friend.h"

#include "Scene.h"

#include "Skydome.h"