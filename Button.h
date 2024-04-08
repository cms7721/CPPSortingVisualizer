#pragma once
#include "SDL.h"
#include "SDL_ttf.h"
#include <string>
#include <vector>
#include <iostream>
class Button {
public:
	Button(const int& x, const int& y, const int& sx, const int& sy, const std::string& label, SDL_Renderer* renderer, TTF_Font* font);

	int render(SDL_Renderer* renderer);
	SDL_Rect getRect() { return m_rect; }
	bool inRange(const int& x, const int& y);


private:
	SDL_Rect m_rect{};
	SDL_Texture* m_label{};
	SDL_Rect m_labelBox{};

};