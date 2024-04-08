#pragma once
#include "Button.h"
#include "SDLFuncs.h"
#include <string>
#include <vector>

class Menu {
public:
	Menu(const std::string& title, std::vector<std::string> labels, SDL_Renderer* renderer, TTF_Font* font);
	int render(SDL_Renderer* renderer);
	void buttonPress(const int& x, const int& y, std::vector<SDL_Rect> arr, Pack* pack);
	void buttonHover(const int& x, const int& y);

private:
	SDL_Texture* m_title{};
	SDL_Rect m_titleBox{};
	std::vector<Button> m_buttons{};
};