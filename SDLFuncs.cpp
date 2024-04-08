#include "Constants.h"
#include "SDLFuncs.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <random>
#include <chrono>
#include <iostream>
#include <string>

bool init(SDL_Window** window, SDL_Renderer** renderer) {
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cerr << "Failed to initialize SDL: " << SDL_GetError() << std::endl;
		return false;
	}

	if (TTF_Init() < 0) {
		std::cerr << "Failed to initialize TTF: " << TTF_GetError() << std::endl;
		return false;
	}

	*window = SDL_CreateWindow("Sorting Visualizer", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (!window) {
		std::cerr << "Failed to create Window: " << SDL_GetError() << std::endl;
		SDL_Quit();
		return false;
	}
	SDL_RaiseWindow(*window);

	*renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		std::cerr << "Failed to create renderer: " << SDL_GetError() << std::endl;
		SDL_DestroyWindow(*window);
		SDL_Quit();
		return false;
	}

	return true;
}


void close(SDL_Window** window, SDL_Renderer** renderer) {
	SDL_DestroyWindow(*window);
	SDL_DestroyRenderer(*renderer);
	SDL_Quit();
}

int get_num_rects() {
	int x{};
	std::cout << "Number of elements: ";
	std::cin >> x;
	if (x > SCREEN_HEIGHT || x > SCREEN_WIDTH) {
		std::cerr << "ERROR: Number of elements greater than Window dimensions" << std::endl;
		return -1;
	}
	return x;
}

std::vector<SDL_Rect> generate_array(int width, int height, int l) {
	std::vector<int> arr{};
	std::vector<SDL_Rect> rects{};
	for (int i = 0; i < l; i++) {
		arr.push_back(i+1);
	}

	unsigned int seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::shuffle(arr.begin(), arr.end(), std::default_random_engine(seed));

	for (int i = 0; i < l; i++) {
		rects.push_back(SDL_Rect{ i * width, SCREEN_HEIGHT - arr[i] * height, width, arr[i] * height });
	}

	return rects;
}

int event_handle(SDL_Event e) {
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			return -1;
			break;
		case SDL_MOUSEBUTTONDOWN:
			while (!SDL_PollEvent(&e) || e.type != SDL_MOUSEBUTTONUP) {
				SDL_Delay(50);
			}
			break;
		}
	}
}


int visualizer(Pack* pack, std::vector<SDL_Rect> arr, int cur, int max, int pre, int post, bool complete) {
	SDL_SetRenderDrawColor(pack->renderer, 0x00, 0x00, 0x00, 0xFF);
	SDL_RenderClear(pack->renderer);
	SDL_Event e{};
	SDL_RenderCopy(pack->renderer, pack->text, nullptr, &pack->text_box);

	if (max == -1) max = arr.size();
	//Run Completed animaiton
	if (complete) {
		SDL_SetRenderDrawColor(pack->renderer, 0x00, 0xFF, 0x00, 0xFF);
		for (int i = 0; i < arr.size(); i++) {
			for (int j = 0; j < arr.size(); j++) {
				if (event_handle(e) < 0) return -1;
				if (j > i) {
					SDL_SetRenderDrawColor(pack->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
				}
				else {
					SDL_SetRenderDrawColor(pack->renderer, 0x00, 0xFF, 0x00, 0xFF);
				}
				SDL_RenderFillRect(pack->renderer, &arr[j]);
			}
			SDL_RenderPresent(pack->renderer);
			SDL_Delay(100/arr.size());
		}
	}

	//Animate current step
	else {
		for (int i = 0; i < arr.size(); i++) {
			if (event_handle(e) < 0) {
					return -1;
				}
			if (i == cur) {
				SDL_SetRenderDrawColor(pack->renderer, 0xFF, 0x00, 0xFF, 0xFF);
			}
			else if (i == pre) {
				SDL_SetRenderDrawColor(pack->renderer, 0xFF, 0x00, 0x00, 0xFF);
			}
			else if (i == post) {
				SDL_SetRenderDrawColor(pack->renderer, 0x00, 0x00, 0xFF, 0xFF);
			}
			else {
				SDL_SetRenderDrawColor(pack->renderer, 0xFF, 0xFF, 0xFF, 0xFF);
			}
			SDL_RenderFillRect(pack->renderer, &arr[i]);
		}
		SDL_RenderPresent(pack->renderer);
		SDL_Delay(300 / arr.size());
	}

	return 0;
}
