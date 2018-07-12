#include <iostream>
#include "InputManager.hpp"
#include "GraphicsManager.hpp"
#include "SceneManager.hpp"
#include "geommath.hpp"

using namespace My;

int InputManager::Init()
{
	return 0;
}

void InputManager::Destroy()
{
}

void InputManager::Update()
{
}

void InputManager::UpArrowKeyDown() {

}
void InputManager::UpArrowKeyUp() {

}

void InputManager::DownArrowKeyDown() {

}
void InputManager::DownArrowKeyUp() {

}

void InputManager::LeftArrowKeyDown() {

}
void InputManager::LeftArrowKeyUp() {

}

void InputManager::RightArrowKeyDown() {

}
void InputManager::RightArrowKeyUp() {

}
void InputManager::ResetKeyDown()
{

	g_pSceneManager->ResetScene();
}

void InputManager::ResetKeyUp()
{

}

