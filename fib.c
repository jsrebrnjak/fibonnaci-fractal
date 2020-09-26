/*Assignment 4: Question 1
 * Filename: fib.c
 * By Justina Srebrnjak (400189506, srebrnjj)*/

#include "bmp.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* concatWord(char* part1, char* part2) {
	char *word;
	word = malloc(strlen(part1) + strlen(part2) + 1);
	if (word == NULL) return NULL;
	strcpy(word, part1);
	strcat(word, part2);
	return word;
}

char* findFibWord(int n) {
	if (n == 1) return "1";
	if (n == 2) return "0";
	return concatWord(findFibWord(n-1), findFibWord(n-2));
}

int fib(int n, int x, int y, int step, RGB bc, RGB fc, int w, int h, RGB* image) {
	char* fibWord = findFibWord(n);
	long int lengthOfWord = strlen(fibWord);
	char direction = 'U';
	
	int i;
	for (i = 0; i < w*h; i++) {
		image[i].r = bc.r;
		image[i].g = bc.g;
		image[i].b = bc.b;
	}

	int j, k;
	for (j = 1; j <= lengthOfWord; j++) {
		switch(direction) {
			case 'U':
				if (x < 0 || x >= w || y < 0 || y >= h) return 0;
				for (i = 0; i < step; i++) {
					k = (x+i)*w + y;
					image[k].r = fc.r;
					image[k].g = fc.g;
					image[k].b = fc.b;
				}
				x += step;
				break;
			case 'D':
				if (x < 0 || x >= w || y < 0 || y >= h) return 0;
				for (i = 0; i < step; i++) {
					k = (x-i)*w + y;
					image[k].r = fc.r;
					image[k].g = fc.g;
					image[k].b = fc.b;
				}
				x -= step;
				break;
			case 'L':
				if (x < 0 || x >= w || y < 0 || y >= h) return 0;
				for (i = 0; i < step; i++) {
					k = x*w + (y-i);
					image[k].r = fc.r;
					image[k].g = fc.g;
					image[k].b = fc.b;
				}
				y -= step;
				break;
			case 'R':
				if (x < 0 || x >= w || y < 0 || y >= h) return 0;
				for (i = 0; i < step; i++) {
					k = x*w + (y+i);
					image[k].r = fc.r;
					image[k].g = fc.g;
					image[k].b = fc.b;
				}
				y += step;
				break;
		}

		char character = (char)fibWord[j-1];
		if (character == '0') {
			if (j % 2 == 0) {
				switch(direction) {
					case 'U':
						direction = 'L';
						break;
					case 'D':
						direction = 'R';
						break;
					case 'L':
						direction = 'D';
						break;
					case 'R':
						direction = 'U';
						break;
				}
			} else {
				switch(direction) {
					case 'U':
						direction = 'R';
						break;
					case 'D':
						direction = 'L';
						break;
					case 'L':
						direction = 'U';
						break;
					case 'R':
						direction = 'D';
						break;
				}
			}
		}
	}
	free(fibWord);
	return lengthOfWord;
}
