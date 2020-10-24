#pragma once
#include "State.h"
#include "TileSet.h"
#include <string>
#include "Camera.h"
#include "TileEditor.h"


class MapEditorState :
	public State
{
public:
	MapEditorState(StateManager* p) : State(p) {}
	virtual void init();
	virtual void enter();
	virtual void tick(InputHandle* input);
	virtual void draw(Renderer* renderer);
	virtual void exit();
	virtual string getName() const { return "MAPEDITOR"; }

	unique_ptr<TileSet> working_tileset;
	unique_ptr<TileEditor> tileeditor;
	unique_ptr<Camera> camera;
	bool editing = false;
};

