#pragma once
#include "SDLFuncs.h"
#include <SDL.h>
#include <vector>


enum class Mode {
		SELECTION,
		BUBBLE,
		INSERTION,
		QUICK,
		NUM_SORTS,
};


//Function prototypes
int selection_sort(std::vector<SDL_Rect> arr, Pack* pack);
int bubble_sort(std::vector<SDL_Rect> arr, Pack* pack);
int insertion_sort(std::vector<SDL_Rect> arr, Pack* pack);
int quick_sort(std::vector<SDL_Rect> arr, Pack* pack);
