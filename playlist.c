#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Define the structure for a song
typedef struct Song {
    char title[50];
    char artist[50];
    int duration; // in seconds
} Song;

// Define the structure for a node in the doubly linked list
typedef struct Node {
    Song song;
    struct Node* next;
    struct Node* prev;
} Node;

// Define the structure for the playlist
typedef struct Playlist {
    Node* head;
    Node* tail;
} Playlist;
// Function to initialize the playlist
void initPlaylist(Playlist* playlist) {
    playlist->head = NULL;
    playlist->tail = NULL;
}
// Function to create a new node
Node* createNode(const char* title, const char* artist, int duration) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    strcpy(newNode->song.title, title);
    strcpy(newNode->song.artist, artist);
    newNode->song.duration = duration;
    newNode->next = NULL;
    newNode->prev = NULL;
    return newNode;
}
// Function to add a song to the end of the playlist
void addSong(Playlist* playlist, const char* title, const char* artist, int duration) {
    Node* newNode = createNode(title, artist, duration);
    if (playlist->head == NULL) {
        playlist->head = newNode;
        playlist->tail = newNode;
    } else {
        playlist->tail->next = newNode;
        newNode->prev = playlist->tail;
        playlist->tail = newNode;
    }
}
// Function to remove a song by title
void removeSong(Playlist* playlist, const char* title) {
    Node* current = playlist->head;
    while (current != NULL) {
        if (strcmp(current->song.title, title) == 0) {
            if (current->prev != NULL) {
                current->prev->next = current->next;
            } else {
                playlist->head = current->next;
            }
            if (current->next != NULL) {
                current->next->prev = current->prev;
            } else {
                playlist->tail = current->prev;
            }
            free(current);
            return;
        }
        current = current->next;
    }
    printf("Song not found in the playlist.\n");
}
// Function to display the playlist
void displayPlaylist(const Playlist* playlist) {
    Node* current = playlist->head;
    while (current != NULL) {
        printf("Title: %s, Artist: %s, Duration: %d seconds\n", current->song.title, current->song.artist, current->song.duration);
        current = current->next;
    }
}

int main() {
    Playlist playlist;
    initPlaylist(&playlist);

    addSong(&playlist, "Song1", "Artist1", 210);
    addSong(&playlist, "Song2", "Artist2", 180);
    addSong(&playlist, "Song3", "Artist3", 240);

    printf("Current Playlist:\n");
    displayPlaylist(&playlist);

    printf("\nRemoving 'Song2' from the playlist...\n");
    removeSong(&playlist, "Song2");

    printf("\nUpdated Playlist:\n");
    displayPlaylist(&playlist);
    return 0;
}