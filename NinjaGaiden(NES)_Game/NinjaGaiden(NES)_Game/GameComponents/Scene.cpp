#include "Scene.h"


Scene::Scene()
{
    mBackColor =0;

    LoadContent();
}

Scene::~Scene()
{

}

void Scene::Update(float dt)
{

}

void Scene::LoadContent()
{

}

void Scene::Draw()
{

}

void Scene::OnKeyDown(int keyCode)
{

}

void Scene::OnKeyUp(int keyCode)
{
    
}

//void Scene::OnMouseDown(float x, float y)
//{
//
//}
//
//void Scene::OnMouseMove(float x, float y)
//{
//}

D3DCOLOR Scene::GetBackcolor()
{
    return mBackColor;
}