
// http://www.cprogramming.com/snippets/source-code/singly-linked-list-insert-remove-add-count

// 4/24/15 - lrb - minor edits
// 9/19/20 - lrb - changed node to hold both a string and number
// 9/20/20 - tag - comments, plus portable i/o in main (fgets, and sscanf)
// 9/21/20 - lrb - using a different way to parse input

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
 
struct node
{
	char str[50];
	int data;
	struct node *next;
}*head;	// The head of the list.

/*	Internal routine: head MUST reference an existing node.
	Appends a new node to the end of the list. 
 */
void _append(char *s,int num)
{
	struct node *temp,*right;
	temp=(struct node *)malloc(sizeof(struct node));
	strcpy(temp->str,s);
	temp->data=num;
	right=(struct node *)head;
	while(right->next != NULL) right=right->next;
	right->next =temp;
	right=temp;
	right->next=NULL;
}

/**	Adds a node to the top of the list.
	NOTE: each created node is in its own malloc.
 */
void add(char *s,int num)
{
	struct node *temp;
	temp=(struct node *)malloc(sizeof(struct node));
	strcpy(temp->str,s);
	temp->data=num;
	if (head== NULL)
	{
	head=temp;
	head->next=NULL;
	}
	else
	{
	temp->next=head;
	head=temp;
	}
}

/*	Internal routine: The list must have at least loc nodes.
	Adds a node as the nth on the list, n=loc. 
 */
void _addafter(char *s,int num,int loc)
{
	int i;
	struct node *temp,*left,*right;
	right=head;
	for(i=1;i<loc;i++)
	{
	left=right;
	right=right->next;
	}
	temp=(struct node *)malloc(sizeof(struct node));
	strcpy(temp->str,s);
	temp->data=num;
	left->next=temp;
	left=temp;
	left->next=right;
	return;
}

/**	Returns the length of the list.
 */
int count()
{
	struct node *n;
	int c=0;
	n=head;
	while(n!=NULL)
	{
	n=n->next;
	c++;
	}
	return c;
} 

/**	Inserts a new node just after the first in the list alphabetically (strcmp)
	less than *s. Thus if used exclusively the linked list stays sorted.
 */
void insert(char *s,int num)
{
	int c=0;
	struct node *temp;
	temp=head;
	if(temp==NULL)
	{
	add(s,num);
	}
	else
	{
	while(temp!=NULL)
	{
		if(strcmp(temp->str,s)<0)
		c++;
		temp=temp->next;
	}
	if(c==0)
		add(s,num);
	else if(c<count())
		_addafter(s,num,++c);
	else
		_append(s,num);
	}
}

/**	Delete the node whose string matches *s.
 */
int delete(char *s)
{
	struct node *temp,*prev;
	temp=head;
	while(temp!=NULL)
	{
	if(strcmp(temp->str,s)==0)
	{
		if(temp==head)
		{
		head=temp->next;
		free(temp);
		return 1;
		}
		else
		{
		prev->next=temp->next;
		free(temp);
		return 1;
		}
	}
	else
	{
		prev=temp;
		temp=temp->next;
	}
	}
	return 0;
}

/**	Print the list to stdout.
 */
void display(void)
{
	struct node *r;
	r=head;
	if(r==NULL)
	{
	return;
	}
	while(r!=NULL)
	{
	printf("\n%s %d",r->str,r->data);
	r=r->next;
	}
	printf("\n");
}

/**	Manually test all the above.
*/
	int main(void) {
		int i,num,loc,j;
		char line[80],st[50],stn[10];
		struct node *n;
		head=NULL;
		printf("\nsinglyLinkedList.c - 9/22/20\n");
		while(1)
		{
			printf("\nList operations\n");
			printf("\n");
			printf("1 Insert\n");
			printf("2 Display\n");
			printf("3 Size\n");
			printf("4 Delete\n");
			printf("5 Exit\n");
			printf("\nEnter your choice (1..5) : ");
			fgets(line,80,stdin);
			i=atoi(line);
			switch(i)
			{
				case 1:
					printf("\nEnter a number, space, and string: ");
					fgets(line,80,stdin);
					j=0;
					while(line[j]!=' ') { // grab the number part
						stn[j]=line[j];
						j++;
						}
					num=atoi(stn);
					strcpy(st,line+j+1); // put rest of line into st
					st[strlen(st)-1]=0; // get rid of newline
   					insert(st,num);
					break;
				case 2:
					if(head==NULL) {
						printf("\nList is empty\n");
						}
					else {
						printf("\nElement(s) in the list are : \n");
						}
					display();
					break;
				case 3:
					printf("\nSize of the list is %d\n",count());
					break;
				case 4:
					if(head==NULL) printf("\nList is empty\n");
					else {
						printf("\nEnter a string to delete : ");
						fgets(st,50,stdin);
						st[strlen(st)-1]=0; // get rid of newline
			 			if(delete(st)) printf("\n%s deleted successfully\n",st);
						else printf("\n%s not found in the list\n",st);
						}
					break;
				case 5:	return 0;
				default: printf("\nInvalid option\n");
			}
		
	}
	return 0;
}
