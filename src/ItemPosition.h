#pragma once


class ItemPosition final
{
public:
	const int width, height, dx, dy;

public:
	ItemPosition(const int width, const int height, const int dx, const int dy) :
		width(width), height(height), dx(dx), dy(dy)
	{}
	~ItemPosition() {}

	bool clicked(const int x, const int y) const {
		return x >= dx && x < dx + width &&
			y >= dy && y < dy + height;
	}
};
