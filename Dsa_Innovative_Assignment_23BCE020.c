#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Movie {
    char title[100];
    double rating;
    int popularity;
    char genre[50];
    struct Movie *left, *right;
} Movie;

// Function to create a new movie node
Movie* createMovie(char *title, double rating, int popularity, char *genre) {
    Movie *newMovie = (Movie*)malloc(sizeof(Movie));
    strcpy(newMovie->title, title);
    newMovie->rating = rating;
    newMovie->popularity = popularity;
    strcpy(newMovie->genre, genre);
    newMovie->left = newMovie->right = NULL;
    return newMovie;
}

// Insert a movie into the BST based on popularity
Movie* addMovie(Movie *root, char *title, double rating, int popularity, char *genre) {
    if (!root) return createMovie(title, rating, popularity, genre);

    if (popularity < root->popularity)
        root->left = addMovie(root->left, title, rating, popularity, genre);
    else if (popularity > root->popularity)
        root->right = addMovie(root->right, title, rating, popularity, genre);
    else // If popularity is equal, sort by title
        if (strcmp(title, root->title) < 0)
            root->left = addMovie(root->left, title, rating, popularity, genre);
        else
            root->right = addMovie(root->right, title, rating, popularity, genre);

    return root;
}

// Search for a movie by title
Movie* findMovieByTitle(Movie *root, char *title) {
    if (!root || strcmp(root->title, title) == 0)
        return root;

    if (strcmp(title, root->title) < 0)
        return findMovieByTitle(root->left, title);

    return findMovieByTitle(root->right, title);
}

// Display details of a movie
void displayMovie(Movie *movie) {
    if (movie) {
        printf("Title: %s\n", movie->title);
        printf("Rating: %.1f\n", movie->rating);
        printf("Popularity: %d\n", movie->popularity);
        printf("Genre: %s\n\n", movie->genre);
    }
}

// In-order traversal to display movies by popularity
void displayAllMovies(Movie *root) {
    if (root) {
        displayAllMovies(root->left);
        displayMovie(root);
        displayAllMovies(root->right);
    }
}

// Find the minimum node by popularity
Movie* getMinNode(Movie *node) {
    Movie *current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Delete a movie by title
Movie* deleteMovie(Movie *root, char *title) {
    if (!root) return root;

    if (strcmp(title, root->title) < 0)
        root->left = deleteMovie(root->left, title);
    else if (strcmp(title, root->title) > 0)
        root->right = deleteMovie(root->right, title);
    else {
        if (!root->left) {
            Movie *temp = root->right;
            free(root);
            return temp;
        } else if (!root->right) {
            Movie *temp = root->left;
            free(root);
            return temp;
        }

        Movie *temp = getMinNode(root->right);
        strcpy(root->title, temp->title);
        root->rating = temp->rating;
        root->popularity = temp->popularity;
        strcpy(root->genre, temp->genre);
        root->right = deleteMovie(root->right, temp->title);
    }
    return root;
}

// Display top N movies by rating (descending order)
void displayTopNMovies(Movie *root, int *N) {
    if (root && *N > 0) {
        displayTopNMovies(root->right, N);
        if (*N > 0) {
            displayMovie(root);
            (*N)--;
        }
        displayTopNMovies(root->left, N);
    }
}

// Recommend movies based on genre and minimum rating
void recommendMovies(Movie *root, char *genre, double minRating) {
    if (root) {
        recommendMovies(root->left, genre, minRating);
        if (strcmp(root->genre, genre) == 0 && root->rating >= minRating)
            displayMovie(root);
        recommendMovies(root->right, genre, minRating);
    }
}

// Display movies by specific genre
void displayMoviesByGenre(Movie *root, char *genre) {
    if (root) {
        displayMoviesByGenre(root->left, genre);
        if (strcmp(root->genre, genre) == 0)
            displayMovie(root);
        displayMoviesByGenre(root->right, genre);
    }
}

// Function to take movie details input from the user
void addMovieInput(Movie **root) {
    char title[100], genre[50];
    double rating;
    int popularity;

    printf("Enter movie title: ");
    scanf(" %[^\n]%*c", title);
    printf("Enter movie rating: ");
    scanf("%lf", &rating);
    printf("Enter movie popularity index: ");
    scanf("%d", &popularity);
    printf("Enter movie genre: ");
    scanf(" %[^\n]%*c", genre);

    *root = addMovie(*root, title, rating, popularity, genre);
}

// Main function
int main() {
    Movie *root = NULL;
    int choice, N;
    char title[100], genre[50];
    double minRating;

    while (1) {
        printf("\n--- Movie Recommendation System ---\n");
        printf("1. Add a movie\n");
        printf("2. Search for a movie by title\n");
        printf("3. Display all movies (sorted by popularity)\n");
        printf("4. Delete a movie by title\n");
        printf("5. Display top N rated movies\n");
        printf("6. Recommend movies by genre and rating\n");
        printf("7. Display movies by genre\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addMovieInput(&root);
                break;

            case 2:
                printf("Enter movie title to search: ");
                scanf(" %[^\n]%*c", title);
                Movie *movie = findMovieByTitle(root, title);
                if (movie) displayMovie(movie);
                else printf("Movie not found.\n");
                break;

            case 3:
                printf("All Movies (sorted by popularity):\n");
                displayAllMovies(root);
                break;

            case 4:
                printf("Enter title of movie to delete: ");
                scanf(" %[^\n]%*c", title);
                root = deleteMovie(root, title);
                printf("Movie deleted if it existed.\n");
                break;

            case 5:
                printf("Enter number of top rated movies to display: ");
                scanf("%d", &N);
                displayTopNMovies(root, &N);
                break;

            case 6:
                printf("Enter genre for recommendations: ");
                scanf(" %[^\n]%*c", genre);
                printf("Enter minimum rating: ");
                scanf("%lf", &minRating);
                recommendMovies(root, genre, minRating);
                break;

            case 7:
                printf("Enter genre to display movies: ");
                scanf(" %[^\n]%*c", genre);
                displayMoviesByGenre(root, genre);
                break;

            case 8:
                printf("Exiting...\n");
                exit(0);
                break;

            default:
                printf("Invalid choice. Try again.\n");
        }
    }

    return 0;
}
