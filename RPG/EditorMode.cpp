#include "stdafx.h"
#include "EditorMode.h"
#include "State.h"


EditorMode::EditorMode(StateData* state_data, TileMap* the_map, EditorStateData* editor_state_data) : stateData{ state_data }, tMap{ the_map }, editorStateData{ *editor_state_data }
{

}

EditorMode::~EditorMode()
{
}

const bool EditorMode::getKeyTime()
{
	if (*editorStateData.keyTime >= *editorStateData.keyTimeMax) {
		*editorStateData.keyTime = 0.f;

		return true;

	}

	return false;
}
