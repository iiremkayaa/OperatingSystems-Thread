#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"linkedListsAndStruct.h"
#include <pthread.h>
#include"time.h"
#include<unistd.h>
#define NUM_THREAD 3
pthread_mutex_t lock1;
pthread_mutex_t lock2; 
pthread_mutex_t lock4;
pthread_mutex_t lock5; 
pthread_mutex_t lock6; 
pthread_mutex_t lock7; 
pthread_mutex_t lock8; 

Node *playList1=NULL;
Node *playList2=NULL;
NodeUserPlayList *userPlayList=NULL;

void addSongToList (Node ** playListArg,char *name,char *genre,int year) { //this function add songs to playlist
    Song song1;  //First of all playlist1 and playlist2 have 10 songs. This helps to create playlists 
    strcpy(song1.name,name);
    strcpy(song1.genre,genre);
    song1.year=year;
    Node *playList=*playListArg;
    addNodeForPlayList(playListArg,song1);
}
void* threadA(void *arg) {
    int num = (rand() % (10)) + 1;//num is the total number of music it's going to cut/paste randomly
    int numList=(rand() % (2)) + 1; //numlist determines the first playlist to use.
    pthread_mutex_lock(&lock1); 
    CutPasteStruct *a;
    a=(CutPasteStruct*)arg;
    Node **current = a->node1;
    Node *currentNode=*current;
    Node **current2=a->node2;
    Node *currentNode2=*current2;
    NodeUserPlayList **dest=a->userNode;
    NodeUserPlayList *destNode=*a->userNode;

    if(numList==1){ //If numlist is 1, songs are cut from playlist1 until playlist1 is empty 
        while(currentNode !=NULL && num>0){ //If playlist1 is empty and number of music that  
            Song destSong; // it's going to cut is greater than 0, songs are cut from playlist2.
            strcpy(destSong.name, currentNode->song1.name);
            strcpy(destSong.genre,currentNode->song1.genre);
            destSong.year=currentNode->song1.year; //information about currentNode is copied to destSong and
            addNodeForUserPlayList(&(*a->userNode),destSong); // destSong is added to user playlist
            Node *tempNode = currentNode->link;
            free(currentNode); 
            num--;
            currentNode=tempNode;             
        }
        playList1=currentNode;
        if(currentNode == NULL && num>0){
            while(currentNode2 != NULL && num>0){
                Song destSong;
                strcpy(destSong.name,currentNode2->song1.name);
                strcpy(destSong.genre,currentNode2->song1.genre);
                destSong.year=currentNode2->song1.year; //information about currentNode2 is copied to destSong and
                addNodeForUserPlayList(&(*a->userNode),destSong); //destSong is added to user playlist
                Node *tempNode=currentNode2->link;
                free(currentNode2);
                num--;
                currentNode2=tempNode;
            }
        }
        playList2=currentNode2;
    }
    if(numList==2){ //If numlist is 2, songs are cut from playlist2 until playlist1 is empty 
        while(currentNode2 !=NULL && num>0){//If playlist2 is empty and number of music that 
            Song destSong; //it's going to cut is greater than 0,songs are cut from playlist2 
            strcpy(destSong.name,currentNode2->song1.name);
            strcpy(destSong.genre,currentNode2->song1.genre);
            destSong.year=currentNode2->song1.year; //information about currentNode2 is copied to destSong and 
            addNodeForUserPlayList(&(*a->userNode),destSong);//destSong is added to user playlist 
            Node *tempNode = currentNode2->link;
            free(currentNode2);
            num--;
            currentNode2=tempNode;
        }
        playList2=currentNode2;
        if(currentNode2 == NULL && num>0){
            while(currentNode != NULL && num>0){
                Song destSong; //information about currentNode is copied to destSong and
                strcpy(destSong.name,currentNode->song1.name); //destSong is added to user playlist
                strcpy(destSong.genre,currentNode->song1.genre);
                destSong.year=currentNode->song1.year;
                addNodeForUserPlayList(&(*a->userNode),destSong);
                Node *tempNode=currentNode->link;
                free(currentNode);
                num--;
                currentNode=tempNode;
            }
            playList1=currentNode;
        }
    }
    pthread_mutex_unlock(&lock1);

} 
void* threadB(void* arg){ //Address of playlist1,playlist2 and user playlist are taken with struct RemoveStructForGenre in thread B
    RemoveStructForGenre *b;
    b=(RemoveStructForGenre*)arg;
    Node* temp1=*b->node1;
    Node* temp2=*b->node2;
    NodeUserPlayList* tempUser=*b->userNode;
    pthread_mutex_lock(&lock5); //In each deletion of node in playlist1 ,lock is set because other threads should not be access  
    deleteNodeForGenre1(&temp1,b->input);
    pthread_mutex_unlock(&lock5); 
    pthread_mutex_lock(&lock6); //In each deletion of node in playlist2 ,lock is set because other threads should not be access
    deleteNodeForGenre1(&temp2,b->input);
    pthread_mutex_unlock(&lock6);
    pthread_mutex_lock(&lock7);//In each deletion of node in user playlist ,lock is set because other threads should not be access
    deleteNodeForGenre2(&tempUser,b->input);
    pthread_mutex_unlock(&lock7);    
}
void* threadC(void* arg){//Address of playlist1,playlist2 and user playlist are taken with struct RemoveStructForYear in thread C
    RemoveStructForYear *c;
    c=(RemoveStructForYear*)arg;
    Node* temp1=*c->node1;
    Node* temp2=*c->node2;
    NodeUserPlayList* tempUser=*c->userNode;
    pthread_mutex_lock(&lock8); //In each deletion of node in playlist1 ,lock is set because other threads should not be access
    deleteNodeForYear1(&temp1,c->input);
    playList1=temp1;
    pthread_mutex_unlock(&lock8); 
    pthread_mutex_lock(&lock4);  //In each deletion of node in playlist2 ,lock is set because other threads should not be access
    deleteNodeForYear1(&temp2,c->input);
    playList2=temp2 ;
    pthread_mutex_unlock(&lock4);     
    pthread_mutex_lock(&lock2); //In each deletion of node in user playlist ,lock is set because other threads should not be access
    deleteNodeForYear2(&tempUser,c->input);
    userPlayList=tempUser; 
    pthread_mutex_unlock(&lock2);    
}


int main(){
    addSongToList(&playList1,"song1","genre1",1970); //creating playlist1
    addSongToList(&playList1,"song2","genre2",1971);
    addSongToList(&playList1,"song3","genre2",1980);
    addSongToList(&playList1,"song4","genre4",1973);
    addSongToList(&playList1,"song5","genre3",1974);
    addSongToList(&playList1,"song6","genre6",1975);
    addSongToList(&playList1,"song7","genre5",1976);
    addSongToList(&playList1,"song8","genre4",1977);
    addSongToList(&playList1,"song9","genre2",1978);
    addSongToList(&playList1,"song10","genre2",1979);

    addSongToList(&playList2,"song11","genre1",1970); //creating playlist2
    addSongToList(&playList2,"song12","genre2",1971);
    addSongToList(&playList2,"song13","genre3",1972);
    addSongToList(&playList2,"song14","genre3",1975);
    addSongToList(&playList2,"song15","genre2",1973);
    addSongToList(&playList2,"song16","genre5",1975);
    addSongToList(&playList2,"song17","genre6",1976);
    addSongToList(&playList2,"song18","genre7",1977);
    addSongToList(&playList2,"song19","genre5",1978);
    addSongToList(&playList2,"song20","genre4",1979);

    CutPasteStruct cutPasteStr; //For thread A,this struct holds address of playlist1,playlist2 and user playlist
    cutPasteStr.node1=&playList1;
    cutPasteStr.node2=&playList2;
    cutPasteStr.userNode=&userPlayList;
    pthread_t threads[NUM_THREAD]; 
    for (int i = 0; i < NUM_THREAD; i++) { 
		int* p = malloc(sizeof(int));
		*p=i; 
		pthread_create(&threads[i], NULL, threadA, &cutPasteStr);//pthread_create creates a new thread and makes it executable.
	} 
	for (int i = 0; i < NUM_THREAD; i++){ 
		pthread_join(threads[i], NULL);	 ///pthread_join is used to link the current thread process to another thread.
    }
    
    char genreInput[20];
    printf("Enter genre to delete:");
    scanf("%s", genreInput);
    pthread_t tid;
    RemoveStructForGenre argGenre;
    argGenre.node1=&playList1;
    argGenre.node2=&playList2;
    argGenre.userNode=&userPlayList;
    strcpy (argGenre.input, genreInput);
    pthread_create(&tid, NULL, threadB, &argGenre); //pthread_create creates a new thread and makes it executable.
    pthread_join(tid, NULL);//pthread_join is used to link the current thread process to another thread.
   
    pthread_t tid2;
    int yearInput;
    printf("Enter a year to delete: ");
    scanf("%d", &yearInput);
    RemoveStructForYear argYear;
    argYear.node1=&playList1;
    argYear.node2=&playList2;
    argYear.userNode=&userPlayList;
    argYear.input=yearInput;
    pthread_create(&tid2, NULL, threadC, &argYear);//pthread_create creates a new thread and makes it executable.
    pthread_join(tid2, NULL);//pthread_join is used to link the current thread process to another thread.


    printf("Playlist1:\n");
    printForPlayList(playList1);
    printf("Playlist2:\n");
    printForPlayList(playList2);
    printf("User playlist:\n");
    printForUserPlayList(userPlayList);
    return 0;
}