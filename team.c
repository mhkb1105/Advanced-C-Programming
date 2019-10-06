//
// EECS2031 team.c
//
// This is a Program for maintaining a personal team of soccer players
//



#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <assert.h>

//**********************************************************************
// Linked List Definitions
//  Define your linked list nodes and pointer types
//  here for use throughout the file.

struct player {
  char * familyName;
  char * firstName;
  char position;
  int value;
};

struct node {
  struct player playerInfo;
  int value;
  struct node * next;
};


//**********************************************************************

// Linked List and Supporting Function Declarations:

// A. Functions that modify the linked list
struct node* add_to_list(struct node*, struct node*, struct player*);
void dismissPlayer(struct player*);
void dismissNode(struct node *node_to_delete);
struct node * deleteNode(struct node * head, char familyName[]);
struct node * findPlayerByFamilyName(struct node *head, char familyName[]);
void findPlayerByValue(struct node *head, int value);
void printPlayerInfo(struct node *found_node);
void printTeam(struct node *head);
void deleteTeam(struct node*);

// -- -- -- -- -- -- -- -- -- -- -- //

// B. The rest of the functions
void safegets (char s[], int arraySize);        // gets without buffer overflow
void familyNameDuplicate (char familyName[]);   // marker/tester friendly
void familyNameFound (char familyName[]);       //   functions to print
void familyNameNotFound (char familyName[]);    //     messages to user
void familyNameDeleted (char familyName[]);
void printTeamEmpty (void);
void printTeamTitle(void);
void printNoPlayersWithLowerValue(int value);

//**********************************************************************
// Program-wide Constants
//

const int MAX_LENGTH = 1023;
const char NULL_CHAR = '\0';
const char NEWLINE = '\n';
const char GOALKEEPER = 'G';
const char DEFENDER = 'D';
const char MIDFIELDER = 'M';
const char STRIKER = 'S';



//**********************************************************************
// Main Program
//

int main (void)
{
    const char bannerString[]
        = "\nPersonal Team Maintenance Program.\n\n";
    const char commandList[]
        = "Commands are I (insert), D (delete), S (search by name),\n"
          "  V (search by value), P (print), Q (quit).\n";


    // Declare linked list head.

    struct node *head = NULL; // head of linked list
    struct node *current = NULL; // tail of the linked list (null)
    struct player * playerInfo; // define a struct player
    playerInfo = malloc(sizeof(struct player)); // initialize it


    // announce start of program
    printf("%s",bannerString);
    printf("%s",commandList);

    char response;
    char input[MAX_LENGTH+1];

    char * inputString; // String input from user
    int inputInt; // will be used to store value whenever a user inputs an int

    do
    {
        printf("\nCommand?: ");
        safegets(input,MAX_LENGTH+1);
        // Response is first char entered by user.
        // Convert to uppercase to simplify later comparisons.
        response = toupper(input[0]);

        if (strlen(input) > 1) // checks if user inputs more than one char, if so print error
          printf("\nInvalid command.\n%s\n",commandList);

        else

        if (response == 'I')
        {


          //************** 1. PROVIDE FAMILY NAME *****************
          printf("  family name: ");
          safegets(input, MAX_LENGTH+1); // grabs the info and puts it in input
          inputString = &input[0]; // a pointer that points to the address of the string inputted by user

          playerInfo->familyName = malloc(sizeof(inputString)); // initializes the pointer familyName to the size of the input of user
          strcpy(playerInfo->familyName, inputString); // copies the input into familyName. This way we can use inputString doesn't point to familyName

          // **************** 2. PROVIDE FIRST NAME *****************
          printf("  first name: ");
          safegets(input, MAX_LENGTH+1);
          inputString = &input[0];
          playerInfo->firstName = malloc(sizeof(inputString));
          strcpy(playerInfo->firstName, inputString);

          // ********************* 3. PROVIDE POSITION ************************
          printf("  position: ");
          safegets(input, MAX_LENGTH+1);
          inputString = &input[0];
          playerInfo->position = *inputString;


          // ********************* 4. PROVIDE VALUE ***************************

          printf("  value: ");
          safegets(input, MAX_LENGTH+1);
          playerInfo->value = atoi(input); // converts string to int, used to avoid invalid command problem

          // printf("\nTyped Family Name: %s\n",playerInfo->familyName);
          // printf("Typed First Name: %s\n",playerInfo->firstName);
          // printf("Typed position: %c\n",playerInfo->position);
          // printf("Typed value: %d\n",playerInfo->value);



      if (head == NULL) { //checks if team is empty, if so insert node at the beginning of the list
        head = add_to_list(head, head, playerInfo); // define head to be the first node
        current = head; // current will be used later which will always point to the next value of the  last element in the lis (which is always NULL)
                        // it helps us keep track of the tail of the node

      } else { // if list is not empty then proceed below:

        struct node * temp_node = add_to_list(head, current, playerInfo); //add the new node and set it to a temporary node

        if (temp_node->next != NULL
            && strcmp(temp_node->next->playerInfo.familyName, head->playerInfo.familyName) == 0
            && temp_node->next->playerInfo.position ==  head->playerInfo.position)
            {// checks if the new inserted node has been inserted at the beginining of the list,
            // if so, then update the head!

              head = temp_node; // updates the head with the new temp_node because it has been inserted at the beginning.

            } else { // if the newly inserted node was not inserted at the head then update current node if necessary.

              if (current != NULL)
              current = current->next; // move current one more to keep track if necessary to keep track of tail
            }

      }

            // Insert a player entry into the linked list.
            // Maintain the list in correct order (G, D, M, S).
            //   ADD STATEMENT(S) HERE

            // USE THE FOLLOWING PRINTF STATEMENTS WHEN PROMPTING FOR DATA:
            // printf("  family name: ");
            // printf("  first name: ");
            // printf("  position: ");
            // printf("  value: ");

        }
        else if (response == 'D')
        {
            // Delete a player from the list.
            printf("\nEnter family name for entry to delete: ");
            safegets(input, MAX_LENGTH+1);
            head = deleteNode(head, input); // delete node
        }
        else if (response == 'S')
        {
            // Search for a player by family name.

            printf("\nEnter family name to search for: ");
            safegets(input, MAX_LENGTH+1);
            struct node *found_node = findPlayerByFamilyName(head, input);

            if (found_node == NULL) { // if no nodes found then family not found, display message
              familyNameNotFound(input);
            }
            else
            { // if family found, display family name
              familyNameFound(found_node->playerInfo.familyName);
              printPlayerInfo(found_node); // prints the info of the searched player
            }

        }
        else if (response == 'V')
        {
            // Search for players that are worth less than or equal a value.

            printf("\nEnter value: ");
            safegets(input, MAX_LENGTH+1);
            findPlayerByValue(head, atoi(input));

            //   ADD STATEMENT(S) HERE

        }
        else if (response == 'P')
        {
            // Print the team.

            //   ADD STATEMENT(S) HERE
            struct node *curr_print = head;
            printTeam(curr_print);

            // while (curr_print != NULL) {
            //   printf("\nFamily Name: %s\n",curr_print->playerInfo.familyName);
            //   printf("First Name: %s\n",curr_print->playerInfo.firstName);
            //   printf("position: %c\n",curr_print->playerInfo.position);
            //   printf("value: %d\n",curr_print->playerInfo.value);
            //   printf("\n");
            //   curr_print = curr_print->next;
            // }

        }
        else if (response == 'Q')
        {

             // do nothing, we'll catch this case below
        }
        else
        {

            // do this if no command matched ...

            printf("\nInvalid command.\n%s\n",commandList);
        }
    } while (response != 'Q');

    // Delete the whole linked list that hold the team.
      if (head != NULL) {
       dismissPlayer(playerInfo);
        deleteTeam(head);
        head = NULL;
        current = NULL;
      }

    // Print the linked list to confirm deletion.
      printTeam(head);


    return 0;
}

//**********************************************************************
// Support Function Definitions

// Function to get a line of input without overflowing target char array.
void safegets (char s[], int arraySize)
{
    int i = 0, maxIndex = arraySize-1;
    char c;
    while (i < maxIndex && (c = getchar()) != NEWLINE)
    {
        s[i] = c;
        i = i + 1;
    }
    s[i] = NULL_CHAR;
}

// Function to call when user is trying to insert a family name
// that is already in the book.
void familyNameDuplicate (char familyName[])
{
    printf("\nAn entry for <%s> is already in the team!\n"
           "New entry not entered.\n",familyName);
}

// Function to call when a player with this family name was found in the team.
void familyNameFound (char familyName[])
{
    printf("\nThe player with family name <%s> was found in the team.\n",
             familyName);
}

// Function to call when a player with this family name was not found in the team.
void familyNameNotFound (char familyName[])
{
    printf("\nThe player with family name <%s> is not in the team.\n",
             familyName);

}

// Function to call when a family name that is to be deleted
// was found in the team.
void familyNameDeleted (char familyName[])
{
    printf("\nDeleting player with family name <%s> from the team.\n",
             familyName);
}

// Function to call when printing an empty team.
void printTeamEmpty (void)
{
    printf("\nThe team is empty.\n");
}

// Function to call to print title when whole team being printed.
void printTeamTitle (void)
{
    printf("\nMy Team: \n");
}

// Function to call when no player in the team has lower or equal value to the given value
void printNoPlayersWithLowerValue(int value)
{
	printf("\nNo player(s) in the team is worth less than or equal to <%d>.\n", value);
}

//**********************************************************************
// Add your functions below this line.


struct node*  add_to_list(struct node * head, struct node * list, struct player * value) {

  struct node * new_node;
  struct node * curr_node, *prev_node = NULL;

  new_node = malloc(sizeof(struct node));
  
  if (new_node == NULL) {
    printf("Error: malloc failed in add_to_list\n");
    exit(EXIT_FAILURE);
  }

  if (head == NULL) { // if list is empty
    new_node->playerInfo = *value;
    new_node->next = list;

  } else { // if list is not empty

  curr_node = head;

  while (curr_node != NULL) { 

    if (value->position == GOALKEEPER // if inserting at position G keep updating prev and curr nodes until reaches correct place
        && curr_node->playerInfo.position != DEFENDER
        && curr_node->playerInfo.position != MIDFIELDER
        && curr_node->playerInfo.position != STRIKER
       )
    {
       prev_node = curr_node;
       curr_node = curr_node->next;
    }


    else if (value->position == DEFENDER
             && curr_node->playerInfo.position != MIDFIELDER
             && curr_node->playerInfo.position != STRIKER
            )
    {
      prev_node = curr_node;
      curr_node = curr_node->next;
    }

    else if (value->position == MIDFIELDER
             && curr_node->playerInfo.position != STRIKER
            )
    {
      prev_node = curr_node;
      curr_node = curr_node->next;
    }
    else if (value->position == STRIKER)
    {
      char prev_family[MAX_LENGTH+1], curr_family[MAX_LENGTH+1];

      prev_node = curr_node;
      curr_node = curr_node->next;
    }

    else {
      break; //break out of loop if correct position found
    }

  }

    if (findPlayerByFamilyName(head, value->familyName) != NULL) { // if family already exists, send error message.
      familyNameDuplicate(value->familyName);
   
    } else { // if no duplicate

      if (prev_node == NULL) { // if node will be inserted at the beginning of the node
        new_node->playerInfo = *value;
        new_node->next = curr_node;

    } else { // if node will be inserted anywhere else
        new_node->playerInfo = *value;
        new_node->next = curr_node;
        prev_node->next = new_node;
      }
    }
  }

  return new_node;
}



void dismissPlayer(struct player * a_player)
{
  assert(a_player != NULL);
  free(a_player->familyName);
  free(a_player->firstName);
  free(a_player);
}

void dismissNode(struct node *node_to_delete) {
  free(node_to_delete); // delete node
}


struct node * deleteNode(struct node * head, char familyName[])
{
  struct node *prev_node, *curr_node;

  //if node is first node:
  if (strcmp(head->playerInfo.familyName, familyName) == 0) {
    prev_node = head;
    head = prev_node->next;
    free(prev_node);


  } else {
    curr_node = head;

    while (curr_node != NULL && strcmp(curr_node->playerInfo.familyName, familyName) != 0) { //keep updating current node until family Name found
      prev_node = curr_node;
      curr_node = curr_node->next;
    }

    if (curr_node == NULL) { // if current node reaches the end (null) then family not found
      familyNameNotFound(familyName);
    }

     else { // if family is found then update the previous node, delete it, then display message
       prev_node->next = curr_node->next;
       free(curr_node);
       familyNameDeleted(familyName);
    }
  }

  return head;
}


struct node * findPlayerByFamilyName(struct node *head, char familyName[]) {
  struct node *curr_node;
  curr_node = head;
  while (curr_node != NULL && strcmp(curr_node->playerInfo.familyName, familyName) != 0) { // update curr node until family name found
    curr_node = curr_node->next;
  }

  return curr_node; // if family name not found, this will return NULL. Captured in the 'S' condition up above.
}


void findPlayerByValue(struct node *head, int value) {
  struct node *curr_node;
  int flag = 0; // if atleast 1 player is found this will be set to 1
  curr_node = head;

  while (curr_node != NULL) { // print all matched values
    if (curr_node->playerInfo.value <= value) {
      printf("\n%s\n",curr_node->playerInfo.familyName);
      printf("%s\n",curr_node->playerInfo.firstName);
      printf("%c\n",curr_node->playerInfo.position);
      printf("%d\n",curr_node->playerInfo.value);
      flag = 1;
    }

    curr_node = curr_node->next;  
  }

  if (flag == 0) // if flag = 0 then no matched value
    printNoPlayersWithLowerValue(value);
}


void printPlayerInfo(struct node *found_node) {
  printf("\n%s\n",found_node->playerInfo.familyName);
  printf("%s\n",found_node->playerInfo.firstName);
  printf("%c\n",found_node->playerInfo.position);
  printf("%d\n",found_node->playerInfo.value);
}

void printTeam(struct node *head) {

  if (head == NULL) {
    printTeamEmpty();
  }

  else
    printf("\nMy Team:\n");
  while (head != NULL) {

    printf("\n%s\n",head->playerInfo.familyName);
    printf("%s\n",head->playerInfo.firstName);
    printf("%c\n",head->playerInfo.position);
    printf("%d\n",head->playerInfo.value);
    head = head->next;
  }
}

void deleteTeam(struct node *head) {
  struct node *curr_node = head;

  while (head != NULL) {
    curr_node = head;
    dismissNode(curr_node);
    head = head->next;

  }
}
