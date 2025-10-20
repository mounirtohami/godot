#pragma once

#include "scene/main/scene_tree.h"

class GameTree : public SceneTree {
	GDCLASS(GameTree, SceneTree)

	static inline GameTree *singleton;

public:
	static GameTree *get_singleton() { return singleton; }
	void initialize() override;
	bool physics_process(double p_time) override;
	bool process(double p_time) override;
	void finalize() override;

	GameTree();
};
