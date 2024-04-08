#include "Sort.h"
#include "SDLFuncs.h"
#include <SDL.h>
#include <vector>
#include <algorithm>

//Function for proper swapping of elements
void swap(SDL_Rect* a, SDL_Rect* b) {
	std::swap(a->h, b->h);
	std::swap(a->y, b->y);
}

int selection_sort(std::vector<SDL_Rect> arr, Pack* pack) {
	for (int i = 0; i < arr.size() - 1; i++) {
		int min = i;
		for (int j = i; j < arr.size(); j++) {
			if (visualizer(pack, arr, i, -1, min, j) < 0) return -1;
			if (arr[j].h < arr[min].h) {
				min = j;
			}
		}
		swap(&arr[i], &arr[min]);
	}
	visualizer(pack, arr, -1, -1, -1, -1, true);
	return 0;
}

int bubble_sort(std::vector<SDL_Rect> arr, Pack* pack) {
	for (int i = 0; i < arr.size() - 1; i++) {
		bool swapped = false;
		for (int j = 0; j < arr.size() - i - 1; j++) {
			if (visualizer(pack, arr, j, arr.size() - i) < 0) return -1;
			if (arr[j].h > arr[j + 1].h) {
				swapped = true;
				swap(&arr[j], &arr[j + 1]);
			}
		}
		if (!swapped) {
			visualizer(pack, arr, -1, -1, -1, -1, true);
			break;
		}
	}

	return 0;
}


int insertion_sort(std::vector<SDL_Rect> arr, Pack* pack) {
	int j{};
	int k{};
	int l{};
	for (int i = 1; i < arr.size(); i++) {
		k = arr[i].h;
		l = arr[i].y;
		j = i - 1;
		while (j > -1 && arr[j].h > k) {
			if (visualizer(pack, arr, i, -1, j, j + 1) < 0) return -1;
			swap(&arr[j + 1], &arr[j]);
			j--;
		}
		arr[j + 1].h = k;
		arr[j + 1].y = l;
	}
	visualizer(pack, arr, -1, -1, -1, -1, true);
	return 0;
}

//Quick Sort helper algorithmis
int partition(std::vector<SDL_Rect>* arr, Pack* pack, int low, int high) {
	int p = (*arr)[((high - low) / 2) + low].h;
	int i = low - 1;
	int j = high + 1;
	while (true) {
		do {
			++i;
			if (visualizer(pack, *arr, ((high - low) / 2) + low, -1, i, j) < 0) return -1;
		} while ((*arr)[i].h < p);
		do {
			--j;
			if (visualizer(pack, *arr, ((high - low) / 2) + low, -1, i, j) < 0) return -1;
		} while ((*arr)[j].h > p);
		if (i >= j) {
			return j;
		}
		swap(&((*arr)[i]), &((*arr)[j]));
	}
}
int qsort(std::vector<SDL_Rect>* arr, Pack* pack, int low, int high) {
	if (low >= 0 && high >= 0 && low < high) {
		int p = partition(arr, pack, low, high);
		if (p < 0) return -1;
		if (qsort(arr, pack, low, p) < 0) return -1;
		if (qsort(arr, pack, p + 1, high) < 0) return -1;
	}
	return 0;
}

int quick_sort(std::vector<SDL_Rect> arr, Pack* pack) {
	if (qsort(&arr, pack, 0, arr.size() - 1) < 0) return -1;
	if (visualizer(pack, arr, -1, -1, -1, -1, true) < 0) return -1;
	return 0;
}
