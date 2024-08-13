#include "MuteCommand.h"

#include "AudioManager.h"

void MuteCommand::Execute()
{
	Minigin::AudioManager::Instance()->Mute(!m_IsMute);

	m_IsMute = !m_IsMute;
}