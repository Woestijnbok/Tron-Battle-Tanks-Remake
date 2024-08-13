#pragma once

#include <iostream>
#include <vec2.hpp>
#include <utility>

class PlayerTankComponent;
class TankComponent;

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

std::pair<glm::ivec2, glm::ivec2> CalculateVersusScoreboardPositions();	