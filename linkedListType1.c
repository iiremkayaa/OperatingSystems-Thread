#include"linkedListsAndStruct.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

void addNodeForPlayList(Node **head, Song song){ //this function create new node and insert given song to playlist
    Node *givenNode=*head;
    Node* new_node = ( Node*) malloc(sizeof( Node)); 
    Node *last = *head; 
    strcpy(new_node->song1.name,song.name); 
    strcpy(new_node->song1.genre, song.genre); 
    new_node->song1.year=song.year;
    new_node->link = NULL; 
    if (*head == NULL) 
    { 
       *head = new_node; 
       return ; 
    }   
    while (last->link != NULL){ 
        last = last->link;
    }    
    last->link = new_node; 

}
void deleteNodeForGenre1(Node **head_ref, char *key) { //this function deletes all node that has given genre from playlist
    char genre[15];
    strcpy(genre,key);
    Node* temp = *head_ref, *prev; 
    while (temp != NULL && strcmp(temp->song1.genre,genre)==0) { 
        *head_ref = temp->link;   
        free(temp);                
        temp = *head_ref;         
    } 
    while (temp != NULL) { 
        while (temp != NULL && strcmp(temp->song1.genre,genre)!=0) { 
            prev = temp; 
            temp = temp->link; 
        } 
        if (temp == NULL) return; 
        prev->link = temp->link; 

        free(temp);    
        temp = prev->link; 
    } 
} 
void deleteNodeForYear1(Node **head_ref,int year){ //this function deletes all songs older than a given year from playlist
    Node* temp = *head_ref, *prev;   
    while (temp != NULL && temp->song1.year < year) { 
        *head_ref = temp->link;   
        free(temp);               
        temp = *head_ref;        
    } 
    while (temp != NULL) { 
        while (temp != NULL && temp->song1.year >= year) { 
            prev = temp; 
            temp = temp->link; 
        } 
        if (temp == NULL) return; 
  
        prev->link = temp->link; 
        free(temp); 
        temp = prev->link; 
    } 
}

void printForPlayList(Node *head){ //this function iterates the playlist and prints all song's info
	Node *current = head;
   	while (current != NULL) {
         	printf("Name:%s Genre:%s Year:%d\n", current->song1.name,current->song1.genre,current->song1.year);
         	current = current->link;
   	}
}

