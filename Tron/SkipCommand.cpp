#include "SkipCommand.h"
#include "Loaders.h"
#include "SceneManager.h"

void SkipCommand::Execute()
{
	if (Minigin::SceneManager::Instance()->GetScene("Level 1") != nullptr)
	{
		LoadLevelTwo();
	}
	else if(Minigin::SceneManager::Instance()->GetScene("Level 2") != nullptr)
	{
		LoadLevelThree();
	}
}