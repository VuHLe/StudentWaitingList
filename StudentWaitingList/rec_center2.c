#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define CLASS_LEN 100
#define NAME_LEN 30
#define EMAIL_LEN 50

struct request{
	char class[CLASS_LEN+1];
	char first[NAME_LEN+1];
	char last[NAME_LEN+1];
	char email[EMAIL_LEN+1];;

	struct request *next;
};

struct request *add(struct request *list);
void printList(struct request *list);
void clearList(struct request *list);
int read_line(char str[], int n);

/**********************************************************
 * main: Prompts the user to enter an operation code,     *
 *       then calls a function to perform the requested   *
 *       action. Repeats until the user enters the        *
 *       command 'q'. Prints an error message if the user *
 *       enters an illegal code.                          *
 **********************************************************/
int main(void)
{
  char code;

  struct request *wait_list = NULL;  
  printf("Operation Code: a for adding to the ordered list,"
	  ", p for printing the list; q for quit.\n");
  for (;;) {
    printf("Enter operation code: ");
    scanf(" %c", &code);
    while (getchar() != '\n')   /* skips to end of line */
      ;
    switch (code) {
      case 'a': wait_list = add(wait_list);
		break;
      case 'p': printList(wait_list);
                break;
      case 'q': clearList(wait_list);
		return 0;
      default:  printf("Illegal code\n");
    }
    printf("\n");
  }
}
//---------------------------------------------------------------------
struct request *add(struct request *list)
{
	struct request *cur, *prev, *new_node;

	new_node = malloc(sizeof(struct request));
	if (new_node == NULL)
	{
		printf ("Database is full; loading error.\n");
		return list;
	}

 	printf ("Enter the student email address: ");
 	read_line(new_node->email, EMAIL_LEN);
	printf ("Enter the student class name: ");
        read_line(new_node->class, CLASS_LEN);
	printf ("Enter the student first name: ");
        read_line(new_node->first, NAME_LEN);
	printf ("Enter the student last name: ");
        read_line(new_node->last, NAME_LEN);

	for (cur = list; cur != NULL; cur = cur->next)
	{
		if ((cur != NULL) && ((strcmp(cur->email,new_node->email)==0) && (strcmp(cur->class,new_node->class)==0))
				  && ((strcmp(cur->first,new_node->first)==0) && (strcmp(cur->last,new_node->last)==0)))
		{
			printf ("Request already existed in the waiting list. \n");
			free(new_node);
			return list;
		}
	}

	 // If the list is empty
        if (list == NULL)
        {
                list = new_node;
		list->next = NULL;
		return list;
        }

	else 
	{
		for (cur = list, prev = NULL; 
			cur != NULL && strcmp(new_node->class, cur->class)>0;
			prev = cur, cur = cur->next)
		;

		for (; 
			cur != NULL && strcmp(new_node->class, cur->class)==0 && strcmp(new_node->last, cur->last)>0;
			prev = cur, cur = cur->next)
		;
		
		new_node->next = cur;
		if (prev == NULL)
		{
			return new_node;
		}
		else
		{
			prev->next = new_node;
			return list;
		} 
	}
}


/**********************************************************
 * printList: print the data  in the linked list passed   *
 * in as parameter                                        *
 **********************************************************/


void printList(struct request *list){

  struct request *p;

  printf("\nEmail\t\t\t\t\t\tFirst Name\tLast Name\t\t"
         "class\n");
  for (p =list; p != NULL; p = p->next)
    printf("%-50s%-15s%-15s%15s\n", p->email, p->first,p->last,
           p->class);

}

/*************************************************************
 * clearList: release the memory in the linked list passed   *
 * in as parameter                                           *
 *************************************************************/


void clearList(struct request *list)
{

 
  struct request *p;

  while(list!=NULL)
  {
         p = list;
         list = list->next;
         if(p!=NULL)
            free(p);
  }


}

int read_line(char str[], int n)
{
  int ch, i = 0;

  while (isspace(ch = getchar()))
    ;
  str[i++] = ch;
  while ((ch = getchar()) != '\n') {
    if (i < n)
      str[i++] = ch;
    
   }
   str[i] = '\0';
   return i;
}
