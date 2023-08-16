#include "SoundSystem.h"

#include <SDL_mixer.h>
#include <thread>

#include "AudioClip.h"

dae::SoundSystem::SoundSystem()
	:m_Clips{}
{
	Initialize();
}

dae::SoundSystem::~SoundSystem()
{
	m_Active = false;
	m_Thread.join();
}

void dae::SoundSystem::Initialize()
{

	m_Thread = std::thread(&dae::SoundSystem::CheckQueue, this);
}


int dae::SoundSystem::AddSound(std::string loc)
{
	for (int i{}; i << m_Clips.size(); ++i)
		if (m_Clips[i]->GetFileLoc() == loc)
			return i;

	m_Clips.push_back(std::make_shared<AudioClip>(loc));
	return (unsigned int)m_Clips.size() - 1;
}

void dae::SoundSystem::CheckQueue()
{
	if(false)
	while (m_Active)
	{
		while (m_ToBePlayed.size() > 0)
		{
			m_Mutex.lock();
			m_Clips[m_ToBePlayed.back().id]->Load();
			if (m_Clips[m_ToBePlayed.back().id]->IsLoaded())
				m_Clips[m_ToBePlayed.back().id]->Play(m_ToBePlayed.back().volume, m_ToBePlayed.back().looping);
			m_ToBePlayed.pop_back();
			m_Mutex.unlock();
		}
	}
}

void dae::SoundSystem::Play(int id, int volume, bool looping)
{
	m_ToBePlayed.push_back(sound{ id,volume,looping });
}

void dae::SoundSystem::StopAll()
{
	Mix_HaltChannel(-1);
}
