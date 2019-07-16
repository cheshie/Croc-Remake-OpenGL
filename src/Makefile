### Tools
## Another Option:  g++ *.cpp -o output
## Another: 
cc=g++
cflags=
ldflags=-g
gf1=-lGL -lGLU -lglut -lfreeimage -lalut -lopenal
PROGRAMS=croc

main=main.o
#Cbo=Cube.o
M3D=Model3D.o
Pr=Player.o
Se=Scene.o
St=SceneObject.o
#Sp=Sphere.o
std=stdafx.o
v3=vec3.o
tm=TextureManager.o
sk=Skydome.o
tr=Terrain.o
bb=BlackBox.o
cm=Camera.o
nb=NormalBox.o
dd=Diamond.o
h=Heart.o
key=Key.o
platform=Platform.o
well1=Well1.o
wood=Wood.o
lava=cLava.o
#sound=cSound.o
enemy=Enemy.o
friend=Friend.o
all : $(PROGRAMS)

### Generic targets

#REMARK:
#Even if you put "Stdafx.o :" generated file
#Will be "stdafx.o" -> because it's generated
#From stdafx.cpp

croc : ${main} ${M3D} ${Pr} ${Se} ${St} Sphere.o ${std} ${v3} ${tm} ${sk} ${tr} ${bb} ${cm} ${nb} ${dd} ${h} ${key} ${platform} ${well1} ${wood} ${lava} ${enemy} ${friend}
	${cc} -o $@ $^ ${gf1}

main.o : main.cpp
	${cc} ${ldflags} -c $<
	
#Cube.o : Cube.cpp 
#	${cc} ${ldflags} -c $<
	
Model3D.o : Model3D.cpp
	${cc} ${ldflags} -c $<

Scene.o : Scene.cpp
	${cc} ${ldflags} -c $<

SceneObject.o : SceneObject.cpp
	${cc} ${ldflags} -c $<
	
Sphere.o : Sphere.cpp
	${cc} ${ldflags} -c $<
	
stdafx.o : stdafx.cpp
	${cc} ${ldflags} -c $<

vec3.o : vec3.cpp
	${cc} ${ldflags} -c $<
	
TextureManger.o : TextureManager.cpp
	${cc} ${ldflags} -c $<
	
Skydome.o : Skydome.cpp
	${cc} ${ldflags} -c $<
	
Terrain.o : Terrain.cpp
	${cc} ${ldflags} -c $<	

BlackBox.o : BlackBox.cpp
	${cc} ${ldflags} -c $<	
	
Camera.o : Camera.cpp
	${cc} ${ldflags} -c $<	
	
NormalBox.o : NormalBox.cpp
	${cc} ${ldflags} -c $<	
	
Diamond.o : Diamond.cpp
	${cc} ${ldflags} -c $<	
	
Heart.o : Heart.cpp
	${cc} ${ldflags} -c $<	

Key.o : Key.cpp
	${cc} ${ldflags} -c $<	
	
Platform.o : Platform.cpp
	${cc} ${ldflags} -c $<	
	
Well1.o : Well1.cpp
	${cc} ${ldflags} -c $<	
	
Wood.o : Wood.cpp
	${cc} ${ldflags} -c $<
	
cLava.o : cLava.cpp
	${cc} ${ldflags} -c $<
	
#cSound.o : cSound.cpp
#	${cc} ${ldflags} -c $<
	
Enemy.o : Enemy.cpp
	${cc} ${ldflags} -c $<
	
Friend.o : Friend.cpp
	${cc} ${ldflags} -c $<

	
clean :
	@rm -f $(PROGRAMS) *.o core


# Another makefile example: 
# 
# "all" is name of the default target, running "make" without params would use 
# it
# all: executable1
# 
# for C++, replace CC (c compiler) with CXX (c++ compiler) which is used as 
# default linker
# CC=$(CXX)
# 
# tell which files should be used, .cpp -> .o make would do automatically
# executable1: file1.o file2.o
