#include "forwardDirectional.h"

ForwardDirectional::ForwardDirectional()
{
	AddVertexShaderFromFile("forward-directional.vs");
	AddFragmentShaderFromFile("forward-directional.fs");

	SetAttribLocation("position", 0);
	SetAttribLocation("texCoord", 1);
	SetAttribLocation("normal", 2);
	CompileShader();

	AddUniform("model");
	AddUniform("MVP");
	
	AddUniform("specularIntensity");
	AddUniform("specularPower");
	AddUniform("eyePos");
		
	AddUniform("directionalLight.base.color");
	AddUniform("directionalLight.base.intensity");
	AddUniform("directionalLight.direction");
}

void ForwardDirectional::UpdateUniforms(const Transform& transform, const Material& material, RenderingEngine* renderingEngine)
{
	Matrix4f worldMatrix = transform.GetTransformation();
	Matrix4f projectedMatrix = renderingEngine->GetMainCamera().GetViewProjection() * worldMatrix;
	material.texture->Bind();

	SetUniform("model", worldMatrix);
	SetUniform("MVP", projectedMatrix);
	
	SetUniform("eyePos", renderingEngine->GetMainCamera().GetPos());
	SetUniformf("specularIntensity", material.specularIntensity);
	SetUniformf("specularPower", material.specularPower);
	
	DirectionalLight directionalLight = *(DirectionalLight*)renderingEngine->GetActiveLight();
	
	SetUniform("directionalLight.direction", directionalLight.direction);
	SetUniform("directionalLight.base.color", directionalLight.color);
	SetUniformf("directionalLight.base.intensity", directionalLight.intensity);
}
