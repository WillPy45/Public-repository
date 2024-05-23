#include <stdio.h>
/* Dado un monto en centavos, determina la cantidad mínima de monedas que debes dar como cambio */

//Prototipos
int get_integer(char* imprimir); //Entrada de solo enteros.
int CambioMinimo(int Centavos, int *dir1, int *dir2, int *dir3, int *dir4); //

//Programa
int main(void)
{
    // Variables
    int C25 = 0, C10 = 0, C5 = 0, C1 = 0; // Monedas
    // Direcciones de memoria de las variables de monedas
    int *dirC25 = &C25;
    int *dirC10 = &C10;
    int *dirC5 = &C5;
    int *dirC1 = &C1;

    int Centavos = 0;
   
    // [Entrada]
    do
    {
    
        printf("Rango de cambio debido: números enteros positivos (no 0)\n");
        Centavos = get_integer("Cambio debido en centavos: ");
            
        if (Centavos <= 0)
        {
            printf("El cambio debido está fuera del rango. Introduce un número entero mayor que 0.\n");
        }
        
    }while (Centavos <= 0);

    // [Proceso] Determinar la cantidad mínima de monedas
    int MonedasNecesarias = CambioMinimo(Centavos, dirC25, dirC10, dirC5, dirC1);

    // [Salida] Monedas necesarias y distribución de denominaciones de monedas
    printf("Monedas necesarias: %i\nDistribución: (%d x 25c | %d x 10c | %d x 5c | %d x 1c)\n", MonedasNecesarias, C25, C10, C5, C1);
    return 0;
}


//Funciones
int get_integer(char* imprimir){
    //Esta funcion lee hasta la ultima entrada valida.
    int num = 0;
    int Verif = 0;
    //Si entrada es correcta funcion scanf retorna 1, caso incorrecto, retorna 0;
    do
    {
        printf("%s", imprimir); //Imprime segun la entrada get_integer("TEXTO QUE SE IMPRIME")
        Verif = scanf("%i", &num);
        //Si scanf falló, limpiar bufer
        if (Verif == 0 || getchar() != '\n')
        {
            while (getchar() != '\n'); //LIMPIEZA DE BUFER
            Verif = 0; //Declarar invalido por encontrar un caracter prohibido
        }
    } while (Verif == 0);
   
    return num;
    
}

int CambioMinimo(int Centavos, int *dir1, int *dir2, int *dir3, int *dir4)
{
    int Cents = Centavos;
    int Monedas = 0;

    do
    {
        if (Cents >= 25)
        {
            Cents -= 25;
            Monedas++;
            *dir1 += 1; // contador +1 de monedas de 25 centavos
        }
        else if (Cents >= 10)
        {
            Cents -= 10;
            Monedas++;
            *dir2 += 1; // contador +1 de monedas de 10 centavos
        }
        else if (Cents >= 5)
        {
            Cents -= 5;
            Monedas++;
            *dir3 += 1; // contador +1 de monedas de 5 centavos
        }
        else if (Cents >= 1)
        {
            Cents -= 1;
            Monedas++;
            *dir4 += 1; // contador +1 de monedas de 1 centavo
        }
    } while (Cents > 0);

    return Monedas;
}
