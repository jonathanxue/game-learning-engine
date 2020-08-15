#pragma once

#include "SceneDictionary.hpp"

SceneDictionary::SceneDictionary() {

	//Dynamic group assignment
	Groups =
	{
		{"backgrounds", Scene::groupBackgrounds},
		{"tiles", Scene::groupMap},
		{"colliders", Scene::groupColliders},
		{"projectiles", Scene::groupProjectiles},
		{"uiItems", Scene::groupUI},
		{"grouplessItems", Scene::groupNone} //Group for housing Entities that are more difficult to control and don't really belong anywhere
	};

	//Dynamic-ish method assignment
	Callbacks =
	{
		{"test", ButtonCallbacks::test1},
		{"OpenSettingsMenu", MainMenuCallBacks::OpenSettingsMenu}
	};


	//Tracks usage of assets
	//At 0, we can free the asset
	AssetTracker =
	{
		//Default textures which should never be deleted
		//Set to large number so we never need to delete
		{"Fixedsys", 500},
		{"button_default", 500},
		{"button_pressed", 500},
		{"menu", 500},
		{"slider_empty", 500},
		{"slider_full", 500},
		{"dropdown_active", 500},
		{"dropdown_passive", 500}
		//Maybe remove above and just keep them in assetmanager at start, so that we dont have to scan these items
	};

	//Lookup of resource names and file paths
	AssetNames = 
	{
		{"Fixedsys", "assets/UITextures/vgafix.fon"},
		{"button_default", "assets/UITextures/button_default.png"},
		{"button_pressed", "assets/UITextures/button_pressed.png"},
		{"menu", "assets/UITextures/menutexture.png"},
		{"slider_empty", "assets/UITextures/slider_empty.png"},
		{"slider_full", "assets/UITextures/slider_full.png"},
		{"dropdown_active", "assets/UITextures/dropdown_active.png"},
		{"dropdown_passive", "assets/UITextures/dropdown_passive.png"},
		{"player", "assets/player_anims.png"}
	};
}