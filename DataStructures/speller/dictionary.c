
// Implements a dictionary's functionality
#include <unistd.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "dictionary.h"
#include <string.h>
#include <strings.h>

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;

int WORD_COUNT = 0;
// Hash table
node *table[N];

// Función para eliminar espacios en blanco y nuevos caracteres al final de la cadena
void trimWhitespace(char *str) {
    int len = strlen(str);
    while (len > 0 && isspace((unsigned char)str[len - 1])) {
        str[len - 1] = '\0';
        len--;
    }
}



// Returns true if word is in dictionary, else false

bool check(const char *word)
{


    if (word == NULL || word[0] == '\0') {
        return false;
    }


    node* currentNode = NULL;

    for (currentNode = table[hash(word)]; currentNode != NULL; currentNode = currentNode->next){
        if(strcasecmp(word, currentNode->word) == 0){
            return true;
        }


    }

    return false;
}



// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    return toupper(word[0]) - 'A';
}


//Toma el puntero de la cabecera y trabaja sobre él. Solo para nodos superiores a nodo inicial de la tabla
//No puede pasarse como Node el inicio de la tabla
void loadOnNode(const char *str_buffer, node *currentNode, node **LastNode_Ptr){
    if (currentNode == NULL) {
         // Error: El nodo no debe ser nulo
         return;
    }

    //Reutilizacion de punteros a ultimo nodo trabajado
    if (*LastNode_Ptr == NULL){
        *LastNode_Ptr = currentNode;
    }

    else{
        currentNode = *LastNode_Ptr;
    }

    while (currentNode->next != NULL){
        currentNode = currentNode->next;
    }

    //Crear nuevo nodo
    node *newNode = (node*) malloc(sizeof(node));
    if (newNode == NULL) {
        perror("No se pudo asignar memoria para el nuevo nodo");
        return;
    }

    strcpy(newNode->word, str_buffer);// Copiar la cadena

    trimWhitespace(newNode->word);
    WORD_COUNT++;
    newNode->next = NULL;

    //Asociar nuevo nodo con su nodo padre
    currentNode->next = newNode;
    *LastNode_Ptr = newNode;
}


void replaceWord(char buffer[], char fromReplace, char toReplace){
    for (int i = 0; i < LENGTH; i++){
        if (buffer[i] == fromReplace){
            buffer[i] = toReplace;
            break;
        }

    }
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{

    FILE *file = fopen(dictionary, "r");

    if (file == NULL){
        perror("No se pudo abrir el archivo");
        return false;
    }

    char str_buffer[LENGTH + 1];
    unsigned int hashIndex = 0;

    // Inicializar el buffer
    memset(str_buffer, 0, sizeof(str_buffer));


    //Inicializar tabla
    for (int i = 0; i < N; i++){
        table[i] = (node*) malloc(sizeof(node));
        if (table[i] == NULL){
            printf("No se pudo inicializar nodo\n");
            fclose(file);
            return false;
        }
        table[i]->next = NULL;

        //Valgrind detecta no inicializacion de variables de estructuras y variables simples
        table[i]->word[0] = '\0';
    }

    //Crear matriz de punteros a nodos para recordarlos y no recorrer desde nodo origen a ultimo nodo
    //Este enfoque ahorra mucho trabajo para el ordenador

    node *LastNodes[N];
    for (int i = 0; i < N; i++)
    {
        LastNodes[i] = NULL;
    }
    

    //Carga del diccionario en la tabla
    while(fgets(str_buffer, LENGTH + 1, file) != NULL){

        replaceWord(str_buffer, 0x0a, '\0');
        if (str_buffer[0] == '\0'){
            break;
        }
        hashIndex = hash(str_buffer);
        loadOnNode(str_buffer, table[hashIndex], &LastNodes[hashIndex]);

    }

    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return WORD_COUNT;
}

// Unloads dictionary from memory, returning true if successful, else false

bool unload(void)
{

    for (unsigned int i = 0; i < N; i++){
        node *tmp = table[i];
        node *cursor = table[i];

        while (cursor != NULL){
            tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }

    return true;
}


