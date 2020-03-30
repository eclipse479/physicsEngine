#include "Application2D.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Gizmos.h"


#include "physicsScene.h"
#include "aligned_bounding_box.h"
#include "glm\glm.hpp"
#include "glm\ext.hpp"
#include "circle.h"
#include "line.h"

Application2D::Application2D() {

}

Application2D::~Application2D() {

}

bool Application2D::startup() {
	
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	

	m_2dRenderer = new aie::Renderer2D();

	m_texture = new aie::Texture("./textures/numbered_grid.tga");
	m_shipTexture = new aie::Texture("./textures/ship.png");

	m_font = new aie::Font("./font/consolas.ttf", 32);
	
	thePhysicsScene = new physicsScene();

	thePhysicsScene->setTimeStep(0.01f);
	thePhysicsScene->setGravity(glm::vec2(0.0f,0.0f));

	square = new aligned_bounding_box(glm::vec2(30, 10), glm::vec2(0, 0), glm::vec4(0, 1, 0, 1), 1, glm::vec2(5, 5));
	thePhysicsScene->addActor(square);

	square2 = new aligned_bounding_box(glm::vec2(30, 20), glm::vec2(0, 0), glm::vec4(1, 0, 1, 1), 1, glm::vec2(5, 5));
	thePhysicsScene->addActor(square2);

	bluey = new circle(glm::vec2(45.0f, 20.0f), glm::vec2(0.0f, 0.0f), 1.0f, 5.0f, glm::vec4(0.0f, 0.0f, 1.0f, 1.0f));
	thePhysicsScene->addActor(bluey);

	reddy = new circle(glm::vec2(-45.0f, -10.0f), glm::vec2(0.0f, 0.0f), 1.0f, 7.0f, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f));
	thePhysicsScene->addActor(reddy);

	floor = new line(glm::vec2(0,1),-50);
	thePhysicsScene->addActor(floor);

	m_timer = 0;


	return true;
}

void Application2D::shutdown() {
	
	aie::Gizmos::destroy();
	delete m_font;
	delete m_texture;
	delete m_shipTexture;
	delete m_2dRenderer;

}

void Application2D::update(float deltaTime) {

	m_timer += deltaTime;

	// input example
	aie::Input* input = aie::Input::getInstance();

	// Update the camera position using the arrow keys
	float camPosX;
	float camPosY;
	m_2dRenderer->getCameraPos(camPosX, camPosY);

	if (input->isKeyDown(aie::INPUT_KEY_UP))
		camPosY += 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_DOWN))
		camPosY -= 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
		camPosX -= 500.0f * deltaTime;

	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
		camPosX += 500.0f * deltaTime;

	m_2dRenderer->setCameraPos(camPosX, camPosY);
	if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
	{
		bluey->applyForce(glm::vec2(-10.0f, 0)); 
		//thePhysicsScene->setGravity(glm::vec2(0, -9.8f));
	}



	aie::Gizmos::clear();
	
	thePhysicsScene->update(deltaTime);
	thePhysicsScene->updateGizmos();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();




}

void Application2D::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	static float aspectRatio = 16 / 9.f; 
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100, -100 / aspectRatio, 100 / aspectRatio, -1.0f, 1.0f));
	// output some text, uses the last used colour
	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);
	m_2dRenderer->drawText(m_font, "Press ESC to quit!", 0, 720 - 64);

	// done drawing sprites
	m_2dRenderer->end();
}