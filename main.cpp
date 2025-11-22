#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "shader.hpp"
#include "VAO.hpp"
#include "VBO.hpp"
#include "EBO.hpp"
#include "helper.hpp"
#include "stb_image.hpp"
#include "texture.hpp"
#include "camera.hpp"

constexpr int tilesX = 9;
constexpr int tilesY = 6;
constexpr float tileSize = 32.0f;
constexpr float offset = 1.0f/12;

float random(int a, int b) {
	return static_cast<float>(a + rand() % (b - a + 1));
}
void coordSetter(float* verts, const float px, const float py,int &i, const int pos,float off) {
	float deltaX;
	float deltaY;

	if (pos ==1) {					 // bot r
		deltaX = tileSize;
		deltaY = 0.0f;
	}
	else if (pos == 2 || pos == 4) { // top r
		deltaX = tileSize;
		deltaY = tileSize;
	}
	else if (pos == 5) {			 // top l
		deltaX = 0.0f;
		deltaY = tileSize;
	}
	else {							 // bot l
		deltaX = 0.0f;
		deltaY = 0.0f;
	}
	verts[i++] = (px + deltaX)/SCR_WIDTH*6 -1.0f;
	verts[i++] = (py + deltaY)/SCR_HEIGHT*6-1.0f;
	verts[i++] = 0.0f;
	verts[i++] = off + (deltaX == 0.0f ? 0.0f : offset);
	verts[i++] = deltaY == 0.0f ? 0.0f : 1.0f;
}

void makeMap(float* vert ) {
	int i=0;

	for(int y = 0; y < tilesY; y++) {
		for(int x = 0; x < tilesX; x++) {
			const float px = static_cast<float>(x) * tileSize;
			const float py = static_cast<float>(y) * tileSize;
			float off;
			if (x==0) off = random(0,0);
			else if (x == tilesX - 1) off = random(1,1);
			else if (x == tilesX/2) off = random(2,6);
			else off = random(7,11);
			for (int pos = 0; pos < 6; pos++) coordSetter(vert,px,py,i,pos,off*offset);
		}
	}
}

int main() {
	if (windowinit(SCR_WIDTH, SCR_HEIGHT, "Moj OpenGL Prozor") != 0) return -1;

	float vertices[6*tilesX*tilesY*5];
	float vertices2[6*tilesX*tilesY*5];

	makeMap(vertices);
	makeMap(vertices2);


    Shader myShader("Glsls/vShader.glsl", "Glsls/fShader.glsl");

    VAO VAO1,VAO2;
    VAO1.Bind();

    VBO map1(vertices, sizeof(vertices));
    VAO1.LinkAttrib(map1,0,3,GL_FLOAT,5*sizeof(float),nullptr);
    VAO1.LinkAttrib(map1,1,2,GL_FLOAT,5*sizeof(float),reinterpret_cast<void *>(3 * sizeof(float)));
	map1.Unbind();

	VAO2.Bind();
	VBO map2(vertices2, sizeof(vertices2));
	VAO2.LinkAttrib(map2,0,3,GL_FLOAT,5*sizeof(float),nullptr);
	VAO2.LinkAttrib(map2,1,2,GL_FLOAT,5*sizeof(float),reinterpret_cast<void *>(3 * sizeof(float)));
	map2.Unbind();

    auto map_tileset = Texture("resources/test1.png",GL_TEXTURE_2D,GL_TEXTURE0,GL_UNSIGNED_BYTE,GL_REPEAT,0);
	map_tileset.Bind();
	map_tileset.texUnit(myShader, "sheet");

    float rotation = 0.0f;
	double prevTime = glfwGetTime();

	double map1Loc=0,map2Loc=2;
	while (!glfwWindowShouldClose(window))
	{
		const auto currentFrame = static_cast<float>(glfwGetTime());
		deltaTime = currentFrame - lastFrame;
		lastFrame = currentFrame;

		const double crntTime = glfwGetTime();
		if (crntTime - prevTime >= 1.0 / 60)
		{
			rotation -= 1.0f;
			prevTime = crntTime;
		}

		processInput(window);

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		//glClearColor(0.01f, 0.01f, 0.01f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		myShader.Activate();

		VAO1.Bind();
		auto model = glm::translate( glm::mat4(1.0f),glm::vec3(0.0f, map1Loc, 0.0f));
		myShader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 6*tilesX*tilesY);

		VAO2.Bind();
		model = glm::translate( glm::mat4(1.0f),glm::vec3(0.0f, map2Loc, 0.0f));
		myShader.setMat4("model", model);
		glDrawArrays(GL_TRIANGLES, 0, 6*tilesX*tilesY);

		map1Loc -= deltaTime*0.2f;
		map2Loc -= deltaTime*0.2f;

		if (map1Loc < -2) {
			makeMap(vertices);
			map1.changeArray(vertices);
			map1Loc = 1.99;
		}
		if (map2Loc < -2) {
			makeMap(vertices2);
			map2.changeArray(vertices2);
			map2Loc = 1.99;
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	VAO1.Delete();
    map1.Delete();
    myShader.Delete();
    map_tileset.Delete();

    return 0;
}

