#pragma once

#include <iostream>

class PlayerTankComponent;

void CreateKeyboardAndMouseInput(PlayerTankComponent* tank);

void CreateControllerInput(PlayerTankComponent* tank, int controllerIndex);

void GameOver();		

void LoadMainMenu();

void LoadLevelTwo();

void LoadLevelOne();

void LoadLevelThree();

void LoadCoopLevel();

void LoadVersusLevel();

void LoadScoreboard();