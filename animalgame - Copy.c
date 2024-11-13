// https://github.com/smrizzo/AnimalGuessingGame/blob/master/guess.c   

#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// lrb - reformatted and edited comments - 12/16-17/21

/*

Created a structure called Node that will represent my nodes for binary
tree. Declared char pointer which points to address in memory that has
name of animal or question

Declared three Node pointers which will be pointing address of parent
node, address of left node, and address of right node

*/

struct Node {
	char *data;
	struct Node *parent;
	struct Node *left;
	struct Node *right;
};

/*

Declared a global struct pointer called root which will always be
pointing to address of first node in tree in memory

Declared global integer variables NodeCount and LineCount to check for
corrupted file

*/

struct Node* root;
int NodeCount;
int LineCount;

/*

GetNewNode function takes in a struct node pointer, and a char pointer. 

The node pointer passed in as a parameter is specifically for setting
the newNode's parent pointer to its parent nodes address in memory

char pointer passed in as a parameter is for setting the newNode's data
pointer to the data passed in through the char pointer parameter(animal
or question to animal)

It creates a new struct node by requesting space in the heap using
malloc, it then sets both node pointer left and right to NULL.

This subroutine returns a node pointer which is pointing to the newNodes
address in memory

*/

struct Node* GetNewNode(struct Node* current, char *data)
{
	struct Node* newNode = (struct Node*)malloc(sizeof(struct Node));
	newNode->data = data;
	if(current != NULL)
	{
		newNode->parent = current;
	}
	else
	{
		newNode->parent = NULL;
	}
	newNode->left = NULL;
	newNode->right = NULL;
	NodeCount++;	
	return newNode;
}

/*

readline subroutine takes in a File pointer as its paramenter which is
pointing to the first line in the file which was just opened before it
was called

By using a char pointer which requests memory in the heap using malloc
of size 20 and then if more space is needed it reallocs more space of
size 20

The char pointer will be pointing to the address in memory we requested
where the line from the text file will be living

we get each character in the line of the file by storing in a int
variable c using getc() and assign each space in memory with that
character by using our char pointer

We get everything up to the newline then place a null terminator '\0' at
that location.  This subroutine returns a pointer pointing to the
address of our line from file

*/

char *readline(FILE *fptr)
{
	int c;
	char *ptr;
	int limit;
	int i;
	i = 0;
	limit = 20;
	ptr = malloc(limit);
	 while((c = getc(fptr)) != '\n')
  	 {

       if(c == EOF)
         {
           free(ptr);
           return NULL;
         }
       	else if(i == limit)
         {
           limit += 20;
           ptr = realloc(ptr, limit);
           ptr[i++] = (char)c;
        	}
        	else
        	{
            ptr[i++] = (char)c;

         }
	  }
		
   
	ptr[i] = '\0';
	return ptr;
}

/*

CountNewLines takes in a file pointer and just reads the entire file to
get a \n count for my global integer variable LineCount to check for
corrupted database

*/

void CountNewLines(FILE *fptr)
{
   char *ptr;
   while((ptr = readline(fptr)) != NULL)
   {
      if(ptr[0] == '\0')
      {
         LineCount++;
      }
      free(ptr);
   }
   free(ptr);

}


/*

UpdateDatabase subroutine takes in a struct node pointer I called
"current", and a File pointer as its parameters

If current is equal to NULL the function is then exited otherwise we
will print out what is living at the memory address of the data pointer
of the current node

If the current nodes left child is pointing to NULL we now know we
are a leaf node in our tree so printout to the file two newlines which
is how we set up the database

It then recursivly calls the function which traverses the binary tree in
a preorder fashion prioritizing the right child nodes before the left

This subroutine is void and prints out the binary tree into our database
which updates it

*/

void UpdateDatabase(struct Node* current, FILE *fpo)
{
	if(current != NULL)
	{
		fprintf(fpo,"%s\n", current->data);
		if(current->left == NULL)
		{
			fprintf(fpo,"\n");
			fprintf(fpo,"\n");
		}
		UpdateDatabase(current->right, fpo);
		UpdateDatabase(current->left, fpo);
	}
	
}

/*

FreeTree subroutine does exactly what you think, it takes in a struct
Node pointer which I called current

It traverses through the binary tree recursively in a postorder fashion
freeing the memory that was allocated for the char data pointer in each
node which then also free our getline() mallocs

It also frees the current node address in memory as well as the memory
addresses that the left and right node pointers are pointing to

*/

void FreeTree(struct Node* current)
{
	if(current == NULL)
	{
		return;
	}
	else
	{

		FreeTree(current->left);
		FreeTree(current->right);
		free(current->data);
		free(current);

	}
}

/*

InsertFirstAnimal subroutine was created specifically to handle the case
where the file is empty, and if the file didn't exist so we created a
new empty file

It takes in a FILE pointer as its parameter

It then proceeds to ask the user what animal it is, gets that animal
using getline() which allocates and reallocates memory if needed in the
heap for my char FirstAnimal pointer to point to

It then updates database based on user's input and then frees the
memory we are using for FirstAnimal char pointer

*/

void InsertFirstAnimal(FILE *fptr)
{	
	
	char *FirstAnimal = NULL;
	size_t first_animal_length = 0;
	size_t char_read = 0;

	printf("\n");
	printf("What is it (with article)? ");
	char_read = getline(&FirstAnimal, &first_animal_length, stdin);
	FirstAnimal[char_read - 1] = '\0';
	
	fprintf(fptr,"%s\n", FirstAnimal);
	fprintf(fptr,"\n");
	fprintf(fptr,"\n");

	free(FirstAnimal);
	
}

/*

BuildTree subroutine takes in a struct Node pointer which I called
current, a File pointer, and a char pointer

I first create the first node by using global variable root then check
while the char pointer gets what my readline function returns is not
equal to NULL keep getting lines from file

If there is a null terminator at first index of char pointer we know we
have found a child or leaf node in the file so go down to next item in
file that's not a newline '\0'

Because I have built the tree to have yes's on the right child it
essentially keeps building the tree to the right until it finds a
child/leaf node

Then jumps up to previous node and checks if left node exist or not, if
it does it's not a child, if it doesn't build it and check next thing in
file to see if it's a leaf node or not

This process keeps going until the tree is built and resets current
pointer to point to address that root is pointing to and returns
current

*/

struct Node* BuildTree(struct Node* current, FILE *fptr, char *ptr)
{
		ptr = readline(fptr);
		root = GetNewNode(root, ptr);
		current = root;
		while((ptr = readline(fptr)) != NULL)
		{
			if(ptr[0] == '\0')
			{
			
				free(ptr);
				ptr = readline(fptr);
				free(ptr);
				ptr = readline(fptr);
				if(ptr == NULL)
				{
				   free(ptr);	
			           break;
				}
				else
				{
					while(current->parent->left != NULL)
					{
						current = current->parent;
					}
					current->parent->left = GetNewNode(current->parent, ptr);
					current = current->parent->left;
				
				}				
				
			}
			else if(ptr[0] != '\0')
			{
				current->right = GetNewNode(current, ptr);
				current = current->right;			
			}		
			
		}
		current = root;
		return current;
}


/*

Insert subroutine takes in a struct Node pointer(current), char pointer
for NewAnimal, char pointer for NewQuestion, and char pointer for
NewAnswer

Insert is only called when my program guesses the wrong animal, and
inserts the NewAnimal and NewQuestion in the binary tree where it needs
to be

It says if current node is only thing in tree then make newQuestion the
root, NewAnimal the left child if NewAnswr is no, or make right child if
the NewAnswer is yes

It also covers all other cases where there is more then one node in
tree, it re-arranges the binary tree accordingly

Since current is pointing to the address of the animal we guessed wrong,
current nodes parent points to NewQuestion and NewQuestion left child
and right child will either be

left child:Old animal right child: New animal is NewQuestion is yes,
left child:New Animal and right child:Old Animal if NewAnswer is no
reset current to point to address of root node

Insert will return current node which is pointing at root of binary tree
in memory and frees NewAnswer from memory

*/

struct Node* Insert(struct Node* current, char *NewAnimal, char *NewQuestion, char *NewAnswer)
{
	struct Node* Animal;
	struct Node* Question;

	if(current->parent == NULL)
	{
		Question = NULL;
		Question = GetNewNode(Question, NewQuestion);
		Animal = GetNewNode(Question, NewAnimal);

		if(NewAnswer[0] == 'Y' || NewAnswer[0] == 'y')
		{
			Question->right = Animal;
			Question->left = current;
		}
		else if(NewAnswer[0] == 'N' || NewAnswer[0] == 'n')
		{
			Question->right = current;
			Question->left = Animal;
		}
		current->parent = Question;
		root = Question;

	}
	else
	{
		Question = GetNewNode(current->parent, NewQuestion);
		Animal = GetNewNode(Question, NewAnimal);

		if(NewAnswer[0] == 'Y' || NewAnswer[0] == 'y')
		{	
			Question->left = current;
			Question->right = Animal;
		}
		else if(NewAnswer[0] == 'N' || NewAnswer[0] == 'n')
		{
			Question->right = current;
			Question->left = Animal;
		}
		
		if(current->parent->left == current)
		{
			current->parent->left = Question;
			current->parent = Question;
			
		}
		else if(current->parent->right == current)
		{
			current->parent->right = Question;
			current->parent = Question;
			
		}
	}
	free(NewAnswer);	
	current = root;
	return current;
}
	

/*

PlayGame subroutine takes in a struct Node pointer(current) as its
parameter

PlayGame essentially traverses through the tree based on whether the
user enters a yes or no.  If yes go to right child address in memory, if
no go to left child address in memory

Once it reaches a leaf node(animal) it will ask the user if it's that
animal.  If it guesses right then game is over. Both tree and database
remain the same

If it guesses wrong and the user enters a no instead at leaf node will
then proceed to ask what the NewAnimal is, a NewQuestion to
differentiate the oldanimal and newanimal, the answer for new animal

PlayGame then calls the Insert subtroutine passing current node,
NewAnimal, NewQuestion, and NewAnswer all as pointers.  Insert will
return the root nodes address and then Insert will return that
address as well

*/

struct Node* PlayGame(struct Node* current)
{
	
	char *YesOrNo = NULL;
	char *NewAnimal = NULL;
	char *NewAnswer = NULL;
	char *NewQuestion = NULL;
	size_t new_animal_length = 0;
	size_t new_answer_length = 0;
	size_t new_question_length = 0;
	size_t YesOrNo_length = 0;
	size_t char_read = 0;
	while(current->left != NULL)
	{
		
			printf("%s ", current->data);
			getline(&YesOrNo, &YesOrNo_length, stdin);
			/*YesOrNo[char_read - 1] == '\0';*/
			if(YesOrNo[0] == 'Y' || YesOrNo[0] == 'y')
			{
				current = current->right;
			}
			else if(YesOrNo[0] == 'N' || YesOrNo[0] == 'n')
			{
				current = current->left;
			}

	}

	if(current->left == NULL)
		{
			printf("Is it %s? ", current->data);
			getline(&YesOrNo, &YesOrNo_length, stdin);
			/*YesOrNo[char_read - 1] == '\0';*/
			if(YesOrNo[0] == 'Y' || YesOrNo[0] == 'y')
			{
				printf("\n");
				printf("My, am I clever.  :)\n");
				printf("Thanks for playing.\n");
				printf("\n");
				current = root;
			
			}
			else if(YesOrNo[0] == 'N' || YesOrNo[0] == 'n')
			{
				printf("\n");
				printf("How disappointing.\n");
				printf("What is it (with article)? ");
				char_read = getline(&NewAnimal, &new_animal_length, stdin);
				NewAnimal[char_read - 1] = '\0';
				

				printf("What is a yes/no question that will distinguish %s from %s?\n", current->data, NewAnimal);
				printf("? ");
				char_read = getline(&NewQuestion, &new_question_length, stdin);
				NewQuestion[char_read - 1] = '\0';
                
				printf("\n");
				printf("What is the answer to the question for %s? ", NewAnimal);
				char_read = getline(&NewAnswer, &new_answer_length, stdin);
				NewAnswer[char_read - 1] = '\0';

				printf("\n");
				printf("I'll get it next time, I'm sure.\n");
				printf("Thanks for playing.\n");
				printf("\n");

				current = Insert(current, NewAnimal, NewQuestion, NewAnswer);
				
				current = root;
			
			}
		}
		free(YesOrNo);
		return current;
						
}


/*

My Main will be opening/creating and closing file pointers which are
pointing to my file qa.db

If file was not opened(did not exist) create the file then call my
InsertFirstAnimal subroutine at this point game is over close file

If the file was opened properly check to see if file was empty, if it
was call InsertFirstAnimal subroutine and game is over close file, free
pointer

If there is something in file read database and build binary tree based
on what is in database by calling BuildTree subroutine

Now that binary tree is built in memory let's play the game by calling
PlayGame subroutine

Once the game is over we close old file pointer and open file from
beginning with another pointer and Update the Database with current
Binary Tree that's being stored in Memory

Now that Database is updated we go ahead and free all nodes and data
associated with each node in memory.  Then close last pointer and
program ends

*/

int main(int args, char *argv[])
{

	
	struct Node* current;
	
	char *ptr;
	FILE *fptr;
	FILE *fpo;
	char *mode;
	char *mode2;
	NodeCount = 0;
	LineCount = 0;
	current = NULL;
	root = NULL;
	mode = "r+";
	mode2 = "w";
	fptr = fopen("qa.db", mode);

	if(fptr == NULL)
	{
		printf("qa.db: No such file or directory\n");
		printf("Unable to read database qa.db. Starting fresh.\n");
		fptr = fopen("qa.db", "ab+");
		InsertFirstAnimal(fptr);
		fclose(fptr);
		
	}
	else
	{  
		ptr = readline(fptr);
		if(ptr[0] == '\0')
		{
			rewind(fptr);
			InsertFirstAnimal(fptr);
			fclose(fptr);
			free(ptr);
		}
		else
		{
			rewind(fptr);
			CountNewLines(fptr);
			rewind(fptr);
			current  = BuildTree(current, fptr, ptr);
			if(LineCount - 1 != NodeCount)
			{
				printf("corrupted database - - prompt with missing response\n");
				FreeTree(root);
				free(ptr);
				fclose(fptr);
				return 0;

			}
			else
			{
				current = PlayGame(current);
				fclose(fptr);
				free(ptr);
				fpo = fopen("qa.db", mode2);
				UpdateDatabase(current, fpo);
				fclose(fpo);
				FreeTree(root);

			}

		}
	
	}
	return 0;
}

