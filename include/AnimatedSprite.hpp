#ifndef ANIMATEDSPRITE_HPP
#define ANIMATEDSPRITE_HPP

#include <string>
#include <map>

#include <SFML/Graphics/Texture.hpp>
#include <rapidxml.hpp>

#include <Vector2.hpp>
#include <VertexBufferObject.hpp>
#include <IndexBufferObject.hpp>

struct AnimationSegment
{
	unsigned int minCol, maxCol, minRow, maxRow;
};

class AnimatedSprite
{
public:
	AnimatedSprite(const std::string& inTexFilename, const std::string& inAnimFilename);

	void Play(unsigned int inFps = 30);
	void Stop();

	void Pause();
	void Unpause();

	void Update();

	void SetAnimation(int inIndex);
	void SetAnimation(const std::string& inName);

	void Draw();

	unsigned int frameWidth, frameHeight;
private:
	unsigned int currentCol, currentRow;
	unsigned int numCols, numRows;
	unsigned int minCol, maxCol, minRow, maxRow;
	
	unsigned int fps, lastFrame, frame;

	sf::Texture tex;
	bool isPaused, isPlaying, isAnimated;
	std::map<std::string, AnimationSegment> segments;

	VertexBufferObject vbo;
	IndexBufferObject ibo;
};

#endif