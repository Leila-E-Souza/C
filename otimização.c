//Bibliotecas Uitiizadas
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Defini�o das variaveis que controlam a medi�o de tempo
clock_t _ini, _fim;

//FUNCOES AUXILIARES
void inicia_tempo(){
    srand(time(NULL));
    _ini = clock();
}

double finaliza_tempo(){
    _fim = clock();
    return ((double) (_fim - _ini)) / CLOCKS_PER_SEC;
}

// aloca memoria para uma matriz
double** aloca_matriz(int nLinhas, int nColunas){
    int i;
    double **M = (double**)malloc(nLinhas * sizeof(double*));

    for (i=0; i<nLinhas; i++) {
        M[i] = (double*)malloc(nColunas * sizeof(double));
    }

    return M;
}

//aloca memoria para um vetor
double* aloca_vetor(int n){
    double *V = (double*)malloc(n*sizeof(double));

    return V;
}

// calcula matriz inversa
double** matriz_inversa(int n, double **A, int *IndicesBasicos){
    int i, j;
    double **B = aloca_matriz(n,n);

    for(i=0;i<n; i++){
        for(j=0;j<n; j++){
            B[i][j] = A[i][IndicesBasicos[j]];
        }
    }
    return B;
}

// calcula o valor da funcao solucao
double funcao_objetivo(int n, double *b, double *c, int *bas, double f){
    int i;

    for(i=0; i<n; i++){
        f = f + c[bas[i]] * b[i];
    }
    return f;
}

void imprime_tableau(int NumC_A, int NumL_A,int NumC_custos, double **A, double *c, int *IndicesBasicos, double *b, double f){
    int i,j,k,l;

    printf("\n");
    for(i=0;i<NumC_A*14;i++){
        printf("_");
    }
    printf("\n\n");
    for(i=0;i<NumC_A*5;i++){
        printf(" ");
    }
    printf("TABLEAU DA ITERACAO ATUAL\n");
    for(i=0;i<NumC_A*14;i++){
        printf("_");
    }
    printf("\n\n              ");

    k=0;
    for(j=0;j<NumC_A;j++){
        printf("    x%d     ", j);
        k = k+13;
    }
	printf("\n    %lf  |",f);
    for(i=0; i<NumC_custos; i++){
        printf("%lf  ", c[i]);
    }
    printf("\n");
    for(l=0;l<k+4;l++){
        printf("-");
    }
    printf("\n  ");

    k=0; l=0;

	for(i=0;i<NumL_A;i++){
        printf("x%d=%lf|", IndicesBasicos[k],b[l]);
        for(j=0;j<NumC_A;j++){
            printf("  %lf ", A[i][j]);
        }
        k++; l++;
        printf("\n  ");
	}
	printf("\n");
}

// faz o pivoteamento das linhas da matriz A
double** pivoteamento(double **A, double **invB, int i, int L_pivo, double elem_a_zerar, int Num_Var_Basicas, int IndiceEntraBase, double *b_atual){
    int j;

    for(j=0; j<Num_Var_Basicas; j++){
        invB[i][j] = invB[i][j]-(elem_a_zerar*invB[L_pivo][j]);
    }
    A[i][IndiceEntraBase] = A[i][IndiceEntraBase] - (elem_a_zerar*A[L_pivo][IndiceEntraBase]);
    b_atual[i] = b_atual[i] - (elem_a_zerar*b_atual[L_pivo]);

    return A;
}

// FUNCAO PRINCIPAL
int main(int argc, char const *argv[]){
    int NumL_A, NumC_A; // numero de linhas e colunas da matriz A, respectivimente
    int NumC_custos; // numero de colunas do vetor de custos reduzidos
    int NumL_b; // numero de linhas do vetor b

    double **A, **invB; // matriz com valores das variaveis das resticoes e matriz inversa de A, respectivamente
    double *b, *b_atual; // vetores solucao e sulucao atual, respectivamente
    double *c; // vetor de custo
    double auxiliar = 0; // variavel auxiliar
    double *vetor_auxiliar;
    double f = 0.0; // funcao solucao

    int i,j,k,l; // contadores
    int flag = 1;
    int aux = 0.0, min = 1000000, iteracoes = 0, aux2;

    double *interm, res = 0.0, custo_relativo = 0.0, menor_custo_relativo=10000000;
    double pivo, elem_a_zerar;
    int L_pivo; //linha do pivo

    int Num_Var_Nao_Basicas, Num_Var_Basicas; //Define numero de variaveis basicas e nao basicas
    int *IndicesBasicos, *IndicesNaoBasicos; // vetor de indices basicos e indices naoo basicos
    int IndiceEntraBase, IndiceSaiBase; // indices de quem entra e de quem sai da base
    int posEntra, posSai; //posicoes de quem entra e quem sai dentro dos vetores de indices

    inicia_tempo();

    printf("****************  METODO SIMPLEX  ****************\n\n");
    printf("__________________________________________________\n\n");
    printf("                 ENTRADA DE DADOS:              \n");
    printf("__________________________________________________\n\n");
    printf("\nDigite o numero de linhas da matriz A: ");
    scanf("%d", &NumL_A);

    printf("\nDigite o numero de colunas da matriz A: ");
    scanf("%d", &NumC_A);

    NumL_b = NumL_A; // numero de linhas do vetor b eh igual ao numero de linhas da matriz A
    NumC_custos = NumC_A; // numero de colunas do vetor de custos reduzidos eh igual ao numero de colunas da matriz A

    /*printf("\nDigite o numero de linhas do vetor b: ");
    scanf("%d", &NumL_b);

    printf("\nDigite o numero de colunas do vetor c: ");
    scanf("%d", &NumC_custos);*/

    // Alocando mem�ria
    A = aloca_matriz(NumL_A, NumC_A);
    b = aloca_vetor(NumL_b);
    c = aloca_vetor(NumC_custos);

    double *z;
    z = aloca_vetor(NumC_custos);


    printf("\n\nDigite os valores da matriz A");
    for(i=0;i<NumL_A; i++){
        for(j=0;j<NumC_A; j++){
            printf("\n   A[%d][%d] = ",i,j);
            scanf("%lf", &auxiliar);
            A[i][j] = auxiliar;
            //printf("\nAuxiliar: %d", auxiliar);
        }
        printf("\n");
    }

    printf("\n\nDigite os valores do vetor b");
    for(i=0; i<NumL_b; i++){
        printf("\n   b[%d] = ", i);
        scanf("%lf", &auxiliar);
	   b[i] = auxiliar;
        //printf("\nb[%d] = %f", i,b[i]);
    }

    printf("\n\nDigite os valores do vetor custos reduzidos");
    for(i=0; i<NumC_custos; i++){
        printf("\n   c[%d] = ", i);
        scanf("%lf", &auxiliar);
        c[i] = auxiliar;
	   //printf("\nc[%d] = %f", i,c[i]);
    }

    Num_Var_Nao_Basicas = NumC_A - NumL_A; // numero de variaveis nao basicas corresponde ao numero de variaveis que nao sao li entre si
    Num_Var_Basicas = NumL_A; // pois existem mais restricoes do que variaveis

    // alocando mem�ria para armazenar os indices
    IndicesBasicos = (int*)malloc(Num_Var_Basicas*sizeof(int));
    IndicesNaoBasicos = (int*)malloc(Num_Var_Nao_Basicas*sizeof(int));

    //obtem indices das colunas basicas
    printf("\n\nDigite os indices das colunas basicas: (Lembrando que os indices comecam a partir do 0)");
    for(i=0; i<Num_Var_Basicas; i++){
        printf("\n   Indice = ");
        scanf("%d", &IndicesBasicos[i]);
    }

    //obtem indices das colunas nao basicas
    printf("\n\nDigite os indices das colunas nao basicas: (Lembrando que os indices comecam a partir do 0)");
    for(i=0; i<Num_Var_Nao_Basicas; i++){
        printf("\n   Indice = ");
        scanf("%d", &IndicesNaoBasicos[i]);
    }

    inicia_tempo();

    //inicializa inversa de B
    invB = aloca_matriz(Num_Var_Basicas, Num_Var_Basicas);
    invB = matriz_inversa(NumL_A,A,IndicesBasicos);

    //aloca vetor de solucao atual
    b_atual = aloca_vetor(NumL_b);

    //inicializa b_atual
	for(i=0; i<Num_Var_Basicas; i++){
	    b_atual[i] = 0.0;
	    b_atual[i] = b[i];
	    //printf("\nb atual[%d]: %f\n", i,b_atual[i]);
	}

    flag = 1;
    iteracoes = 0; // ainda nao foram feitas iteracoes

	//alocacao intermediaria para o produto inv(B) * a_i
	interm = aloca_vetor(NumL_A); // aloca memoria para o produto inv(B) * a_i
	vetor_auxiliar = aloca_vetor(Num_Var_Basicas); 	//aloca memoria para vetor temporario de atualizacao dos a_k

	//imprime_tableau(NumC_A,NumL_A,NumC_custos, A, c, IndicesBasicos, b_atual, f);

    while((flag==1)){
		f = 0.0;

        f = funcao_objetivo(Num_Var_Basicas, b_atual, c, IndicesBasicos, f);
        //printf("\n\n\n %lf \n\n\n", f);

        //calculando os custos relativos
		for(i=0; i<Num_Var_Nao_Basicas; i++){
			for(j=0; j<Num_Var_Nao_Basicas; j++){
				interm[j] = 0.0; //inicializa
			}

			// inv(B)*coluna Ai (B^-1*Aj)
			for(j=0; j<Num_Var_Basicas; j++){
				for(k=0; k<Num_Var_Basicas; k++){
					interm[j] = interm[j] + invB[j][k] * A[k][IndicesNaoBasicos[i]];
				}
			}
			res = 0.0;

			//custo basico * resultado acima
			for(l=0; l<Num_Var_Basicas; l++){
				res = res + c[IndicesBasicos[l]] * interm[l];
			}

			custo_relativo = c[IndicesNaoBasicos[i]] - res; // custo relativo

			//printf("\n\n\ncustos basicos: %lf \n\n\n", custo_relativo);

			z[IndicesNaoBasicos[i]]= custo_relativo;
            z[IndicesBasicos[i]] = 0;

			//printf("\n\n\n z[%d]=%lf\n\n\n", IndicesNaoBasicos[i], z[IndicesNaoBasicos[i]]);
			//printf("\n\n\n z[%d]=%lf\n\n\n", IndicesBasicos[i], z[IndicesBasicos[i]]);

			//verificamos o menor custo relativo, e pegamos o indice associado
			if(custo_relativo < menor_custo_relativo){
				menor_custo_relativo = custo_relativo;
				IndiceEntraBase = IndicesNaoBasicos[i];
				posEntra = i;
			}
		}//for custos relativos

        imprime_tableau(NumC_A, NumL_A, NumC_custos, A, z, IndicesBasicos, b_atual, f);

		//verifica se menor custo relativo eh negativo
		if(menor_custo_relativo >= 0){
			break; //encerra
		}

		for(i=0; i<Num_Var_Basicas; i++){
            vetor_auxiliar[i] = 0.0;
		}

		//atualiza�o da coluna a_k
		for(i=0; i<Num_Var_Basicas; i++){
			for(j=0; j<Num_Var_Basicas; j++){
				vetor_auxiliar[i] += invB[i][j]*A[j][IndiceEntraBase];
			}
		}//fim atualizacao de a_k

		//transfere valores para matriz A
		for(i=0; i<Num_Var_Basicas; i++){
            A[i][IndiceEntraBase] = vetor_auxiliar[i];
		}

		min = 1000000;
		flag = 0; //sup�e solu�o infinita

		//verifica quem sai da base
		for(i=0; i<Num_Var_Basicas; i++){
			if(A[i][IndiceEntraBase] > 0){
				flag = 1; //solucao n�o tende a menos infinito
				if(b_atual[i] / A[i][IndiceEntraBase] < min){
					min = b_atual[i] / A[i][IndiceEntraBase];
					IndiceSaiBase = IndicesBasicos[i];
					posSai = i;
				}
			}
		}

		//controle: printf("\nSai da base indice %d --- valor: %d --- pos: %d\n", IndiceQueSaiBase, min,posSai);
		//atualiza�o - realiza pivoteamento.
		// a linha pivo � dada pelo indice de quem sai: posSai, que passarei a chamar de linha_pivo

		L_pivo = posSai;

		//come�ando colocando 1 na posicao pivo
		pivo = A[posSai][IndiceEntraBase];

		for(i=0; i<Num_Var_Basicas; i++){
		    invB[L_pivo][i] = invB[L_pivo][i]/pivo;
		}
		A[L_pivo][IndiceEntraBase] = A[L_pivo][IndiceEntraBase]/pivo;
		b_atual[L_pivo] = b_atual[L_pivo]/pivo; //posicao com valor 1
		//controle: printf("\nB atual no pivo: b[%d] = %f\n", linha_pivo, b_chapeu[linha_pivo]);

		//a partir da linha do pivo, irei para as linhas abaixo desta
		for(i=(L_pivo+1); i<Num_Var_Basicas; i++){
			elem_a_zerar = A[i][IndiceEntraBase];
			//controle: printf("\nelemento a zerar: %f\n", elem_a_zerar);

			if(elem_a_zerar != 0){
                A = pivoteamento(A, invB, i, L_pivo, elem_a_zerar, Num_Var_Basicas, IndiceEntraBase, b_atual);
			}
		}

		//a partir da linha do pivo, irei agora para as linhas acima desta
		for((i=L_pivo-1); i > -1; i--){
			elem_a_zerar = A[i][IndiceEntraBase];

			if(elem_a_zerar != 0){
                A = pivoteamento(A, invB, i, L_pivo, elem_a_zerar, Num_Var_Basicas, IndiceEntraBase, b_atual);
			}
		}

		//arrumar indices b�sicos e n�o b�sicos
		aux2 = IndicesBasicos[posSai];
		IndicesBasicos[posSai] = IndicesNaoBasicos[posEntra];
		IndicesNaoBasicos[posEntra] = aux2;

        //imprime_tableau(NumC_A, NumL_A, NumC_custos, A, z, IndicesBasicos, b_atual, f);

        f = 0.0;
        res = 0.0;
        aux = 0.0;
        min = 1000000;
        menor_custo_relativo = 1000000;

		iteracoes ++;

    }//fim do processamento

    //imprime_tableau(NumC_A, NumL_A, NumC_custos, A, z, IndicesBasicos, b_atual, f);

    double tempo_busca = finaliza_tempo();

	printf("\n\n\n-------------------------------------------------------------\n SOLUCAO: \n");
	if(flag == 0) printf("\nO problema nao possui solucao finita.\n\n");

	else{
		for(i=0; i<Num_Var_Basicas; i++){
            printf("\n x[%d] = %f \n", IndicesBasicos[i], b_atual[i]);
		}
		for(i=0; i<Num_Var_Nao_Basicas; i++){
            printf("\n x[%d] = %d \n", IndicesNaoBasicos[i], 0);
		}

		printf("\nValor da funcao objetivo: %f\n\n", f);
		printf("Numero de iteracoes feitas pelo metodo: %d\n\n", iteracoes);
        printf("Tempo de solucao:\t%fs\n", tempo_busca);
		printf("\n-------------------------------------------------------------\n\n");
	}

    return(0);
}
