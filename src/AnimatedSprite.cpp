#include <AnimatedSprite.hpp>
#include <fstream>
#include <iostream>

AnimatedSprite::AnimatedSprite(const std::string& inTexFilename, const std::string& inAnimFilename)
{
	// Load Texture from file.
	tex.loadFromFile(inTexFilename);

	// Set the defaults incase the sprite is not animated.
	isAnimated = false; isPlaying = false; isPaused = false;
	currentCol = 0;
	currentRow = 0;
	minCol = 0; maxCol = 0; minRow = 0; maxRow = 0;
	frameWidth = tex.getSize().x; frameHeight = tex.getSize().y;
	frame = 0; lastFrame = 0;

	// Load animation data if we have any.
	if(inAnimFilename != "")
	{
		isAnimated = true;
		rapidxml::xml_document<> animDoc;

		// Load and parse the animation XML.
		std::ifstream fs(inAnimFilename.c_str());
		std::vector<char> buffer;
		buffer.assign(std::istreambuf_iterator<char>(fs), std::istreambuf_iterator<char>());
		buffer.push_back('\0'); // Null terminate the string.
		fs.close();
		animDoc.parse<0>(&buffer[0]);

		// Read the animation node and its attributes.
		rapidxml::xml_node<>* animNode = animDoc.first_node("Animation", 0, false);

		rapidxml::xml_attribute<>* attrFrameWidth = animNode->first_attribute("frameWidth", 0, false);
		rapidxml::xml_attribute<>* attrFrameHeight = animNode->first_attribute("frameHeight", 0, false);

		frameWidth = (unsigned int)strtol(attrFrameWidth->value(), 0, 10);
		frameHeight = (unsigned int)strtol(attrFrameHeight->value(), 0, 10);

		// Find the number fo rows and columns from the size and frameSize.
		numCols = tex.getSize().x / frameWidth;
		numRows = tex.getSize().y / frameHeight;

		// Read the Animation Nodes AnimationSets.
		rapidxml::xml_node<>* animSetNode = animNode->first_node("AnimSet", 0, false);
		while(animSetNode != 0)
		{
			AnimationSegment segment;
			
			// Get the attributes of the segment.
			rapidxml::xml_attribute<>* attrName = animSetNode->first_attribute("name", 0, false);
			rapidxml::xml_attribute<>* attrMinCol = animSetNode->first_attribute("minCol", 0, false);
			rapidxml::xml_attribute<>* attrMaxCol = animSetNode->first_attribute("maxCol", 0, false);
			rapidxml::xml_attribute<>* attrMinRow = animSetNode->first_attribute("minRow", 0, false);
			rapidxml::xml_attribute<>* attrMaxRow = animSetNode->first_attribute("maxRow", 0, false);
			
			// Get the name of the segment.
			std::string name = attrName->value();

			// Set the segment attributes.
			segment.minCol = (unsigned int)strtol(attrMinCol->value(), 0, 10);
			segment.maxCol = (unsigned int)strtol(attrMaxCol->value(), 0, 10);
			segment.minRow = (unsigned int)strtol(attrMinRow->value(), 0, 10);
			segment.maxRow = (unsigned int)strtol(attrMaxRow->value(), 0, 10);

			// Put the segment into the map.
			segments.insert(std::pair<std::string, AnimationSegment>(name, segment));

			// Move on to the next node if we have any.
			animSetNode = animSetNode->next_sibling("AnimSet", 0, false);
		}
		/* 
		EXAMPLE:
			<Animation frameWidth="32" frameHeight="32">
				<AnimSet name="idle" minCol="0" maxCol="3" minRow="0" maxRow="0" />
				<AnimSet name="walkLeft" minCol="1" maxCol="2" minRow="1" maxRow="2" />
			</Animation>
		*/
	}
	else
	{
		// If the sprite is not animated then we only want to populate the VBO and IBO with one segment.
	}


	std::vector<Vertex> vertices;
	std::vector<unsigned short> indices;
	unsigned int currentIndex = 0;
	// Iterate over the image and fill up the frames.
	for(int i = 0; i < (numRows * numCols); i++)
	{
		// Convert the 1D index to 2D.
		unsigned int col = i % numCols;
		unsigned int row = i / numCols;

		// Find the min and max texture coordinates.
		float minX = (col * (float)frameWidth) / (float)tex.getSize().x;
		float minY = (row * (float)frameHeight) / (float)tex.getSize().y;
		float maxX = ((col * (float)frameWidth) + frameWidth) / (float)tex.getSize().x;
		float maxY = ((row * (float)frameHeight) + frameHeight) / (float)tex.getSize().y;

		Vertex v;
		v.pos = Vector3(0.0f, 0.0f, 0.0f);
		v.normal = Vector3(1.0f, 1.0f, 1.0f);
		v.col = Color(255, 255, 255, 255);
		v.texcoords = Vector2(minX, minY);
		vertices.push_back(v);

		v.pos = Vector3(frameWidth, 0.0f, 0.0f);
		v.normal = Vector3(1.0f, 1.0f, 1.0f);
		v.col = Color(255, 255, 255, 255);
		v.texcoords = Vector2(maxX, minY);
		vertices.push_back(v);

		v.pos = Vector3(frameWidth, frameHeight, 0.0f);
		v.normal = Vector3(1.0f, 1.0f, 1.0f);
		v.col = Color(255, 255, 255, 255);
		v.texcoords = Vector2(maxX, maxY);
		vertices.push_back(v);

		v.pos = Vector3(0.0f, frameHeight, 0.0f);
		v.normal = Vector3(1.0f, 1.0f, 1.0f);
		v.col = Color(255, 255, 255, 255);
		v.texcoords = Vector2(minX, maxY);
		vertices.push_back(v);

		unsigned int idx = currentIndex;
		indices.push_back(idx); indices.push_back(idx + 1); indices.push_back(idx + 2);
		indices.push_back(idx); indices.push_back(idx + 3); indices.push_back(idx + 2);
		currentIndex += 4;
	}

	vbo.SetData(vertices);
	ibo.SetData(indices);
}

void AnimatedSprite::Play(unsigned int inFps)
{
	// Reset the frame positions and allow for updating.
	currentCol = 0;
	currentRow = 0;
	isPlaying = true;

	// Set the new frame rate.
	fps = inFps;
}

void AnimatedSprite::Stop()
{
	// Reset the frame positions and disallow updating.
	currentRow = 0;
	currentCol = 0;
	isPlaying = false;
	isPaused = false;
}

void AnimatedSprite::Pause()
{
	// Keep the same frame positions and disallow updating.
	isPaused = true;
}

void AnimatedSprite::Unpause()
{
	// Resume on the same frame position and reallow updating.
	isPaused = false;
}

void AnimatedSprite::Update()
{
	// Screw updating if we don't need to.
	if(!isAnimated || !isPlaying || isPaused)
		return;

	if((frame - lastFrame) >= (1000.0f / (float)fps))
	{
		currentCol++;
		if(currentCol > maxCol)
		{
			currentRow++;
			currentCol = minCol;

			if(currentRow > maxRow)
				currentRow = minRow;
		}

		lastFrame = frame;
	}
	frame++;
}

void AnimatedSprite::SetAnimation(int inIndex)
{
	// If our index is larger than the amount of segments we have then don't do anything.
	if(inIndex > segments.size() - 1)
		return;

	auto it = segments.begin();
	for(int i = 0; i < inIndex; ++i)
		++it;
	AnimationSegment seg = it->second;
}

void AnimatedSprite::SetAnimation(const std::string& inName)
{
	auto it = segments.find(inName);

	if(it == segments.end())
		return;

	AnimationSegment seg = it->second;
	this->minCol = seg.minCol;
	this->maxCol = seg.maxCol;

	this->minRow = seg.minRow;
	this->maxRow = seg.maxRow;

	currentCol = minCol;
	currentRow = minRow;
}

void AnimatedSprite::Draw()
{
	sf::Texture::bind(&tex);
	// Draw the sprite via the indices and the offset.
	vbo.Bind();
	ibo.Bind();

	unsigned currentFrame = numCols * currentRow + currentCol;
	glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, (GLvoid*)((currentFrame * 6) * sizeof(unsigned short)));

	vbo.Unbind();
}