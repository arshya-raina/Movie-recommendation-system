# Movie Recommendation System Using Binary Search Tree

This is a console-based movie recommendation system implemented using a Binary Search Tree (BST). It allows users to manage a movie database by adding, searching, deleting, filtering, and recommending movies based on popularity, rating, and genre.

# Features

- Binary Search Tree (BST) implementation for efficient movie storage
- Add, search, and delete movies
- Recommend movies based on genre and rating
- Display all movies sorted by popularity
- Display top N highest-rated movies
- Filter movies by genre or other criteria
- Interactive user input to manage movie data

# Functions

1. Create_Movie  
   Initializes a new movie node with title, rating, popularity, and genre.

2. Add_Movie  
   Inserts a movie into the BST, ordered by popularity and title.

3. Find_Movie_By_Title  
   Searches for a movie by its title in the BST.

4. Display_Movie  
   Displays details of a single movie.

5. Display_All_Movies  
   Performs in-order traversal to show all movies sorted by popularity.

6. Get_Min_Node  
   Finds the node with the minimum popularity.

7. Delete_Movie  
   Removes a movie by title while maintaining BST structure.

8. Display_Top_N_Movies  
   Displays the top N highest-rated movies.

9. Recommend_Movies  
   Suggests movies based on genre and minimum rating.

10. Display_Movies_By_Genre  
    Lists all movies belonging to a specified genre.

11. Add_Movie_Input  
    Collects user input and adds a movie to the BST.
