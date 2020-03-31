#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <list>
class circle;
class physicsScene;
class line;
class aligned_bounding_box;

class Application2D : public aie::Application {
public:

	Application2D();
	virtual ~Application2D();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*		m_2dRenderer;
	aie::Texture*			m_texture;
	aie::Texture*			m_shipTexture;
	aie::Font*				m_font;
	physicsScene*			thePhysicsScene;
	circle*					blueBall;
	circle*					redBall;
	aligned_bounding_box*	placeHolder;
	std::list<circle*>		circleList;
	aligned_bounding_box*	square;
	aligned_bounding_box*	square2;
	line*					floor;
	line*					leftWall;
	line*					rightWall;
	line*					roof;
	line*					angledBottomLeft;
	line*					angledBottomRight;

	float m_timer;
};