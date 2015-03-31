#ifndef COULEURS_H_
# define COULEURS_H_

# include <SDL/SDL.h>

enum {
  C_NOIR = 0, C_BLEU_FONCE, C_VERT_FONCE, C_CYAN_FONCE, C_ROUGE_FONCE,
  C_MAGENTA_FONCE, C_OCRE, C_GRIS_CLAIR, C_GRIS, C_BLEU, C_VERT,
  C_CYAN, C_ROUGE, C_MAGENTA, C_JAUNE, C_BLANC,

  NB_COULEURS
};


SDL_Surface* pixel;
Uint32 couleurs[NB_COULEURS];

void initCouleurs(void)
{
  couleurs[C_NOIR]          = SDL_MapRGB(pixel->format, 0x00, 0x00, 0x00);
  couleurs[C_BLEU_FONCE]    = SDL_MapRGB(pixel->format, 0x00, 0x00, 0x80);
  couleurs[C_VERT_FONCE]    = SDL_MapRGB(pixel->format, 0x00, 0x80, 0x00);
  couleurs[C_CYAN_FONCE]    = SDL_MapRGB(pixel->format, 0x00, 0x80, 0x80);
  couleurs[C_ROUGE_FONCE]   = SDL_MapRGB(pixel->format, 0x80, 0x00, 0x00);
  couleurs[C_MAGENTA_FONCE] = SDL_MapRGB(pixel->format, 0x80, 0x00, 0x80);
  couleurs[C_OCRE]          = SDL_MapRGB(pixel->format, 0x80, 0x80, 0x00);
  couleurs[C_GRIS_CLAIR]    = SDL_MapRGB(pixel->format, 0xC0, 0xC0, 0xC0);
  couleurs[C_GRIS]          = SDL_MapRGB(pixel->format, 0x80, 0x80, 0x80);
  couleurs[C_BLEU]          = SDL_MapRGB(pixel->format, 0x00, 0x00, 0xFF);
  couleurs[C_VERT]          = SDL_MapRGB(pixel->format, 0x00, 0xFF, 0x00);
  couleurs[C_CYAN]          = SDL_MapRGB(pixel->format, 0x00, 0xFF, 0xFF);
  couleurs[C_ROUGE]         = SDL_MapRGB(pixel->format, 0xFF, 0x00, 0x00);
  couleurs[C_MAGENTA]       = SDL_MapRGB(pixel->format, 0xFF, 0x00, 0xFF);
  couleurs[C_JAUNE]         = SDL_MapRGB(pixel->format, 255, 255, 0);
  couleurs[C_BLANC]         = SDL_MapRGB(pixel->format, 255, 255, 255);
}

#endif /* !COULEURS_H_ */
