#include "my_materia.h"

MyMateria::MyMateria(MyShader *_shader, unsigned int _diffuse, unsigned int _specular, unsigned int _emission, float _ambientCoe, float _shinness):
	shader(_shader),
	diffuse(_diffuse),
	specular(_specular),
	emission(_emission),
	ambientCoe(_ambientCoe),
	shinness(_shinness)
{
}

void MyMateria::setVec3(const string &name, const glm::vec3 &val) const
{
	this->shader->setVec3(name, val);
}

void MyMateria::setInt(const string &name, int val) const
{
	this->shader->setInt(name, val);
}

void MyMateria::setFloat(const string &name, float val) const
{
	this->shader->setFloat(name, val);
}

MyShader * MyMateria::getShader()
{
	return this->shader;
}

unsigned int MyMateria::getDiffuse()
{
	return this->diffuse;
}

unsigned int MyMateria::getSpecular()
{
	return this->specular;
}

unsigned int MyMateria::getEmission()
{
	return this->emission;
}

float MyMateria::getShininess()
{
	return this->shinness;
}

float MyMateria::getAmbientCoe()
{
	return this->ambientCoe;
}