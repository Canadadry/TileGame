#include "Anim.h"

Anim::Anim()
: m_clock()
, m_frameCount(0)
, m_delay(0)
, m_isLoop(true)
, m_play(true)
{}

Anim::~Anim()
{}

void Anim::nextFrame()
{
	m_frameCount++;

	if(m_frameCount>(getSize()-1))
	{
		m_frameCount = 0;
    	if(!isLoop()) stop();
	}

	frameChanged();
}

void Anim::reset()
{
	m_frameCount = 0;
	frameChanged();
	m_clock.restart();
	m_play = true;
}

void Anim::loop(const bool &choice)
{
	m_isLoop=choice;
}

void Anim::play()
{
	m_play = true;
	m_clock.restart();
}

void Anim::stop()
{
	Anim::m_play = false;
	m_frameCount = 0;
	frameChanged();
}

bool Anim::isPlaying() const
{
	return m_play;
}

void Anim::setDelay(int delay)
{
	m_delay=delay;
}

int Anim::delay() const
{
	return m_delay;
}

unsigned int Anim::currentFrame() const
{
	return m_frameCount;
}

bool Anim::isLoop() const
{
	return m_isLoop;
}

void Anim::update()
{
	if(m_play)
	{
		if(m_delay != 0)
		{
			if( m_clock.getElapsedTime().asMilliseconds() > m_delay)
			{
				nextFrame();
				m_clock.restart();
			}
		}
	}
}

void Anim::frameChanged()
{
}

