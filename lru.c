#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
typedef struct node{
        int data;
        struct node * link;
}node;

//This is an implementation of the least recently used (lru) page replacement algorithm
//number of items in argv
//argv[1] = size (number of pages)
//argv[0] = type (fifo, lru, sc)
int main(int argc, char *argv[]){

        int temp;
        int found;
        int count;
        int size =atoi(argv[1]);
        node* root = malloc(sizeof(node));
        node* current_node;
	node* previous_node;
	node* previouser_node;	//node pointer for the node we checked previous to the previous_node

        scanf("%d", &temp);
        root->data = temp;
        root->link = NULL;
        printf("%d\n", temp);

        while(scanf("%d", &temp)!=EOF){

                found = 0;
                current_node = root;
		previous_node = root;
		previouser_node = root;
                count = 0;

                while(found == 0 && current_node!=NULL && count < size){
                        count++;
                        if(current_node->data == temp){
                                found = 1;
				if(current_node != root){	//if the current node is not the root, makes it the root
					previous_node->link = current_node->link;	//and closes gap in list
					current_node->link = root;
					root = current_node;
				}
                        }
                        else
                                previouser_node = previous_node;
				previous_node = current_node;
				current_node = current_node->link;
                }

                if(found == 0 && count == size){	//replaces last page in list and sets the node before it's
			previouser_node->link = NULL;	//link to NULL
                        free(previous_node);
                }

                if(found == 0){
                        printf("%d\n", temp);
                        node* new = malloc(sizeof(node));
			node* temp_node = root;
                        new->data = temp;
                        new->link = temp_node;
                        root = new;	//makes the new page in the list the root
                }
        }
}                                                                                                                                                                                                                                                  
