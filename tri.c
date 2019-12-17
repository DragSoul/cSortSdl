#include "tri.h"


/*****************************************************************/
int comp1(int a, int b){
    if(a == b)return 0;
    if(a<b)return -1;
    return 1;
}

int comp2(int a, int b){
    if(a == b)return 0;
    if(a>b)return -1;
    return 1;
}

int comp3(int a, int b){
    if(a%2 == b%2)return 0;
    if(a%2<b%2)return 1;
    return -1;
}


int maximum(int tab[], int n){
    int max = 0;
    for(int i = 0; i < n; i++){
        if(tab[i] > max) max = tab[i];
    }
    return max;
}

/****************************************************************/

//utilisé pour arreter le programme à un moment précis
void boucle(){
    int count = 1;
    SDL_Event event;
    while(count){
        SDL_WaitEvent(&event);
        switch(event.type){
            case SDL_QUIT:
                exit(1);
            case SDL_KEYDOWN:
                case SDLK_SPACE:
                    count = 0;
        }
    }
}

//fonction qui colorie les deux élements qu'on compare
void colorie(int tab[], int i, int j){
    SDL_FillRect(tabrect[i], NULL, SDL_MapRGB(tabrect[i]->format, 0, 255, 0));
    SDL_FillRect(tabrect[j], NULL, SDL_MapRGB(tabrect[j]->format, 0, 255, 0));
    SDL_BlitSurface(tabrect[i], NULL, ecran, &tabpos[i]);
    SDL_BlitSurface(tabrect[j], NULL, ecran, &tabpos[j]);
    SDL_Flip(ecran);
}

//fonction d'update
void dessine(int tab[], int n){
    SDL_FillRect(ecran, NULL,SDL_MapRGB(ecran->format, 0, 0, 0));
    SDL_Flip(ecran);
    for(int i = 0; i < n; i++){
        tabpos[i].x = i*(WIDTH/n);
        tabpos[i].y = HEIGHT-tab[i]*(HEIGHT/maxi);
        SDL_FillRect(tabrect[i], NULL, SDL_MapRGB(tabrect[i]->format, 255, 255, 255));
        SDL_BlitSurface(tabrect[i], NULL, ecran, &tabpos[i]);
    }
    SDL_Flip(ecran);
}

//fonction d'initialisation de l'écran
void dessine_ecran(int tab[], int n){
    if(SDL_Init(SDL_INIT_VIDEO) != 0){
        fprintf(stderr,"\nUnable to initialize SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }
    if((ecran = SDL_SetVideoMode(WIDTH,HEIGHT,32, SDL_HWSURFACE)) == NULL){
        fprintf(stderr,"Erreur VideoMode %s\n",SDL_GetError());
        exit(EXIT_FAILURE);
    }
    tabpos = malloc(sizeof(SDL_Rect)*n);
    tabrect = malloc(sizeof(SDL_Surface*)*n);
    for (int i = 0; i < n; i++){
        tabrect[i] = SDL_CreateRGBSurface(SDL_HWSURFACE, WIDTH/n, tab[i]*(HEIGHT/maxi), 32, 0, 0, 0, 0);
        SDL_FillRect(tabrect[i], NULL, SDL_MapRGB(tabrect[i]->format, 255, 255, 255));
        tabpos[i].x = i*(WIDTH/n);
        tabpos[i].y = HEIGHT-tab[i]*(HEIGHT/maxi);
        SDL_BlitSurface(tabrect[i], NULL, ecran, &tabpos[i]);
    }
}

//fonction de tri random
void tri_vision(int tab[], int n, int (*comp)(int, int)){
    int x, tmp;
    SDL_Surface *tmpr;
    for (int i = 1; i < n; i++){
        for(int j = i; j > 0; j--){
            if(comp(tab[j], tab[j-1]) == -1){
                colorie(tab, j-1, j);
                boucle();

                tmp = tab[j];
                tab[j] = tab[j-1];
                tab[j-1] = tmp;

                //même échange dans le tableau de surfaces
                tmpr = tabrect[j];
                tabrect[j] = tabrect[j-1];
                tabrect[j-1] = tmpr;

                dessine(tab, n);
                boucle();
            }
        }
    }
}

//affiche un tableau d'entier dans la console
void affichetab(int tab[], int n){
    for(int i = 0; i < n; i++){
        printf("%d ", tab[i]);
    }
    printf("\n");
}


int main(int argc, char ** argv){
    int tab[10] = {5,7,3,1,8,6,10,9,2,4}, n = 10;
    maxi = maximum(tab, n);
    
    dessine_ecran(tab, n);
    boucle();

    tri_vision(tab, n, &comp1);
    boucle();

    SDL_Quit();
    return 0;
}