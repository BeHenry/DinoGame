#include "Asset.h"
Asset::Asset(std::vector<SDL_Rect> info, SDL_Texture* text, int type, int anime)
{
	id = type;
	pos = info;
	assets_base = text;
	animationOffset = anime;
}
Asset::Asset(SDL_Rect info, SDL_Texture* text, int type)
{
	id = type;
	pos.push_back(info);
	assets_base = text;
	animationOffset = 1;
}
Asset::~Asset()
{
	
}
void Asset::addAnimationFrame(SDL_Rect info)
{
	pos.push_back(info);
	animationOffset +=1;
}
void Asset::setAnimationOffset(int i)
{
	animationOffset = i;
}
SDL_Rect* Asset::getRect(int i)
{
	int n = pos.size();
	int m = (i/animationOffset) % n;
	
	return &pos[m];
}
int Asset::getType()
{
	return id;
}
SDL_Texture* Asset::getTexture()
{
	return assets_base;
}
