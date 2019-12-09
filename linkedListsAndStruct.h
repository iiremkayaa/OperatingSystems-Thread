#include<stdio.h>
#include<stdlib.h>
typedef struct song { //struct of song
    char name [25];
    char genre [15];
    int year;//(1992)
}Song;

struct node{ //struct of playlists
    struct song song1;
    struct node *link;
};
typedef struct node Node;

struct removeStructForGenre{ //struct for operation of removing on thread B
    struct node **node1;
    struct node **node2;
    struct nodeUserPlayList **userNode;
    char input[20]; //input is given genre
};
typedef struct removeStructForGenre RemoveStructForGenre; 

struct removeStructForYear{ //struct for operation of removing on thread C
    struct node **node1;
    struct node **node2;
    struct nodeUserPlayList **userNode;
    int input; //input is given age
};
typedef struct removeStructForYear RemoveStructForYear;

struct nodeUserPlayList{ //struct for user playlist
    struct song song2;
    struct nodeUserPlayList *link2;
};
typedef struct nodeUserPlayList NodeUserPlayList;

struct cutPasteStruct{ //struct for operation of cutting and pasting on thread A
    struct node **node1;
    struct node **node2;
    struct nodeUserPlayList **userNode;
};
typedef struct cutPasteStruct CutPasteStruct;

void addNodeForUserPlayList(NodeUserPlayList **head,Song song); //Add given song to the given user playlist
void printForUserPlayList(NodeUserPlayList *head); //print the song of each node in the user playlist
void deleteNodeForGenre2(NodeUserPlayList **head,char* key); //delete songs that has given genre from user playlist
void deleteNodeForYear2(NodeUserPlayList **head,int year); //delete the songs older than a given year from user playlist

void addNodeForPlayList(Node **head,Song song); //Add given song to the given playlist
void deleteNodeForGenre1(Node **head,char* key); //delete songs that has given genre from user playlist
void deleteNodeForYear1(Node **head,int year); //delete the songs older than a given year from user playlist
void printForPlayList(Node *head); //print name of the song of each node in the playlist
