#include"linkedListsAndStruct.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void addNodeForUserPlayList(NodeUserPlayList **head, Song song){ //this function create new node and insert given song to user playlist
    NodeUserPlayList *givenNode=*head;
    NodeUserPlayList* new_node = ( NodeUserPlayList*) malloc(sizeof( NodeUserPlayList)); 
    NodeUserPlayList *last = *head; 
    strcpy(new_node->song2.name,song.name); 
    strcpy(new_node->song2.genre, song.genre); 
    new_node->song2.year=song.year;
    new_node->link2 = NULL; 
    if (*head == NULL) { 
       *head = new_node; 
       return ; 
    }   
    while (last->link2 != NULL){ 
        last = last->link2;
    }    
    last->link2 = new_node; 
}
void deleteNodeForGenre2(NodeUserPlayList **head_ref, char *key) { //this function deletes all node that has given genre from user playlist
    char genre[15];
    strcpy(genre,key);
    NodeUserPlayList* temp = *head_ref, *prev; 
    while (temp != NULL && strcmp(temp->song2.genre,genre)==0) { 
        *head_ref = temp->link2;   
        free(temp);               
        temp = *head_ref;        
    } 
    while (temp != NULL) { 
        while (temp != NULL && strcmp(temp->song2.genre,genre)!=0) 
        { 
            prev = temp; 
            temp = temp->link2; 
        } 
        if (temp == NULL) return; 
  
        prev->link2 = temp->link2; 
        free(temp);   
        temp = prev->link2; 
    } 
}
 
void deleteNodeForYear2(NodeUserPlayList **head_ref,int year){ //this function deletes all songs older than a given year from user playlist
    NodeUserPlayList* temp = *head_ref, *prev;  
    while (temp != NULL && temp->song2.year < year) { 
        *head_ref = temp->link2;    
        free(temp);              
        temp = *head_ref;       
    } 
    while (temp != NULL) { 
        while (temp != NULL && temp->song2.year >= year) { 
            prev = temp; 
            temp = temp->link2; 
        } 
        if (temp == NULL) return; 
  
        prev->link2 = temp->link2; 
        free(temp);  
        temp = prev->link2; 
    } 
}
void printForUserPlayList(NodeUserPlayList *head){ //this function iterates the user playlist and prints all song's info
	NodeUserPlayList *current = head;
   	while (current != NULL) {
         	printf("Name:%s Genre:%s Year:%d\n", current->song2.name,current->song2.genre,current->song2.year);
         	current = current->link2;
   	}
}
