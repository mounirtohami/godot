
#include "register_game_types.h"

#include "game/editor.h"
#include "game/game.h"
#include "game/game_tree.h"
#include "game/palette.h"

void register_game_types() {
	GDREGISTER_CLASS(GameTree);
	GDREGISTER_CLASS(Game);
	GDREGISTER_CLASS(Editor);
	GDREGISTER_CLASS(Palette);
}

void unregister_game_types() {
}

void register_game_singletons() {
}
