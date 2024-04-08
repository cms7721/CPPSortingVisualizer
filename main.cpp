#include "SDLFuncs.h"
#include "Constants.h"
#include "Sort.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <iostream>
#include <vector>
#include <string>


int main(int argc, char* argv[]) {
	//SDL tools
	SDL_Window* window{ nullptr };
	SDL_Renderer* renderer{ nullptr };
	SDL_Surface* screen_surface{ nullptr };
	SDL_Event e{};
	Pack pack{};

	//Main Loop exit flag
	bool quit = false;

	//Choose which algorithm
	int x{};
	std::cout << "Sorting algorithm: ";
	std::cin >> x;
	Mode mode = static_cast<Mode>(x);

	//Rectangle dimensions
	int RECT_NUM =  get_num_rects();
	if (RECT_NUM < 0) {
		return -1;
	}
	int width{ SCREEN_WIDTH / RECT_NUM };
	int height{ SCREEN_HEIGHT / RECT_NUM };

	//Initialize window
	if (!init(&window, &renderer)) {
		return -1;
	}
	screen_surface = SDL_GetWindowSurface(window);
	SDL_FillRect(screen_surface, nullptr, SDL_MapRGB(screen_surface->format, 0x00, 0x00, 0x00));
	SDL_UpdateWindowSurface(window);
	SDL_RenderClear(renderer);

	//Initialize textbox
	TTF_Font* font = TTF_OpenFont("mmlib/Bitstream-Vera-Sans/Vera.ttf", 16);
	if (!font) {
		std::cerr << "Failed to load font: " << TTF_GetError() << std::endl;
		return -1;
	}
	std::string str{};

	switch (mode) {
	case Mode::SELECTION:
		str = "Selection Sort ";
		break;
	case Mode::BUBBLE:
		str = "Bubble Sort ";
		break;
	case Mode::INSERTION:
		str = "Insertion Sort ";
		break;
	case Mode::QUICK:
		str = "Quick Sort ";
		break;
	default:
		std::cerr << "Algorithm not found";
		return -1;
	}
	int w{};
	TTF_SizeText(font, str.c_str(), &w, nullptr);
	str += "n=" + std::to_string(RECT_NUM);
	SDL_Surface* text = TTF_RenderText_Blended_Wrapped(font, str.c_str(), SDL_Color{0xFF, 0xFF, 0xFF, 0xFF}, w);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, text);
	SDL_Rect text_box{ 10, 0, text->w, text->h };
	SDL_FreeSurface(text);
	pack.renderer = renderer;
	pack.text = texture;
	pack.text_box = text_box;



	//Draw rectangles from generated array
	std::vector<SDL_Rect> arr = generate_array(width, height, RECT_NUM);
	SDL_SetRenderDrawColor(renderer, 0xFF, 0xFF, 0xFF, 0xFF);
	if (SDL_RenderFillRects(renderer, arr.data(), RECT_NUM) < 0) {
		std::cerr << "Failed to render Rectangles: " << SDL_GetError();
		return -1;
	}

	//Main loop
	switch (mode) {
	case Mode::SELECTION:
		if (selection_sort(arr, &pack) < 0) quit = true;
		break;
	case Mode::BUBBLE:
		if (bubble_sort(arr, &pack) < 0) quit = true;
		break;
	case Mode::INSERTION:
		if (insertion_sort(arr, &pack) < 0) quit = true;
		break;
	case Mode::QUICK:
		if (quick_sort(arr, &pack) < 0) quit = true;
		break;
	default:
		std::cerr << "Algorithm not found";
		return -1;
		break;
	}
	while (!quit) {
		if (event_handle(e) < 0) quit = true;
	}
	close(&window, &renderer);
	return 0;

}