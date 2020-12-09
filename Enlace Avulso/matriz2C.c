#include <stdio.h>
#include <stdlib.h>
#define N 13

float identidade[N][N];

void inversa(int n, float Matriz_A[N][N]);

main(){
    int i = 0, j = 0, k1 = 0, k2 = 0, value = 0;
	float beta = 2.0, a = 5, b = 11, aa = 0.4, bb = 1.0,
        vector5FF[13] = {0.0, 1.0, 1.0, 1.0, 1.0, 2.0, 2.0, 2.0, 0.0, 0.0, 3.0, 1.0, 1.0},
        vector11FF[13] = {0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 1.0, 1.0, 0.0, 1.0, 1.0},
        D[13][1] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
        eixox[1000], eixoyy[1000], occupeixoyy[1000], littleYY[1000],
        XX[13][1], temp = 0.0, C[13][13], NPb5 = 0, soma = 0, NPb11 = 0, NPbb, lambdaS = 0, l5, l11;

	// Alimentando os eixos
	for(i = 0; i < 1000; i++){
		eixox[i] = eixoyy[i] = occupeixoyy[i] = littleYY[i] = i;
	}

	for(value = 0; value < 1000; value++){
		float l5 = value / 100.0, l11 = beta * l5, nList[13][13] = {-(l5+l11), 1, 1, 1, 1, 0, 0, 0, 1, 1, 0, 0, 0,
																l5, -(l5+l11+1), 0, 0, 0, 0, 1, 1, 0, 0, 0, 1, 0,
																0, 0, -(l5+1), 0, 0, 1, 0, 1, 0, 0, 0, 0, 0,
																0, 0, 0, -(l5+1), 0, 1, 1, 0, 0, 0, 0, 0, 0,
																0, 0, 0, 0, -(l11+l5+1), 0, 0, 0, 0, 0, 0, 0, 1,
																0, 0, 0, 0, l5, -(l5+2), 0, 0, 0, 0, 1, 0, 0,
																0, 0, 0, l5, 0, 0, -(l5+2), 0, 0, 0, 1, 0, 0,
																0, l5, l5, 0, 0, 0, 0, -(l5+2), 0, 0, 1, 0, 0,
																l11, 0, 0, 0, 0, 0, 0, 0, -(l5+1), 0, 0, 0, 1,
																0, 0, 0, 0, 0, 0, 0, 0, 0, -(l5+1), 0, 1, 0,
																0, 0, 0, 0, 0, l5, l5, l5, 0, 0, -3, 0, 0,
																0, l11, 0, 0, 0, 0, 0, 0, 0, l5, 0, -2, 0,
																0, 0, 0, 0, l11, 0, 0, 0, l5, 0, 0, 0, -2};

		for(i = 0; i < N; i++){
			for(j = 0; j < N; j++){
				C[i][j] = nList[i][j];
				if(i == 12){
					C[i][j] = 1;
				}
			}
	    }
		inversa(N, C);

		// Realizando a multiplicação
		for(k1 = 0; k1 < N; k1++){
	         temp = 0.0;
	         for(i = 0; i < N; i++)
	         {
	            temp += identidade[k1][i] * D[i][0];
	         }
            XX[k1][0] = temp;
	    }

        NPb5 = XX[10][0] + XX[11][0] + XX[12][0];
        NPb11 = 1 - (XX[0][0] + XX[1][0] + XX[4][0]);
		NPbb = ((a * l5 * NPb5) + (b * l11 * NPb11)) / ((a * l5) + (b * l11));
		lambdaS = (((a + (b * beta)) * value) / 100.0);
		eixox[value] = lambdaS;

        float somador = 0.0;
		for(i = 0; i < N; i++){
            somador += ((((vector5FF[i] * 5.0) + (vector11FF[i] * 11.0)) * XX[i][0]));
		}
        occupeixoyy[value] = (somador / 16.0);

        littleYY[value] = (lambdaS * (1 - NPbb)) / 16;
        eixoyy[value] = NPbb;
	}

    printf("\n\nSimulacao Final\n");
    printf("\n\n********************************* eixox *********************************\n\n");
	for(i = 0; i < 1000; i++){
		printf("%.2f, ", eixox[i]); // Resultado correto
	}

    printf("\n\n********************************* LittleYY *********************************\n\n");
	for(i = 0; i < 1000; i++){
		printf("%f, ", littleYY[i]); // Resultado correto
	}

	printf("\n\n********************************* occupeixoyy *********************************\n\n");
	for(i = 0; i < 1000; i++){
		printf("%f - ", occupeixoyy[i]); // Resultado errado
	}

    printf("\n\n\n");
    system("pause");
}

// ******************************************** FUNÇÕES ********************************************
void inversa(int n, float Matriz_A[N][N]){
	int linha, coluna, k = 0;
	float pivo = 0, m = 0;

	for(linha = 0; linha < N; linha++){
    	for(coluna = 0; coluna < N; coluna++){
	   		if(linha == coluna){
	    		identidade[linha][coluna] = 1;
	        }else{
	   	        identidade[linha][coluna] = 0;
		    }
    	}
	}

	for(coluna = 0; coluna < N; coluna++){
	    pivo = Matriz_A[coluna][coluna];
	    for(k = 0; k < N; k++){
			Matriz_A[coluna][k] = (Matriz_A[coluna][k]) / (pivo);
			identidade[coluna][k] = (identidade[coluna][k]) / (pivo);
	    }
		for(linha = 0; linha < N; linha++){
			if(linha != coluna){
				m = Matriz_A[linha][coluna];
	   			for(k = 0; k < N; k++){
	     			Matriz_A[linha][k] = (Matriz_A[linha][k]) - (m * Matriz_A[coluna][k]);
		    		identidade[linha][k] = (identidade[linha][k]) - (m * identidade[coluna][k]);
	    		}
	   		}
	   	}
	}
}
