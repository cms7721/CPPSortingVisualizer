#include "Button.h"
#include "mmlib/SDL2-2.28.5/include/SDL.h"
#include "mmlib/SDL2_ttf-2.20.2/include/SDL_ttf.h"
#include <string>

Button::Button(const int& x, const int& y, const int& sx, const int& sy, const std::string& label, SDL_Renderer* renderer, TTF_Font* font)
	: m_rect{x, y, sx, sy}

{//TODO enforce invariants (such as pos and size must be > 0
	int textWidth{};
	int textHeight{};
	TTF_SizeText(font, label.c_str(), &textWidth, &textHeight);
	SDL_Surface* t{ TTF_RenderText_Blended(font, label.c_str(), SDL_Color{0xFF, 0xFF, 0xFF, 0xFF}) };
	m_label = SDL_CreateTextureFromSurface(renderer, t);
	m_labelBox = SDL_Rect{ x + ((sx - textWidth) / 2), y + ((sy - textHeight) / 2), t->w, t->h };
	SDL_FreeSurface(t);
};

int Button::render(SDL_Renderer* renderer) {
	SDL_SetRenderDrawColor(renderer, 0XFF, 0xFF, 0xFF, 0xFF);
	SDL_RenderDrawRect(renderer, &m_rect);
	SDL_RenderCopy(renderer, m_label, nullptr, &m_labelBox);
	return 0;
}

bool Button::inRange(const int& x, const int& y) {
	if (x >= m_rect.x && x <= m_rect.x + m_rect.w && y >= m_rect.y and y <= m_rect.y + m_rect.h) {
		return true;
	}
	else {
		return false;
	}
}