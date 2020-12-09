#include <stdio.h>
#include <stdlib.h>
#define N 12

float identidade[N][N];

void inversa(int n, float Matriz_A[N][N]);

int main(void)
{
    int v1 = 1, v2 = 1, i = 0, j = 0, k1 = 0, k2 = 0;
	float label[12] = {0.0, 1.0, 2.0, 3.0, 0.1, 1.1, 2.1, 3.1, 0.2, 1.2, 2.2, 3.2};
	int B[12][1] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1};
	float A[12][12], resultado[12][1], nList[12][12] = {-(v1+v2), 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0,
						   v1, -(v1+v2+1), 2, 0, 0, 1, 0, 0, 0, 0, 0, 0,
						   0, v1, -(v1+v2+2), 3, 0, 0, 1, 0, 0, 0, 0, 0,
						   0, 0, v1, -(v1+v2+3), 0, 0, 0, 1, 0, 0, 0, 0,
						   v2, 0, 0, 0, -(v1+v2+1), 1, 0, 0, 2, 0, 0, 0,
						   0, v2, 0, 0, v1, -(v1+v2+2), 2, 0, 0, 2, 0, 0,
						   0, 0, v2, 0, 0, v1, -(v1+v2+3), 3, 0, 0, 2, 0,
						   0, 0, 0, (v1+v2), 0, 0, v1, -(v1+v2+4), 0, 0, 0, 2,
						   0, 0, 0, 0, v2, 0, 0, 0, -(v1+v2+2), 1, 0, 0,
						   0, 0, 0, 0, 0, v2, 0, 0, (v1+v2), -(v1+v2+3), 2, 0,
						   0, 0, 0, 0, 0, 0, v2, 0, 0, (v1+v2), -(v1+v2+4), 3,
						   0, 0, 0, 0, 0, 0, 0, (v1+v2), 0, 0, (v1+v2), -5}, temp = 0.0;
	// Carregando as matrizes
	for(i = 0; i < 12; i++)
    {
		for(j = 0; j < 12; j++)
		{
			A[i][j] = nList[i][j];
			if(i == 11)
			{
				A[i][j] = 1; // Pega a última linha
			}
		}
	}

	inversa(N, A);

	// Realizando a multiplicação
	for(k1 = 0; k1 < 12; k1++)
    {
        for(k2 = 0; k2 < 12; k2++)
        {
          temp = 0.0;
              for(i = 0; i < 12; i++)
              {
                temp += identidade[k1][i] * B[i][k2];
              }
          resultado[k1][k2] = temp;
        }
    }

	// Rotina de impressão da tabela de resultados
	printf("Estado\t\t Resultado");
	for(i = 0; i < 12; i++)
	{
		printf("\n%.1f \t\t %f", label[i], resultado[i][0]);
	}

  printf("\n\n\n");
  system("pause");
  return 0;
}

// **************************** FUNÇÕES ****************************

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
			Matriz_A[coluna][k] = (Matriz_A[coluna][k])/(pivo);
			identidade[coluna][k] = (identidade[coluna][k])/(pivo);
	    }

		for(linha = 0; linha < N; linha++){
			if(linha != coluna){
				m = Matriz_A[linha][coluna];
	   			for(k = 0; k < N; k++){
	     			Matriz_A[linha][k] = (Matriz_A[linha][k]) - (m*Matriz_A[coluna][k]);
		    		identidade[linha][k] = (identidade[linha][k]) - (m*identidade[coluna][k]);
	    		}
	   		}
	   	}
	}
}
