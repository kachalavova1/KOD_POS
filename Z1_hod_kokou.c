/*
*Pri večernej akademickej diskusii ste sa vy a vaši 5 kamaráti vášnivo rozprávali o pravdepodobnosti a štatistike. Reč prišla aj na slabú intuíciu, ktorú ako ľudia máme. Svoje tvrdenia ste demonštrovali na správaní hracej kocky, na ktorej pri opakovanom hádzaní niekedy padne 6 viackrát za sebou. Pánovi od vedľajšieho stola sa takéto správanie hracej kocky zdalo podozrivé. Podľa neho je kocka falošná.

Aby ste ho presvedčili, rozhodli ste sa vykonať experiment, v ktorom bude každý z vás hádzať kockou 1595-krát a zapisovať dĺžku sekvencie opakovania hodu čísla 6.
*
*Pre úsporu času sa rozhodlo vykonať celý experiment virtuálne. Vytvorte preto program, v ktorom bude každý kamarát reprezentovaný jedným vláknom, v ktorom bude simulované hádzanie kockou. Výstupom každého vlákna bude frekvenčná tabuľka dĺžok sekvencií opakovania hodu 6.
*
* Priklad
*6 4 6 6 6 6 2 6 6 6 6 6 6
*
*
*1 -> 2
2 -> 2
3 -> 0
4 -> 0
5 -> 1

*
*/


#include <pthread.h> 
#include <time.h> 
#include <stdlib.h> 
#include <stdio.h> 
#include <stdbool.h> 
#include <string.h> 

#define MAX_HODY 1595 
#define POCET_KAMARATOV 5


typedef struct {
int id; // id kamarata
int frekvencie[5];
} KamaratData;

void* kamarat (void* data) {
  KamaratData* kamaratske_data = (KamaratData*)data; // nutne pretypovat

  int aktualna_sekvencia = 0; 


for (int i = 0; i < 5; i++) {
  kamaratske_data->frekvencie[i] = 0; // vytvorim pole kde budem ukladat tie frekvencie 
    //
  }
  for (int i = 0; i < MAX_HODY; i++) {
  int hod = rand() % 6 + 1;
  
    if (hod == 6) {
    aktualna_sekvencia++; // zvysi sekvenciu hodu 6

  } else {
      if (aktualna_sekvencia > 0) { // musi byt viac ako 0 lebo tak logicky pre nulu neratam 


    if (aktualna_sekvencia >= 5) {
    kamaratske_data->frekvencie[4]++; // pripocita v poli ku tomu =>5 na aktualnu sekvenciu 

    } else {
    kamaratske_data->frekvencie[aktualna_sekvencia-1]++;  // pretoze napr. padlo 2x za sebou ale v poli je to na indexe 1

    }

  }

  aktualna_sekvencia = 0; // reset sekvencie 



  
}

      if (aktualna_sekvencia > 0) {
    if (aktualna_sekvencia >= 5) {
      kamaratske_data->frekvencie[4]++;

      } else {
      kamaratske_data->frekvencie[aktualna_sekvencia -1]++;

      }

    } // nutna kontrola lebo keby to uz bolo na tom max hody 
  

}
  return NULL;
}


int main () { // bezparametricky main 

  srand(time(NULL)); 
  
  KamaratData data[POCET_KAMARATOV]; // potrebujem aj to pole kamaratov
  pthread_t kamarati[POCET_KAMARATOV]; 


  // potrebujem im inicializovat atributy
  for (int i = 0; i < POCET_KAMARATOV; i++ ) {
      data[i].id = i + 1;
    
    // lenze oni este maju v sebe mat to pole tych frekvencii 
  for (int j = 0; j < 5; j++) {
      data[i].frekvencie[j] = 0;

    }

  }


  for (int i = 0; i < POCET_KAMARATOV; i++) {
  pthread_create(&kamarati[i], NULL, kamarat, &data[i]); // posielam tam toho jedneho konkrétneho kamaráta &data[i]


  }

  for (int i = 0; i < POCET_KAMARATOV; i++) {
  pthread_join(kamarati[i], NULL);

  }


  // vypis pre kazdeho 
  
  for (int i = 0; i < POCET_KAMARATOV; i++) {
    // vypis ktory kamarat 
    printf("Kamarat %d : \n", data[i].id);
  
    for (int j = 0; j < 5; j++) // pre vypis tych frekvencii
    // 1 -> 2 .... cize najprv ta frekvencia j a potom atribut z kamarat[j]->frekvencie
    printf("Sekvencia %d -> %d \n", j+1, data[i].frekvencie[j]);



  }

  printf("---------------------------------------- \n");


  return 0;


}
