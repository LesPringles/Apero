#ifndef FILTRE_H_INCLUDED
#define FILTRE_H_INCLUDED


typedef struct	filtre filtre;
struct filtre
{
    int taille;
    int[2*taille+1][2*taille+1] coef;
};

static const filtre flou =
{
    filtre f;
    f->taille = 1;
    f->coef =
    {{1, 1, 1},
     {1, 1, 1},
     {1, 1, 1}};
}

static const filtre flou_gaussien =
{
    filtre f;
    f->taile = 2;
    f->coef =
    {{1, 4, 7, 4, 1},
     {4, 16, 26, 16, 4},
     {7, 26, 41, 26, 7},
     {4, 16, 26, 16, 4},
     {1, 4, 7, 4, 1}};
}

static const filtre detec_v =
{
    filtre f;
    f->taille = 1;
    f->coef =
    {{-1, 0, 1},
     {-1, 0, 1},
     {-1, 0, 1}};
}

static const filtre detec_h =
{
    filtre f;
    f->taille = 1;
    f->coef =
    {{-1, -1, -1},
     {0, 0, 0},
     {1, 1, 1}};
}



#endif // FILTRE_H_INCLUDED
