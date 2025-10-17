/* memcpy example */
#include <stdio.h>
#include <string.h>

struct {
  char name[40];
  int age;
} person, person_copy;

int main ()
{
  char myname[] = "Pierre de Fermat";

  /* using memcpy to copy string: */
  memcpy ( person.name, myname, strlen(myname)+1 );
  person.age = 46;

  /* using memcpy to copy structure: */
  memcpy ( &person_copy, &person, sizeof(person) );

  printf ("person original: %s, %d \n", person.name, person.age );
  printf ("person_copy: %s, %d \n", person_copy.name, person_copy.age );



  char memmove_char[] = "Michal";  
  memmove ( person.name, memmove_char, strlen(memmove_char)+1 );  

  /*
    The memcpy function is used to copy a block of
         data from a source address to a destination address.
  */


  return 0;
}