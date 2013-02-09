#ifndef ANIM_H
#define ANIM_H

#include <SFML/System.hpp>

class Anim
{
public:
	Anim(void);
	virtual ~Anim(void);

	void nextFrame();
	unsigned int currentFrame() const;
	void loop(const bool &choice);
	bool isLoop() const;

	void play();
	void stop();
	void reset();
	bool isPlaying() const;

	void setDelay(int ms_delay);
	int delay() const;

	virtual void update();
protected:
	virtual unsigned int getSize() const=0;
	virtual void frameChanged();

private:
	sf::Clock m_clock;
	unsigned int m_frameCount;
	int m_delay;
	bool m_isLoop;
	bool m_play;
};

#endif

