#include "gfx.h"
#include <stdio.h>
#include <stdlib.h>
//Cauê Mendonça Magela do Ó
//rgm : 43558

struct Lseo
{
    int valor;
    struct Lseo *prox;
};
void inserir(int qual, int x, struct Lseo **ant, struct Lseo **ptr){
    struct Lseo *pt = malloc(sizeof(struct Lseo));
    pt->valor = x;
    switch (qual) {
        case 0:
            pt->prox = *ptr;
            *ptr = pt;
            return;
        case 1:
            pt->prox = *ptr;
            *ant = pt;
            return;
        case 2:
            pt->prox = NULL;
            *ant = pt;
        default:
            return;
    }
}
int main()
{
    char string[50];
    int valor, resp, contr, width, height, textwidth, textheight;
    struct Lseo *ant;
    struct Lseo *ptr;
    struct Lseo *prox;
    struct Lseo *ptlista = NULL;
    struct Lseo *pt = NULL;
    struct Lseo *desalocar = NULL;
    gfx_init(1280, 720, "Lista simplesmente encadeada");
    gfx_set_color(255, 255, 255);
    do {
        printf("1-Busca\n2-insercao\n3-remocao\n4-sair\n");
        scanf("%d", &resp);


        switch (resp) {
            case 1:
                printf("Informe o numero que sera buscado\n");
                scanf("%d", &valor);
                contr = 0;
                pt = ptlista;
                while ((pt != NULL) && (contr == 0)){
                    if(pt->valor == valor){
                        contr = 1;
                        printf("O valor esta na lista\n");
                    }
                    pt = pt->prox;
                }
                if(contr == 0){
                    printf("O valor nao esta na lista\n");
                }
                break;
            case 2:
                printf("Informe o numero que sera inserido\n");
                scanf("%d", &valor);
                contr = 0;
                if (ptlista == NULL) {
                    contr = 1;
                    inserir(0, valor, NULL, &ptlista);
                } else {
                    pt = ptlista;
                    if ((pt->valor > valor)) {
                        contr = 1;
                        inserir(0, valor, NULL, &ptlista);
                    } else {
                        if(pt->prox == NULL){
                            contr = 1;
                            inserir(2, valor, &ant, NULL);
                            pt->prox = ant;
                        }else {
                            while ((pt != NULL) && (contr == 0)) {
                                if (pt->prox != NULL) {
                                    prox = pt->prox;
                                }
                                if (pt->valor == valor) {
                                    contr = 1;
                                    printf("Valor ja esta na lista\n");
                                    break;
                                } else {
                                    if (pt->valor < valor) {
                                        if (prox->valor > valor) {
                                            inserir(1, valor, &ant, &prox);
                                            pt->prox = ant;
                                        } else {
                                            ptr = pt;
                                            pt = pt->prox;
                                        }
                                    } else {
                                        ptr = pt;
                                        pt = pt->prox;
                                    }
                                }
                            }
                        }
                        if(contr == 0){
                            inserir(2, valor, &ant, NULL);
                            ptr->prox = ant;
                        }
                    }
                }
                break;
            case 3:
                printf("Informe o numero que sera removido\n");
                scanf("%d", &valor);
                contr = 0;
                ant = NULL;
                pt = ptlista;
                while ((pt != NULL) && (contr == 0)){
                    if(pt->valor == valor){
                        contr = 1;
                        ant->prox = pt->prox;
                        free(pt);
                    }else {
                        ant = pt;
                        pt = pt->prox;
                    }
                }
                if(contr == 0){
                    printf("O valor nao esta na lista\n");
                }
        }
        gfx_clear();
        width = 0;
        height = 0;
    	pt = ptlista;
    	while (pt != NULL){
    	    if(pt->prox != NULL){
    	        sprintf(string, "%d -> ", pt->valor);
    	    }else{
    	        sprintf(string, "%d ", pt->valor);
    	    }
    	    gfx_get_text_size(string, &textwidth, &textheight);
    	    if(width+textwidth <= 1280){
    	        gfx_text(width, height, string);
    	        width += textwidth;
    	    }else{
    	        height += textheight;
    	        gfx_text(0, height, string);
    	        width = textwidth;
    	    }
            pt = pt->prox;
    	}    
        gfx_paint();

    }while(resp != 4);
    pt = ptlista;
    while (pt != NULL){
        desalocar = pt;
        pt = pt->prox;
        free(desalocar);
    }
    gfx_quit();


    return 0;
}
