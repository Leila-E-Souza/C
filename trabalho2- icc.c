#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>


typedef struct flor{    //esta estrutura representa a flor e suas características
    double lenght;
    double width;
    char variety[20];
    int group;
}Flower;


typedef struct pontoMedio{  //esta estrutura representa o ponto medio de representação dos grupos
    double lenght;
    double width;
    int group;
}Point;


void readFlower(FILE *file, Flower *flower){

    int i=0;
    char *dados;
    dados = calloc(100,sizeof(char));

    fgets(dados,100,file);

    while(feof(file)==0){

        fscanf(file,"%lf,%lf,%s\n", &flower[i].lenght, &flower[i].width, flower[i].variety);

        i++;
    }

    for(int i=0;i<150;i++){
        printf("%.1lf %.1lf %s\n", flower[i].lenght, flower[i].width, flower[i].variety);
    }

    printf("\nOs dados foram lidos do documento.\n");

    free(dados);
}


void startLeaders(int representante[],int k,int inicio, Flower *flower,Point *point){

    srand(time(NULL));

    if(inicio==1){

        printf("\nForam escolhidas as seguintes flores como representantes:\n");

            for(int i=1;i<=k;i++){
                representante[i]= (rand() % 150);
                printf("Grupo %i --> Flor: %d Comprimento: %.1lf Largura: %.1lf Especie: %s\n", i, representante[i], flower[representante[i]].lenght, flower[representante[i]].width, flower[representante[i]].variety);
            }

        }
    else{

        printf("\nOs representantes foram atualizados:\n");

        for(int i=1;i<=k;i++){

            float somaLenght=0,somaWidth=0,quantFlower=0;

            for(int a=0;a<150;a++){
                if(flower[a].group==i){
                    somaLenght+= flower[a].lenght;
                    somaWidth+= flower[a].width;
                    quantFlower++;
                }
            }

            point[i].group = i;
            point[i].lenght = (somaLenght/quantFlower);
            point[i].width = (somaWidth/quantFlower);

            printf("Grupo %i --> Comprimento: %.1lf Largura: %.1lf\n", i, point[i].lenght, point[i].width);
        }

    }

}


void allocGroups(int representante[], int k, Flower *flower){ 

    float dist;

    for(int i=0;i<150;i++){ //passa pelas 150 flores, escolhendo um grupo para ela

            float distMinima = 1000;
            int b = 1;

                while(b<=k){ //roda um numero k de representantes, o representante com menor distância da flor é escolhido
                    dist = sqrt(pow(flower[i].lenght-flower[representante[b]].lenght,2)+pow(flower[i].width-flower[representante[b]].width,2));

                    if(distMinima>dist){
                        distMinima=dist;
                        flower[i].group=b;
                    }

                    b++;
                }

            }

        printf("\nAs flores foram alocadas aos grupos:\n");

}


void reallocGroups(int k, Flower *flower, Point *point){

    float dist;

    for(int i=0;i<150;i++){

        float distMinima = 1000;
        int b = 1;

        while(b<=k){
                dist = sqrt(pow(flower[i].lenght-point[b].lenght,2)+pow(flower[i].width-point[b].width,2));

                if(distMinima>dist){
                    distMinima=dist;
                    flower[i].group=b;
                }

                b++;
            }

    }

}


void createCSV(FILE *newF, Flower *flower){ //Esta função irá criar um novo arquivo csv, agora com uma nova coluna com o grupo de cada flor

    for(int i=0;i<150;i++){
        fprintf(newF,"%.1lf,%.1lf,%s,%i\n", flower[i].lenght, flower[i].width, flower[i].variety, flower[i].group);
    }

}


int main()
{
    FILE *file;     //funções que vão abrir os arquivos
    FILE *newF;
    file = fopen("C:\\Users\\Rafael\\Desktop\\iris_petalas.csv","r");
    newF = fopen("C:\\Users\\Rafael\\Desktop\\novoIris_petalas.csv","w");

    if(file == NULL){
        printf("ERRO:arquivo nao encontrado\n");
        return 0;
    }

    Flower *flower;
    flower = calloc(150,sizeof(struct flor));
    Point *point;
    point = calloc(150,sizeof(struct pontoMedio));

    int k, x;
    int inicio = 1;     // esta variável indica se o programa está no começo ou nas partes posteriores
    int *representante;
    representante = calloc(151,sizeof(int));

    readFlower(file,flower);    // esta função irá ler o conteúdo do arquivo e passar para as variaveis da estrutura

    printf("\nDigite o numero de grupos:");
    scanf("%d",&k);

    printf("Defina quantas vezes o programa se repetira:");
    scanf("%d",&x);

    for(int j=0;j<x;j++){

        startLeaders(representante,k,inicio,flower,point); // esta função irá iniciar os representantes aleatóriamente ou atualiza-los

        if(inicio==1){
            allocGroups(representante,k,flower);        // esta função irá alocar as flores aos grupos
        }
        else{
            reallocGroups(k,flower,point);              // esta função irá atualizar as flores aos seus novos representantes
        }

        for(int i=0;i<150;i++){
            printf("%.1lf %.1lf %s Grupo: %i\n", flower[i].lenght, flower[i].width, flower[i].variety, flower[i].group);
        }

        inicio = 0;

        printf("\n");
        system("pause");

    }

    printf("\nPrograma encerrado.\n");

    printf("Gerando novo arquivo...\n");

    createCSV(newF, flower);

    free(flower);
    free(point);
    free(representante);

    fclose(file);

    return 0;
}

:(
:)
 (✿ヘᴥヘ)
 essa sou eu? :(
   (✿◠‿◠)
  essa ai
  ta melhorzinha :/
  (≧ω≦)
  moide?
  nhaaa ∩(︶▽︶)∩
  :(
    sem ideia
    (u.U)
    tbm
    vc ta pegando de site????
    desonesto
    eu pensei q vc tambem pegava, as vezes
    não <(*-*<)
    :( 
      me enganaram 
      
    ;-;

    (O 3 O)
    peixinho?
    
    (👉👈)
    >(*?*)>  <(o E o)< qq isso?
    :(
      :)
      :D
      :C
      da pra atrasar o trab?
      depende
      eu devo mandar antes da entrevista (16) - quarta feira
      entao tem bastante tempo
      a gente pode terminar sexta/sabado?
      sim, podemos.
      segunga tenho prova, e queria estudar no domingo 
      ok
      vou mandar até onde fizemos e dps quando terminarmos eu faço upload do trabalho inteiro
      pq pelo menos estando lá n tem problema
      ele so vai corrigir na entrevista junto cmg
      ta famosa, vai ser entrevistada
      sim
      marquei na minha agenda
      vou enviar essa parte 
      e dps terminamos
      ok?
      Ok -> 0K -> 0 Kelvin
      vou tomar banho
      among as 23:30?
      Sim!
      :)
      Hasta la vista] adieu
      que dios te bendiga <(*-*<)
      
      también
      i see this 
      bye, have a great night
      you too 
      LMAO kkkkkkkkkkk
      voltei to com saudade
      mas já?
      n sei 
      zzzzzz a mimir
      z_zzz 
      (￣。￣)～ｚｚｚi want to sleep 
      "go to sleep"
      et
      i see this
      kkkkkk
      como no minecraft
      ...maybe
      estas acá?
      Si
      i dont wanna bathe :(
      bathing is good
      nooo
      never
      regulates your corporal tempe
      rature to sl
      its no my rules 
      no in my room
      eep
      ok
      did you
      take a shower?
      no now, i go comer lanche
      when?
      10 min
      kkkkkkkkk
      ok
      iv
      vc gosta de snk?e go to remember this 
      snake?
      shingeki no kyoujin mkdsivunerovimervoer
      i like 
      yes 
      this too
      quantos episodios tem?
      da pra assistir emember
      maybe, more ou less, 100?
      more
      vo começa a ver
      parece bom
      it's good
      eu n sei onde é o ascento, acento, ascendente sei la n sei portugues :)
      assento é onde senta
      kkkkkkkkkk ata
      pedro piadas
      pedro eu te odeio
      ... 
      ?
      vou tomar banho
      infelizmente :(

        23:30 
      há mangas
      among blz?
    kkkkkkkkk q
    ???
    kkkkkkk
    tchau 
    tchau, blz
    te love