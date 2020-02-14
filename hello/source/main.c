#include <stdio.h>
#include <OSBIND.h>

int main()
{
  printf("Hello World\n");
  /* Cconin :
   * https://freemint.github.io/tos.hyp/en/gemdos_chrinout.html#Cconin
   */
  Cconin(); // Attendre l'utilisation d'une touche du clavier
  return 0;
}
