#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

//Trabalho de IPC
//Iago Guilherme Comin N Usp: 13687088
//Leila Evangelista Souza N Usp: 11811923
//Alam Kim N Usp: 11810644

//Este Jogo foi programado para rodar corretamente no sistema operacional Windows 10 

//Funcao que cria o tabuleiro
void inicia_tabuleiro(char v[][10]){
  
  int i,j;//Contadores
  
  for(i=0; i<8; i++){
    for(j=0; j<10; j++){
      v[i][j]='*';
      v[7][0]='P';
    }
  }
  return;
}

//Funcao que imprime o tabuleiro
void imprime_tabuleiro(char v[8][10]){
  
  int n[10],i,j;//Contadores
  
  printf(" ");
  printf(" ");
  for(j=0; j<10; j++){
    n[j]=j+1;
    printf("%d  ",n[j]);//Printa os numeros das colunas
  }
  printf("\n");

  for(i=0; i<8; i++){
    printf("%d",i+1);//Printa os números das linhas
    printf(" ");//Printa os espaços das linhas
    for(j=0; j<10; j++){
      printf("%c",v[i][j]);
      printf("  ");
    }
    printf("\n");
  }
  return;
}

//Funcao que faz a maquina jogar simetricamente em relacao a linha 8
void apaga_coluna(char v[][10], int a){

  int i; //Contador

  for(i=a; i>=0; i--){
    v[i][0]=' ';
  }
  return;
}

//Funcao que faz a maquina jogar simetricamente em relacao a coluna 1
void apaga_linha(char v[][10], int a){

  int i; //contador

  for(i=a; i<=9; i++){
    v[7][i]=' ';
  }
  return;
}

//Funcao que gera um nuemro aleatorio e faz a maquina jogar em coordenadas validas
void num_aleatorio(char v[8][10]){
  int linha,coluna;
  int i,j;//contadores

  do{//Gera um nuemero aleatorio 
      srand(time(NULL));
      linha=rand() % 7;
      coluna=rand() % 9;
    }while((v[linha][coluna]==' ')&&(v[7][0]!=0));
  if((v[6][0]==' ')&&(v[7][1]==' ')){
    linha=7;
    coluna=0;
  }
  
  for(i=linha; i>=0; i--){
    for(j=coluna; j<10; j++){
      v[i][j]=' ';
    }
  }
  return;
}


//Inicio da funcao principal
int main (){

  char v[8][10];//Tabuleiro
  int i, j;//Contadores
  int l, c;//Variaveis de linha e coluna
  int n[8],m,vez,win;
  int e;//Variavel para escolha do jogo
  int linha,coluna;//Variaveis para que recebem  numeros aleatorios 

  //Chamando a funcao que cria o tabuleiro
  inicia_tabuleiro(v);
  
  //Menu para o usuário escolher as versao do jogo
  do{
    printf("------------------------  Bem-Vindo ao jogo Chomp  -----------------------\n");
    printf("|");printf("Este eh um jogo que pode ser jogado com um ou dois jogadores, cujo      ");printf("|\n");
    printf("|");printf("objetivo eh comer os chocolates, representados por (*), porem quem comer");printf("|\n");
    printf("|");printf("a pimenta (P) perde o jogo. Que venca a melhor estrategia !!            ");printf("|\n");
    printf("|");printf("                                                                        ");printf("|\n");
    printf("|************************ Escolha o estilo de Jogo **********************|\n"); 
    printf("|");printf("                                                                        ");printf("|\n");
    printf("|");printf("Digite 1 para jogar : Maquina Vs. Jogador                               ");printf("|\n");
    printf("|");printf(" ( Obs: A Maquina comeca jogando )                                      ");printf("|\n");
    printf("|");printf("                                                                        ");printf("|\n");
    printf("|");printf("Digite 2 para jogar : Jogador Vs. Jogador                               ");printf("|\n");
    printf("--------------------------------------------------------------------------\n");
    scanf("%d",&e);
  }
  while(e!=1 && e!=2);

  //Codigo do Jogador Vs. Jogador
  if(e==2){//Verifica qual o modo escolhido para jogar
  printf("----------------------------------------------\n");
  printf("Voce Escolheu a opcao Jogador Vs. Jogador\n");
  printf("----------------------------------------------\n");
  printf("|");printf("(Primeira Coordenada refere-se a linha que pode ir de 1 a 8)            ");printf("|\n");
  printf("|");printf("(Segunda Coordenada refere-se a coluna que pode ir de 1 a 10)           ");printf("|\n");
  printf("\n\n");
  
  //Funcao que imprime o tabuleiro
  imprime_tabuleiro(v);
    
  do{
    //Mecanismo para mostrar a vez de cada jogador
    for(m=2;m<102;m++){
      if(m%2==0){
        vez=1;
      }
      else{
        vez=2;
      }
      printf("\n");//Dá um espaço entre a frase e o tabuleiro
      printf("Digite o numero da linha e coluna jogador %d : ",vez);
      scanf("%d %d", &l, &c);  
      printf("--------------------------------------------------------------------------");
      printf("\n");
      l=l-1;
      c=c-1;
    
      if(v[l][c]==' '){
        printf("*************** Chocolates já comido !! **************** \n");
        printf("Digite novamente jogador %d ",vez);
        m=m-1;
        printf("\n");
        printf("\n");
      }  
      if((l>=0 && l<=7) && (c>=0 && c<=9) ){//Comer as casas de chocolate
        for(i=l; i>=0; i--){
          for(j=c; j<10; j++){
            v[i][j]=' ';
          }
        }
        if(v[7][0]==' '){//Início IF 2
          if((m-1)%2==0){
            win=1;
          }else{
            win=2;
          }
          //Verificação de vitória
          printf("Jogador %d ganhou !!",win);
          printf("Jogador %d comeu a pimenta e perdeu !!\n",vez);
          return(0);
        }//Fim If 2
         
        //Printa o tabuleiro
        imprime_tabuleiro(v);
        
        }else{//Verifica o que esta errado nas coordenadas

          l=l+1;
          c=c+1;
        
          if(l>8){
          printf("Linha invalida ! \n");
          }
          if(c>10){
          printf("Coluna invalida ! \n");
          }
          printf("Tente novamente jogador %d ",vez);
          m=m-1;
          printf("\n");
        }
      }
    }while(v[7][0]!=' ');
  }
  
//---------------------Fim do codigo Jogador Vs. Jogador--------------------------//


//Inicio do codigo Jogador Vs. Maquina
  if(e==1){
    printf("----------------------------------------------\n");
    printf("Voce Escolheu a opcao Maquina Vs. Jogador  \n");
    printf("----------------------------------------------\n");
    printf("\n");
    printf("|");printf("(Primeira Coordenada refere-se a linha que pode ir de 1 a 8)            ");printf("|\n");
  printf("|");printf("(Segunda Coordenada refere-se a coluna que pode ir de 1 a 10)           ");printf("|\n");
  printf("\n\n");

    imprime_tabuleiro(v);
    printf("--------------------------------------------------------------------------");
    printf("\n");
    
    //Primeira jogada da maquina
    for(i=6; i>=0; i--){
      for(j=1; j<10; j++){
        v[i][j]=' ';
      }
    }
    
    do{
      l=0;
      c=0;
      
      imprime_tabuleiro(v);
      printf("\n");
      printf("Sua vez de jogar! Digite o numero da linha e coluna : ");
      scanf("%d %d", &l, &c);  
      printf("--------------------------------------------------------------------------");
      printf("\n");
      l=l-1;
      c=c-1;
    
      if(v[l][c]==' '){
        printf("*************** Chocolates já comido !! **************** \n");
        printf("Digite novamente...");
        printf("\n");
        printf("\n");
        
      }else{//Mecanismo auxiliar que que evita usuario digitar coordenadas ja digitadas antes
      if((l>=0 && l<=7) && (c>=0 && c<=9) ){//Comer as casas de chocolate
        
        for(i=l; i>=0; i--){
          for(j=c; j<10; j++){
            v[i][j]=' ';
          }
        }
        
        if(v[7][0]==' '){
          printf("A Maquina ganhou !!");
          printf("Voce comeu a pimenta e perdeu !!\n");
          return(0);
        }
        
        //Verificacao de vitoria caso linha 8 coluna x        
        if((c+1==10) && (l+1==8)){
          v[7][8]=' ';
        }

//****************************************************************************************
//Caso delicado na qual a maquina tem chance de perder
        //Apos escolhido esse numero aleatorio valido, a maquina efutua sua jogada
        if((c+1==9)  && (l+1==8)){  
          num_aleatorio(v);
        }
        
        //Caso em que a maquina perde
        if((v[6][0]==' ') && (v[7][1]==' ')){
          v[7][0]=' ';
          imprime_tabuleiro(v);
          printf("\nVoce Ganhou ! A Maquina comeu a pimenta e perdeu");
        }
//**************************************************************************************
        
//**************************************************************************************
        if((c+1==8) && (l+1==8)){
          if((v[0][0]==' ')){//Caso v[0][0] ja esteja vazia, a maquina efetua outra jogada pegando a funcao num_aleatorio e depois faz a jogada valida
            num_aleatorio(v);
          }else{
            apaga_coluna(v,0);//Caso v[0][0] nao esteja ocupada, a maquina efetua a sua jogada
          }
        }
//*****************************************************************************************
        if((c+1==7) && (l+1==8)){
          if(v[1][0]==' '){//Caso v[1][0] ja esteja vazia, a maquina efetua outra jogada pegando a funcao num_aleatorio e depois faz a jogada valida
            num_aleatorio(v);
          }else{
            apaga_coluna(v,1);///Caso v[0][1] nao esteja ocupada, a maquina efetua a sua jogada      
          }          
        }
//****************************************************************************************
        if((c+1==6) && (l+1==8)){
          if(v[2][0]==' '){//Caso v[2][0] ja esteja vazia, a maquina efetua outra jogada pegando a funcao num_aleatorio e depois faz a jogada valida
            num_aleatorio(v);
          }else{
            apaga_coluna(v,2);
          }
        }
//****************************************************************************************
        if((c+1==5) && (l+1==8)){
          if(v[3][0]==' '){
            num_aleatorio(v);
          }else{
            apaga_coluna(v,3);
          }
        }
//**************************************************************************************
        if((c+1==4) && (l+1==8)){
          if(v[4][0]==' '){
            num_aleatorio(v);
          }else{
            apaga_coluna(v,4);
          }
        }
//*************************************************************************************
        if((c+1==3) && (l+1==8)){
          if(v[5][0]==' '){
            num_aleatorio(v);
          }else{
            apaga_coluna(v,5);
          }
        }
//************************************************************************************
        if((c+1==2)&& (l+1==8)){
          if(v[6][0]==' '){
            num_aleatorio(v);
          }else{
          apaga_coluna(v,6);
          }
        }
//***********************************************************************************
        
//Verificacao de vitoria caso linha x coluna 1
        if((c==0) && (l==0)){
          apaga_linha(v, 7);
        }
        if((c==0) && (l==1)){
          apaga_linha(v, 6);
        }
        if((c==0) && (l==2)){
          apaga_linha(v, 5);
        }
        if((c==0) && (l==3)){
          apaga_linha(v, 4);
        }
        if((c==0) && (l==4)){
         apaga_linha(v, 3);
        }
        if((c==0) && (l==5)){
         apaga_linha(v, 2);
        }
        if((c==0) && (l==6)){
          apaga_linha(v, 1);
        }
        
        }else{//Verifica o que esta errado nas coordenadas inseridas pelo usuario
          l=l+1;
          c=c+1;
        
          if(l>8){
          printf("Linha invalida ! \n");
          }
          if(c>10){
          printf("Coluna invalida ! \n");
          }
          printf("Tente novamente jogador ");
          printf("\n");
        }
        }
      }while(v[7][0]!=' ');
    }
    
  //Fim do codigo Maquina Vs. Jogador
  return 0;
}