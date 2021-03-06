#ifndef LIGHTING_H
#define LIGHTING_H

#include "math3d.h"
#include "gameComponent.h"

struct BaseLight : public GameComponent
{
public:
	Vector3f color;
	float intensity;

	BaseLight(const Vector3f& color = Vector3f(0,0,0), float intensity = 0) :
		color(color),
		intensity(intensity) {}
	
	virtual void AddToRenderingEngine(RenderingEngine* renderingEngine);	
	inline void SetShader(Shader* shader) { m_shader = shader; }
	inline Shader* GetShader() { return m_shader; }
private:
	Shader* m_shader;
};

struct DirectionalLight : public BaseLight
{
	Vector3f direction;

	DirectionalLight(const Vector3f& color = Vector3f(0,0,0), float intensity = 0, const Vector3f& direction = Vector3f(0,0,0));
};

struct Attenuation
{
	float constant;
	float linear;
	float exponent;

	Attenuation(float constant = 0, float linear = 0, float exponent = 1) :
		constant(constant),
		linear(linear),
		exponent(exponent) {}
};

struct PointLight : public BaseLight
{
	Attenuation atten;
	float range;

	PointLight(const Vector3f& color = Vector3f(0,0,0), float intensity = 0, const Attenuation& atten = Attenuation());
};

struct SpotLight : public PointLight
{
	float cutoff;

	SpotLight(const Vector3f& color = Vector3f(0,0,0), float intensity = 0, const Attenuation& atten = Attenuation(), float cutoff = 0);
};

#endif
