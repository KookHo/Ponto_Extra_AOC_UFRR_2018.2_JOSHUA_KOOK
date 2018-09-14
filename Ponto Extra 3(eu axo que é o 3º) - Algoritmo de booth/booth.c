#include <stdio.h>
#include <stdlib.h>
#include <math.h>


/*entrada em binarios

dois vetores de 4 posiçoes, vetores para o produto e o multiplicando.

int vLeft[4];
int vRight[4];

A = multiplicando nos 4 bits da esquerda;
S = -multiplicando em notação complemento à 2 nos 4 bits da esquerda;
P = multiplicador nos 4 bits da direita;

inteiro 0 ou 1 para complementar o P;

se 0 0 : apenas faz o shift para a direita;
se 0 1: P + A e shift;
se 1 0: P + S e shift;
se 1 1: apenas shift;

Obs.: sempre repetir o primeiro bit da esquerda do produto apos o shift(devido ao sinal)

*/
int m, n, binMultiplicando, binMultiplicador;
int multiplicando[4], multiplicador[4], inverso[4], b = 0;

int vRight[4] = {0};
int vLeft[4] = {0};

void shiftBits(){
    b = vRight[3];
    vRight[3] = vRight[2];
    vRight[2] = vRight[1];
    vRight[1] = vRight[0];
    vRight[0] = vLeft[3];
    vLeft[3] = vLeft[2];
    vLeft[2] = vLeft[1];
    vLeft[1] = vLeft[0];
}

void printBin(){
    printf("\nProduto: %d %d %d %d   ", vLeft[0], vLeft[1], vLeft[2],vLeft[3]);
    printf(" %d %d %d %d - %d\n\n\n", vRight[0], vRight[1], vRight[2],vRight[3],b);
}

int decToBin(int dec){
    if (dec == 0){
        return 0;
    }else{
        return (dec % 2 + 10 * decToBin(dec / 2));
    }
}

void complemento(int * a){
    int j;
    for(j=0; j<4; j++){
        if(a[j]==0){
            inverso[j] = 1;
        }else if (a[j] == 1){
            inverso[j] = 0;
        }
    }

    if (inverso[3] == 1){
        inverso[3] = 0;
        if(inverso[2] == 1){
            inverso[2] = 0;
            if(inverso[1] == 1){
                inverso[1] = 0;
                if(inverso[0] == 1){
                    inverso[0] = 0;
                }else{
                    inverso[0] = 1;
                }
            }else{
                inverso[1] = 1;
            }
        }else{
            inverso[2] = 1;
        }
    }else{
        inverso[3] = 1;
    }
}


void produtoPosNeg(){
    int i;
    for(i=3; i>=0; i--){
        if(vRight[i] == 1){
            vRight[i] = 0;
        }else{
            vRight[i] = 1;
        }
        if(vLeft[i] == 1){
            vLeft[i] = 0;
        }else{
            vLeft[i] = 1;
        }
    }


    if (vRight[3] == 1){
        vRight[3] = 0;
        if(vRight[2] == 1){
            vRight[2] = 0;
            if(vRight[1] == 1){
                vRight[1] = 0;
                if(vRight[0] == 1){
                    vRight[0] = 0;
                    if(vLeft[3] == 1){
                        vLeft[3] = 0;
                        if(vLeft[2] == 1){
                            vLeft[2] = 0;
                            if(vLeft[1] == 1){
                                vLeft[1] = 0;
                                if(vLeft[0] == 1){
                                    vLeft[0] = 0;
                                }else{
                                    vLeft[0] = 1;
                                }
                            }else{
                                vLeft[1] = 1;
                            }
                        }else{
                            vLeft[2] = 1;
                        }
                    }else{
                        vLeft[3] = 1;
                    }
                }else{
                    vRight[0] = 1;
                }
            }else{
                vRight[1] = 1;
            }
        }else{
            vRight[2] = 1;
        }
    }else{
        vRight[3] = 1;
    }

}

int main(){
    scanf("%d", &m);
    scanf("%d", &n);

    binMultiplicando = decToBin(abs(m));
    binMultiplicador = decToBin(abs(n));

    int i,j;
    for(i=3; i>=0; i--){
        multiplicando[i] = binMultiplicando%10;
        vRight[i]= binMultiplicador%10;
        binMultiplicando = binMultiplicando/10;
        binMultiplicador = binMultiplicador/10;
    }

    complemento(multiplicando);

    printf("Multiplicando: %d %d %d %d \n", multiplicando[0], multiplicando[1], multiplicando[2],multiplicando[3]);
    printf("Produto/multiplicador: %d %d %d %d \n", vRight[0], vRight[1], vRight[2],vRight[3]);
    printf("Negativo do multiplicando: %d %d %d %d \n\n\n", inverso[0], inverso[1], inverso[2],inverso[3]);

    for(i=0; i<4;i++){


        if((b == 0 && vRight[3] == 0)||(b==1 && vRight[3] == 1)){



           shiftBits();



        }else if(vRight[3] == 1 && b==0){



            int j, carryIn = 0;
            for(j=3; j>=0;j--){
                if(vLeft[j] == 0 && inverso[j] == 0){

                    if(carryIn == 1){
                        vLeft[j] = 1;
                        carryIn = 0;
                    }else{
                        vLeft[j] = 0;
                        carryIn = 0;
                    }
                }else if((vLeft[j] == 1 && inverso[i] == 0)||(vLeft[j] == 0 && inverso[j] == 1)){

                    if(carryIn == 1){
                        vLeft[j] = 0;
                        carryIn = 1;
                    }else{
                        vLeft[j] = 1;
                        carryIn = 0;
                    }
                }else if (vLeft[j] == 1 && inverso[j] == 1){

                    if(carryIn == 1){
                        vLeft[j] = 1;
                        carryIn = 1;
                    }else{
                        vLeft[j] = 0;
                        carryIn = 1;
                    }
                }
            }

            shiftBits();



        }else if(vRight[3] == 0 && b==1){


            int j;
            int carryIn = 0;
            for(j=3; j>=0; j--){
                if(vLeft[j] == 0 && multiplicando[j] == 0){

                    if(carryIn == 1){
                        vLeft[j] = 1;
                        carryIn = 0;
                    }else{
                        vLeft[j] = 0;
                        carryIn = 0;
                    }
                }else if((vLeft[j] == 1 && multiplicando[j] == 0)||(vLeft[j] == 0 && multiplicando[j] == 1)){

                    if(carryIn == 1){
                        vLeft[j] = 0;
                        carryIn = 1;
                    }else{
                        vLeft[j] = 1;
                        carryIn = 0;
                    }
                }else if (vLeft[j] == 1 && multiplicando[j] == 1){

                    if(carryIn == 1){
                        vLeft[j] = 1;
                        carryIn = 1;
                    }else{
                        vLeft[j] = 0;
                        carryIn = 1;
                    }
                }
            }
           shiftBits();

        }
    }

    if(m<0 || n<0){
        produtoPosNeg();
    }

    printf("\nProduto: %d %d %d %d %d %d %d %d ", vLeft[0],vLeft[1],vLeft[2],vLeft[3],vRight[0],vRight[1],vRight[2],vRight[3]);
}
