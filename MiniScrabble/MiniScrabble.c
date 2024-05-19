#include <ctype.h>
#include <stdio.h>
/*En el juego de Scrabble, los jugadores crean palabras para ganar puntos, y el número de puntos ... 
es la suma de los valores de puntos de cada letra de la palabra.
Por ejemplo, si quisiéramos puntuar la palabra "CODE", notaríamos que la 'C' vale 3 puntos, la 'O' vale 1 punto, ... 
... la 'D' vale 2 puntos y la 'E' vale 1 punto. Sumando estos, obtenemos que "CODE" vale 7 puntos.

A tener en cuenta:
[1] ESTE PROGRAMA MANEJA LOS CARACTERES DEL ASCII REDUCIDO; SOLO LETRAS A-Z PURAS (SIN TILDES, ETC). CARACTERES FUERA DE ESTO ...
... NO GENERARÁ PUNTOS.

[2] SOLO SE PUNTUARÁ LA PRIMERA CADENA DE CARACTERES, O SEA, EL FORMATO ES PALABRA Y NO PALABRA PALABRA. LAS PALABRAS ...
... LUEGO DEL ESPACIO SERÁN IGNORADAS Y LIMPIADAS DEL BUFER.


*/
int points(char players_word[][80], int fila);

int main()
{   
    char players_word[2][80];
    int playerspoints[2];
    printf("Points per letter:\n A = 1 | B = 3 | C = 3 | D = 2 | E = 1 | F = 4 | G = 2 | H = 4 | I = 1 | J = 8 | K = 5 | L = 1 | M = 3 \n|"
    " N = 1 | O = 1 | P = 3 | Q = 10 | R = 1 | S = 1 | T = 1 | U = 1 | V = 4 | W = 4 | X = 8 | Y = 4 | Z = 10 \n");
    for (int j = 0; j < 2; j++)
    {
        printf("Player %i word: ", j + 1);
        scanf("%79s", players_word[j]);
        // Limpieza de bufer
        while (getchar() != '\n');
    }

    //Asignacion de puntajes
    playerspoints[0] = points(players_word, 0);
    playerspoints[1] = points(players_word, 1);
    
    //Resultados
    if (playerspoints[0] > playerspoints[1])
    {
        printf("Player 1 wins!\n");
    }
    else if (playerspoints[0] < playerspoints[1])
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

//FUNCIONES
int points(char players_word[][80], int fila)
{
    int count = 0, puntos = 0;
    char letra;
    do
    {
        letra = players_word[fila][count];
        if ((letra >= 65 && letra <= 90) || (letra >= 97 && letra <= 122))
        {
            switch (tolower(letra))
            {
                case 'a':
                    puntos += 1;
                    break;
                case 'b':
                    puntos += 3;
                    break;
                case 'c':
                    puntos += 3;
                    break;
                case 'd':
                    puntos += 2;
                    break;
                case 'e':
                    puntos += 1;
                    break;
                case 'f':
                    puntos += 4;
                    break;
                case 'g':
                    puntos += 2;
                    break;
                case 'h':
                    puntos += 4;
                    break;
                case 'i':
                    puntos += 1;
                    break;
                case 'j':
                    puntos += 8;
                    break;
                case 'k':
                    puntos += 5;
                    break;
                case 'l':
                    puntos += 1;
                    break;
                case 'm':
                    puntos += 3;
                    break;
                case 'n':
                    puntos += 1;
                    break;
                case 'o':
                    puntos += 1;
                    break;
                case 'p':
                    puntos += 3;
                    break;
                case 'q':
                    puntos += 10;
                    break;
                case 'r':
                    puntos += 1;
                    break;
                case 's':
                    puntos += 1;
                    break;
                case 't':
                    puntos += 1;
                    break;
                case 'u':
                    puntos += 1;
                    break;
                case 'v':
                    puntos += 4;
                    break;
                case 'w':
                    puntos += 4;
                    break;
                case 'x':
                    puntos += 8;
                    break;
                case 'y':
                    puntos += 4;
                    break;
                case 'z':
                    puntos += 10;
                    break;

                default:
                    break;
            }
        }

        count++;
    }
    while (players_word[fila][count] != '\0');
    return puntos;
}