//hanger - word-guessing game|refactoring
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>


int main(){
char word[40], answer[40] = {0}, picture [10] [10] = {0}, description [200] = {0}, progress [26] = {0};
//word - which user needs to guess, answer - to read user's guesses,
//picture - symbos showing Hanger, description - riddle for word,
//progress - history of entered symbols
FILE* library;
//library - pointer to access word list
unsigned short int tries = 0,  i = 0,  j = 0,  word_len = 0;
//tries - amount of errors allowed, i and j - array indexes,
//word_len - length of a word
srand( time( NULL ) );
printf("%s", "Welcome to the game of Hanger!\n"
             "Here you should guess words by guessing letters\n"
             "which, as you think, may be there,\n"
             "or typing the whole word at once.\n"
             "You have 10 tries before the game ends. Good luck!\n"
             "Press Enter to continue.");
scanf( "%*c" );

library = fopen( "lib.txt", "r" );  //picking a word and its description from lib.txt
fscanf( library, "%hu", &j );
i = rand() % j;
while( i-- )
    {  //skipping j strings to pick word j+1
    do
        {
        j = fgetc(library);
        }while( j != '\n' );
    }
i = 0; //reading word till #
do
    {
    fscanf( library, "%c", &word[i] );
    }while( '#' != word[ i++ ] );
word[ --i ] = '\0';
word_len = i;
i = 0; //reading description till end of line
do
    {
    fscanf( library, "%c", &description[i] );
    }while( '\n' != description[ i++ ]);
description[ --i ] = '\0';
fclose(library);


for( i=0; i<10; i++ )  //filling picture with dots aka blank
    {
    for( j=0; j<10; j++ )
        {
        picture [i] [j] = '.';
        }
    }


tries = 11;
do        //game start
    {
    switch( tries )  //modifying picture according to number of errors
        {
        case 11: break;
        case 10: for( i=0; i<10; i++ )  //1st error - floor
                    {
                    picture[9][i] = '_';
                    } break;
        case 9: for( i=2; i<10; i++ )  //2nd error - pole
                   {
                   picture[i][1] = '|';
                   } break;
        case 8: picture[2][3] = '/';    //3rd error - support plank
                picture[3][2] = '/';
                break;
        case 7: for( i=1; i<7; i++ )   //4th error - plank
                   {
                   picture[1][i] = '_';
                   } break;
        case 6: picture[2][6] = '|';    //5th error - empty rope
                picture[3][6] = '|';
                break;
        case 5: picture[3][6] = '0';    //6th error - head
                break;
        case 4: picture[4][6] = '|';    //7th error - body
                picture[5][6] = '|';
                break;
        case 3: picture[4][5] = '/';    //8th error - right arm
                break;
        case 2: picture[4][7] = '\\';   //9th error - left arm
                break;
        case 1: picture[6][5] = '/';    //10th error - right leg
                picture[7][5] = '|';
                break;
        case 0: picture[6][7] = '\\';   //11th error - left leg
                picture[7][7] = '|';    //should actually never excecute
                break;
        }

    for( i=0; i<10; i++ )   //drawing picture
        {
        for ( j=0; j<10; j++ )
            {
            printf( "%c", picture[i][j] );
            }
        printf( "%c", '\n' );
        }

    for( i=0; i<word_len; i++ )   //writing word;
       { //if letter hasn't been picked (absent in progress), then '_' instead
       printf( "%c ", (strchr(progress, word[i]) != NULL) ? (word[i]) : ('_')  );
       }

    printf( "\n%s\n", description );    //writing description

    for( *answer='a'; *answer<='z'; *answer=*answer+1 )   //some compilers don't like this string
       {    //writing alphabet
            //if letter has been picked (present in progress), then '/' instead
       printf( "%c ", (strchr(progress,*answer) != NULL) ? ('/') : (*answer)  );
       if( *answer=='m')   //second string after letter 'm'
         {
         printf("%c",'\n');
         }
       }

    printf( "\nTries left: =%hu\n", tries );
    do  //getting user's answer (1st character of string entered)
        {
        scanf( "%s", answer );
        if(  strchr(progress, *answer) != NULL  )
          {//if letter has been picked (present in progress), then request to try again
          printf( "Letter \'%c\' has already been picked, "
                  "please choose another\n", *answer );
          *answer = 0;
          }
          else
          {
          if(  (*answer < 'a') || (*answer > 'z')   )
            {//if character entered isn't a leter, then request to try again
            printf( "Symbol \'%c\' not recognized, "
                    "please type English lowercase letter\n", *answer );
            *answer = 0;
            }
          }
        }while( !(*answer) );

    j = strlen( progress );   //Processing answer: new letter in history
    progress[j++] = *answer;
    progress[j] = 0;
    for( i=0; i<word_len; i++ )   //check if the letter is present in word
       {
       if( word[i]==*answer )
         {
         printf( "Letter %hu guessed!\n", i+1 );
         progress[j] = 1;
         }
       }
    if( !progress[j] ) //if not present
      {
      printf( "%s", "No match!\n" );
      tries--;
      }

    }while(   (tries > 0) && (strspn(word, progress) < word_len)   );//game end
    //if player is out of tries or all letters in word are guessed (present in progress)

if( tries )//when tries hit 0, player loses
    {//winning message
    printf( "..............\n"
            ".______.......\n"
            ".|./..|.......\n"
            ".|/...|.\\.../.\n"
            ".|.......\\0/..\n"
            ".|........|...\n"
            ".|........|...\n"
            ".|......./.\\..\n"
            "_|_______|_|__\n"
            "Word \"%s\" fully guessed! You win!", word );
    }
    else
    {//losing message
    printf( "%s", "..........\n"
                  ".______...\n"
                  ".|./..|...\n"
                  ".|/...0...\n"
                  ".|.../|\\..\n"
                  ".|....|...\n"
                  ".|.../.\\..\n"
                  ".|...|.|..\n"
                  ".|........\n"
                  "_|________\n"
                  "You lose. Better luck next time.");
    }
return 0;
}
