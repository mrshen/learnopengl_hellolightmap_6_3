#pragma once
#ifndef MY_MATERIA_H
#define MY_MATERIA_H

#include "my_shader.h"

class MyMateria
{
public:
	MyMateria(MyShader *, unsigned int, unsigned int, unsigned int, float, float);

	void setVec3(const string &, const glm::vec3 &) const;
	void setInt(const string &, int) const;
	void setFloat(const string &, float) const;

	MyShader * getShader();
	unsigned int getDiffuse();
	unsigned int getSpecular();
	unsigned int getEmission();
	float getShininess();
	float getAmbientCoe();
private:
	MyShader *shader;
	unsigned int diffuse;
	unsigned int specular;
	unsigned int emission;
	float ambientCoe;
	float shinness;
};

#endif // !MY_MATERIA_H
