
// http://computer-programming-forum.com/47-c-language/d406b299d54242be.htm
// Tobias Oe
// #5 / 14

// The first one I saw was written in basic, and was keeping its data
// in memory only... Here it is in C:

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *get_line(int size){
     char *line;
     char *newline_p;
     char *tmp;
     if((line=malloc(size))==NULL){
          fprintf(stderr,"Can't alloc\n");
          exit(EXIT_FAILURE);
     }
     if(fgets(line,size,stdin)==NULL){
          fprintf(stderr,"Can't read from stdin\n");
          exit(EXIT_FAILURE);
     }
     for(;(newline_p=strchr(line,'\n'))==NULL;size*=2){
          if((tmp=realloc(line,2*size))==NULL){
               fprintf(stderr,"Can't realloc\n");
               exit(EXIT_FAILURE);
          }
          line=tmp;
          if(fgets(line+size-1,size+1,stdin)==NULL){
               fprintf(stderr,"Can't read from stdin\n");
               exit(EXIT_FAILURE);
          }
     }
     *newline_p='\0';
     if((tmp=realloc(line,newline_p-line+1))==NULL){
          fprintf(stderr,"Can't realloc\n");
          exit(EXIT_FAILURE);
     }
     line=tmp;
     return line;
}

int yes_no(void){
     char *line;
     int yes,no;
     do{
          line=get_line(10);
          yes=strcmp(line,"y")==0 ||
              strcmp(line,"Y")==0 ||
              strcmp(line,"yes")==0 ||
              strcmp(line,"Yes")==0;
          no=strcmp(line,"n")==0 ||
             strcmp(line,"n")==0 ||
             strcmp(line,"no")==0 ||
             strcmp(line,"No")==0;
          free(line);
     }while(!(yes ||  no));
     return yes;
}

enum node_type {animal_type,question_type};

struct animal{
     char *name;
};

struct question{
     char *text;
     struct node *yes;
     struct node *no;
};

struct node {
     enum node_type type;
     union {
          struct animal animal;
          struct question question;
     } content;
};

struct node *find_animal(struct node *node_p){
     if(node_p->type==question_type){
          printf("%s ",node_p->content.question.text);
          fflush(stdout);
          if(yes_no()){
               return find_animal(node_p->content.question.yes);
          }else{
               return find_animal(node_p->content.question.no);
          }
     }
     return node_p;
}

int main(void){
     struct node root;
     struct node *found,*new_animal,*old_animal;
     printf("Enter an animal name. ");
     fflush(stdout);
     root.content.animal.name=get_line(100);
     root.type=animal_type;
     do{
          printf("Think of an animal...\n");
          found=find_animal(&root);
          printf("Were you thinking of a %s? ",found->content.animal.name);
          fflush(stdout);
          if(!yes_no()){
               if((new_animal=malloc(sizeof *new_animal))==NULL ||
                  (old_animal=malloc(sizeof *new_animal))==NULL
               ){
                    fprintf(stderr,"Can't malloc new animals\n");
                    exit(EXIT_FAILURE);
               }
               printf("What animal were you thinking of? ");
               fflush(stdout);
               new_animal->content.animal.name=get_line(1000);
               new_animal->type=animal_type;
               *old_animal=*found;
               printf("Enter a question that is true for %s and false for %s. ",
                      new_animal->content.animal.name,
                      old_animal->content.animal.name
               );
               fflush(stdout);
               found->content.question.text=get_line(1000);
               found->content.question.yes=new_animal;
               found->content.question.no=old_animal;
               found->type=question_type;
          }
          printf("Play again? ");
          fflush(stdout);
     }while(yes_no());
}

