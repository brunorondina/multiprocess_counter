#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/mman.h>
#include <sys/wait.h>
#include <unistd.h>

#define N_PROCESSOS 4 //Maximo de 4 processos

int numero_primo(int x) { //Funcao para encontrar numero primo
			int div = 0, i;
      for (i = 1; i <= x; i++) {
      if (x % i == 0) { 
				div++;
				}
      }
  if (div == 2)	return 1;
	else return 0;
}

int main() {
  pid_t filho[N_PROCESSOS];
  unsigned int a;
	char c;
	int fim=0;


  /* Definir flags de protecao e visibilidade de memoria */
  int protection = PROT_READ | PROT_WRITE;
  int visibility = MAP_SHARED | MAP_ANON;

  /* Criar area de memoria compartilhada */
  int *b; //Contador de numeros primos
  b = (int*) mmap(NULL, sizeof(int), protection, visibility, 0, 0);
	while(1){
	if (fim==1) break;
	//Atribui um numero lido a um processo, ate um maximo de 4 processos
	//Apos 4 processos serem atribuidos, espera ate que os 4 terminem e entao repete ate encontrar o fim da linha
  for (int i=0; i<N_PROCESSOS; i++) {
		scanf("%d%c", &a, &c);
		if (fim==1) break;
		if (c == '\n') fim=1;
    	filho[i] = fork();
   	if (filho[i] == 0) {
      /* Esta parte do codigo executa no processo filho */
      (*b) += numero_primo(a);
      exit(0);
    	}
	}
	for (int i=0; i<N_PROCESSOS; i++) {
    waitpid(filho[i], NULL, 0);
  	}
  }
	printf("%d\n", *b);
  return 0;

}
