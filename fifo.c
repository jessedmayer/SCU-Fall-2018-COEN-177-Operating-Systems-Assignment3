#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
typedef struct node{		//data structure for linked list TLB
	int data;		//stores page number
	struct node * link;	//pointer to following node in list
}node;

//This is an implementation of the first-in, first-out (fifo) page replacement algorithm
//number of items in argv
//argv[1] = size (number of pages)
//argv[0] = type (fifo, lru, sc)
int main(int argc, char *argv[]){

	int temp;	//holds current page request from the input file
	int found;	//boolean for whether the page requested is in the TLB
	int count;	//iterative that ensures TLB stays within size limit
	int size =atoi(argv[1]);		//sets the size of TLB to be the value input by user
	node* root = malloc(sizeof(node));	//allocates memory for root node
	node* current_node;	//node pointer for the node we are currently checking
	node* previous_node;	//node pointer for the node we previously checked

	scanf("%d", &temp);	//takes first page request from input list
	root->data = temp;	//adds first page request to the top of TLB
	root->link = NULL;	//sets roots pointer to NULL
	printf("%d\n", temp);	//sends page fault for the first page request to the output file

	while(scanf("%d", &temp)!=EOF){	//reads page requests from the input file till it reaches end of page

		found = 0;		
		current_node = root; 
		previous_node = root;	
		count = 0;		

		while(found == 0 && current_node!=NULL && count < size){//searches for requested page till it is either
			count++;			//found, current_node becomes NULL or we are about to surpass size
			if(current_node->data == temp){		//checks if the current node is the requested page
				found = 1;
			}		
			else
				previous_node = current_node;		//increments previous and current nodes
				current_node = current_node->link;
		}
		
		if(found == 0 && count == size){//checks if the requested page has not been found and if TLB is at max size
			node* temp_node = root;
			root = root->link;
			free(temp_node);	//replaces root node
		}

		if(found == 0){
			printf("%d\n", temp);			//sends page fault to output file
			node* new = malloc(sizeof(node));	//allocates memory for new node for the requested page
			new->data = temp;
			new->link = NULL;
			previous_node->link = new;		//adds new node to the end of the TLB
		}
	}
}
