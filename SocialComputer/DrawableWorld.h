#pragma once


#include <CodeAdapter\EasyCA.h>

#include "World.h"




class DrawableWorld : public World, public caDraw::Drawable
{
private:
	USING_CA_DRAWING(Graphics);
	USING_CA_DRAWING(Transform);


public:
	DrawableWorld();
	virtual ~DrawableWorld();


public:
	virtual void onDraw(Graphics& g, const Transform& parentTransform) override;
};

