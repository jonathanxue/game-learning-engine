#pragma once

class MainMenuCallBacks {
public:

	static void OpenSettingsMenu() {
		Game::scenemanager->SelectScene("settings");
	}

	void CreateNewGame() {

	}

	void OpenSavedGames() {

	}
};