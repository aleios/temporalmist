#ifndef COLOR_HPP
#define COLOR_HPP

class Color
{
public:
	Color(unsigned char r = 255, unsigned char g = 255, unsigned char b = 255, unsigned char a = 255)
		: r(r), g(g), b(b), a(a)
	{
	}

	unsigned char R()
	{
		return r;
	}

	unsigned char G()
	{
		return g;
	}

	unsigned char B()
	{
		return b;
	}

	unsigned char A()
	{
		return a;
	}

	unsigned char r, g, b, a;
};

#endif