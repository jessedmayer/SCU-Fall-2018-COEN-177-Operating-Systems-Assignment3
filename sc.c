#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
typedef struct node{
        int data;
	int ref_bit;		//page's reference bit
        struct node * link;
}node;

//This is an implementation of the second chance (sc) page replacement algorithm
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


        scanf("%d", &temp);
        root->data = temp;
	root->ref_bit = 0;	//initializes unreferenced first page's reference bit to 0
        root->link = NULL;
        printf("%d\n", temp);

        while(scanf("%d", &temp)!=EOF){

                found = 0;
                current_node = root;
		previous_node = root;
                count = 0;

                while(found == 0 && current_node!=NULL && count < size){
                        count++;
                        if(current_node->data == temp){
                                found = 1;
				current_node->ref_bit = 1; //marks page as referenced
                        }
                        else
				previous_node = current_node;
                                current_node = current_node->link;
                }

                if(found == 0 && count == size){
			while(root->ref_bit == 1){	//sets reference bit to 0 and moves to bottom of list till a 
				root->ref_bit = 0;	//page with reference bit equal to 0 is found and is then replaced
				node* temp_node = root;
                	        root = root->link;
				previous_node->link = temp_node;
				previous_node = previous_node->link;
				previous_node->link = NULL;
			}
                        node* temp_node = root;
                        root = root->link;
                        free(temp_node);
                }

                if(found == 0){
                        printf("%d\n", temp);
                        node* new = malloc(sizeof(node));
                        new->data = temp;
			new->ref_bit = 0;	//initializes unreferenced requested page's reference bit to 0
                        new->link = NULL;
                        previous_node->link = new;
                }
        }
}
