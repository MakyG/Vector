/**
 * \file    ioutils.c
 * \author  Tomáš Dulík
 * \date    16.2.2012
 * \brief   Miniknihovna pro načítání vstupu
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "ioutils.h"

bool get_string( char * line, int len );

/**
 * @brief   Loads a string from standard input that has its maximum lenght
 *          specified by a parameter or until the end-of-line character (\\n)
 *          is encountered. In case of unsuccessful loading and coming to
 *          an EOF (end of file), function calls exit() that quits the
 *          evaluation.
 * @param   line    Pointer to a text array containing the loaded input.
 * @param   len     Maximum lenght of loaded input.
 */
bool get_string( char * line, int len )
{
    if( fgets( line, len, stdin ) == NULL ) {
        printf( "End of file, finishing.\n" );
        return false;
    }

    return true;
#ifdef ECHO
    printf( "%s", line );
#endif
}

/**
 * @brief Read one line from stdin
 * @param[out] c
 * @param[in] maxLen
 * @return
 */
bool io_utils_get_string( char *c, int maxLen )
{
    if( c == NULL ) {
        return false;
    }

    return get_string( c, maxLen );
}

/**
 * @brief Loads one character from standard input.
 * @return Returns the loaded character.
 */
bool io_utils_get_char( char * c )
{
    char line[255];

    if( get_string( line, 255 ) == true ) {
        *c = line[0];
        return true;
    }

    return false;
}

/**
 * @brief   Loads a long type value from standard input.
 * @param   val     Pointer to a long type variable
 *                      where the loaded result is stored.
 * @return
 */
bool io_utils_get_long( long * val )
{
    long hodnota;
    int ok;
    char line[255];

    do {
        if( get_string( line, 255 ) == false ) {
            return false;
        }

        ok = sscanf( line, "%ld", &hodnota );

        if( ok != 1 ) {
            printf( "Incorrect format, try again.\n" );
        }
    } while( ok != 1 );

    *val = hodnota;
    return true;
}

/**
 * @brief   Loads double type variable from standard input.
 * @param   val     Pointer to a double type variable
 *                      where the result is stored.
 * @return
 */
bool io_utils_get_double( double * val )
{
    double hodnota;
    int ok;
    char line[255];

    do {
        if( get_string( line, 255 ) == false ) {
            return false;
        }

        ok = sscanf( line, "%lf", &hodnota );

        if( ok != 1 )
        { printf( "Incorrect format, try again.\n" ); }
    } while( ok != 1 );

    *val = hodnota;
    return true;
}

/**
 * @brief Clears one line of input.
 */
void io_utils_clear_stdin()
{
    while( fgetc( stdin ) != '\n' );
}
