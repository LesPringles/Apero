#include "../includes/display.h"
#include "../sources/tracing.c"
#include "../includes/filtre.h"


void set_filtre (t_display *display, int x, int y, filtre f)
{


    int taille = 1;
    Uint8 r, r1, g, g1, b, b1 = 0;
    int somme = 0;
    SDL_LockSurface(display->screen);
    for(int x = 0; y < WINX; x++)
    {
        for(int y = 0; y < WINY; y++) //application à tous les pixels
        {
            for(int a = -f->taille; a <= f->taille; a++)
            {

                if(x+a < 0)||(x+a > WINX) // aucun dépassement gauche/droite
                {
                    for(int b = -f->taille; b <= f->taille; b++)
                    {
                        if(y+b < 0)||(y+b > WINY) // aucun dépassement haut/bas
                        {
                            pixel = (x+a)+ WINX * (y+b);
                            SDL_GetRGB(pixel, display->screen->format, &r1, &g1, &b1);
                            r = r + r1*f->coef;
                            g = g+ g1*f->coef;
                            b = b + b1*f->coef;
                            somme = somme + f->coef;
                        }
                    }
                }
            }
            if (somme != 0)
            {
                r = r /somme;
                g = g /somme;
                b = b /somme;
            }

            // tampon pour les valeurs en dehors de l'ensemble[0;255]
            if (r < 0)
            {
                r = 0;
            }
            if (r > 255)
            {
                r = 255;
            }
            if (g < 0)
            {
                g = 0;
            }
            if (g > 255)
            {
                g = 255;
            }
            if (b < 0)
            {
                b = 0;
            }
            if (b > 255)
            {
                b = 255;
            }


            x + WINX * y = SDL_MapRGB(display->screen->format, r, g, b); // changement du pixel

        }
    }

    SDL_UnlockSurface(display->screen);
}
