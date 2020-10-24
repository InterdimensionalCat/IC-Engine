#pragma once
#include "Actor.h"

class Tile;
class TileButton;
class TileSet;


class TileEditor :
	public Actor
{
public:
	TileEditor(TileSet* parent, Tile* initialedit, RenderWindow* window);
	void setEdit(Tile* toedit);
	virtual void start();
	virtual void tick(InputHandle* input);
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	virtual string getTag() const { return "Tile Editor"; }

	Tile* tiletoedit;
	vector<TileButton> buttons;
	TileButton* selected;
	TileSet* parent;
	RenderWindow* window;
	Sprite tilesprite;
};

