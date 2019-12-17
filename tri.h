#ifndef H_TRI
#define H_TRI

#include <stdio.h>
#include <stdlib.h>
#include <SDL/SDL.h>
#include <SDL/SDL_keysym.h>


#define HEIGHT 512
#define WIDTH 512

SDL_Surface **tabrect;
SDL_Rect *tabpos;
SDL_Surface *ecran = NULL;
int maxi;

void boucle();
void dessine(int tab[], int n);
void dessine_ecran(int tab[], int n);
void tri_vision(int tab[], int n, int (*comp)(int, int));
void affichetab(int tab[], int n);

#endif