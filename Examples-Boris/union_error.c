/**
 * @file union_error.c
 * @author Boris Snäll (boris.snall@yaelev.se)
 * @brief Dummy example for the use of unions
 * @version 0.1
 * @date 2021-10-06
 */
#include <string.h>
#include <stdio.h>


// dummy info for FILE error handling
typedef struct 
{
    char path[50]; // MAX_PATH ?
    unsigned long size;
    unsigned char flags; // read, write, execute, folder, etc
} err_file_t;

// dummy info for NETWORK error handling
typedef struct 
{
    unsigned int bytes;
    unsigned int speed;
    char protocol[10]; 
} err_network_t;

// dummy info for PRINTER error handling
typedef struct
{
    unsigned int paper;
    unsigned int ink;
} err_printer_t;

// enumeration with all possible error types
// --> this is used as switch selector
typedef enum
{
    E_OK = 0,
    E_FILE,
    E_NETWORK,
    E_PRINTER,
    E_BLABLA, // etc
} error_t;

typedef struct 
{
    // this is "the switch"
    int type;

    // depending on the switch we use ONLY one of these structs
    // -->> error type defines which error structure
    union
    {
        err_file_t ef;
        err_network_t en;
        err_printer_t ep;
    };
} err_generic_t;

/**
 * @brief Set of printing functions for each type. In a more real example
 * we should pass the pointer to the struct generic instead of a copy/value.
 */

void print_err_file(err_generic_t e)
{
    printf("err_file_t:\tpath: %s - size: %lu - flags: 0x%X\n", e.ef.path, e.ef.size, (unsigned)e.ef.flags);
}

void print_err_network(err_generic_t e)
{
    printf("err_network_t:\tbytes: %u - speed: %u - protocol: %s\n", e.en.bytes, e.en.speed, e.en.protocol);
}

void print_err_printer(err_generic_t e)
{
    printf("err_printer_t:\tink: %u - paper: %u\n", e.ep.ink, e.ep.paper);
}

/**
 * @brief Dummy example for handling errors with a union
 * 
 * @param e The generic structure containing the rest of the possible error structs
 * @return int 
 */
int err_handler(err_generic_t e)
{
    printf(">> error handler\n");
    printf(">> it should print the values of initialization\n");
    printf(">> (check the switch on main)\n");

        switch (e.type)
    {
    case E_OK:
        printf("No error :)\n"); break;
    case E_FILE:
        print_err_file(e); break;
    case E_NETWORK:
        print_err_network(e); break;
    case E_PRINTER:
        print_err_printer(e); break;
    default:
        printf("error undefined!\n"); break;
    }

    // do something with the error
    printf("\n");
    return e.type;
}

/**
 * @brief Prints all the individual values of each inner struct WITHOUT the
 * use of the switch. NOT SAFE. Expect garbage. 
 * @param e 
 */
void dangerous_print(err_generic_t e)
{
    printf(">> dangerous_print\n");
    printf(">> it should print garbage in the structs that are excluded from type\n");
    print_err_file(e);
    print_err_network(e);
    print_err_printer(e);
    printf("\n");}

int main()
{
    printf("Dummy program to demostrate the use of unions\n\n");

    err_generic_t e;

    // PLAY HERE:
    // change the value of "type" and use
    // different EXCLUSIVE structs inside of the union
    e.type = E_FILE;
    //e.type = E_NETWORK;
    //e.type = E_PRINTER;

    // print sizeof of the generic and individual structures
    printf("sizeofs:\ne: %lu\nef: %lu\nen: %lu\nep: %lu\n", sizeof(e), sizeof(e.ef), sizeof(e.en), sizeof(e.ep));
    printf("\n");

    // print address of each individual structure
    // note how all the inner structs share the SAME address
    printf("addresses:\n&e: %p\n&ef: %p\n&en: %p\n&ep: %p\n", &e, &e.ef, &e.en, &e.ep);
    printf("\n");

    // print type
    printf("error type: %d\n", e.type);
    printf("\n");

    // initialize with some values depending on the type
    switch (e.type)
    {
    case E_FILE:
        // use ONLY data related to err_file_t
        strcpy(e.ef.path, "c:\\blabla\\bla.txt");
        e.ef.size = 25;
        e.ef.flags = 0xAF;
        break;

    case E_NETWORK:
        // use ONLY data related to err_network_t
        e.en.speed = 20;
        e.en.bytes = 555;
        strcpy(e.en.protocol, "HTTP");
        break;

    case E_PRINTER:
        // use ONLY data related to err_printer_t
        e.ep.ink = 75;
        e.ep.paper = 80;
        break;

    default:
        printf("error undefined!\n");
        break;
    }

    // do something with the error
    err_handler(e);

    // Print the info without switching
    // -> expect garbage or even runtime error
    dangerous_print(e);

    return 0;
}