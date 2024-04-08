#pragma once
#include <SDL.h>
#include <SDL_ttf.h>
#include <vector>
#include <string>


//Animation package for simpler argument passing
struct Pack {
	SDL_Renderer* renderer{};
	SDL_Texture* text{};
	SDL_Rect text_box{};
};

//Function Prototypes
bool init(SDL_Window** window, SDL_Renderer** renderer);
int get_num_rects();
void close(SDL_Window** window, SDL_Renderer** renderer);
std::vector<SDL_Rect> generate_array(int width, int height, int l);
int event_handle(SDL_Event e);
int visualizer(Pack* pack, std::vector<SDL_Rect> arr, int cur = -1, int max = -1, int pre = -1, int post = -1, bool complete = false);
