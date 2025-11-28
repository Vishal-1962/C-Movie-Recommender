#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_MOVIES 1000
#define LINE_BUF 1024
typedef struct {
    int id;
    char title[256];
    char genre[128];
    float rating;
    int year;
    char language[64];
} Movie;

Movie movies[MAX_MOVIES];
int movie_count = 0;

/* Trim leading/trailing spaces */
void trim(char *s) {
    if (!s) return;
    int len = strlen(s);
    int start = 0;
    while (isspace((unsigned char)s[start])) start++;
    int end = len - 1;
    while (end >= start && isspace((unsigned char)s[end])) end--;
    int newlen = end - start + 1;
    if (newlen < 0) newlen = 0;
    memmove(s, s + start, newlen);
    s[newlen] = '\0';
}

/* Convert to lowercase */
void toLowercase(char *s) {
    for (int i = 0; s[i]; i++)
        s[i] = (char)tolower((unsigned char)s[i]);
}

/* Case-insensitive substring search */
int containsIgnoreCase(const char *haystack, const char *needle) {
    if (!haystack || !needle) return 0;
    char h[256], n[128];
    strncpy(h, haystack, sizeof(h) - 1);
    strncpy(n, needle, sizeof(n) - 1);
    h[sizeof(h) - 1] = '\0';
    n[sizeof(n) - 1] = '\0';
    trim(h);
    trim(n);
    toLowercase(h);
    toLowercase(n);
    return strstr(h, n) != NULL;
}

/* ✅ Simplified & reliable file parser */
void loadMovies() {
    FILE *file = fopen("movieslist.txt", "r");
    if (!file) {
        printf("Error: could not open movieslist.txt\n");
        exit(1);
    }

    char line[LINE_BUF];
    movie_count = 0;

    while (fgets(line, sizeof(line), file)) {
        if (movie_count >= MAX_MOVIES) break;

        trim(line);
        if (strlen(line) == 0) continue;

        // parse fields separated by commas
        char *token = strtok(line, ",");
        if (!token) continue;
        movies[movie_count].id = atoi(token);

        token = strtok(NULL, ",");
        if (!token) continue;
        strcpy(movies[movie_count].title, token);

        token = strtok(NULL, ",");
        if (!token) continue;
        strcpy(movies[movie_count].genre, token);

        token = strtok(NULL, ",");
        if (!token) continue;
        movies[movie_count].rating = atof(token);

        token = strtok(NULL, ",");
        if (!token) continue;
        movies[movie_count].year = atoi(token);

        token = strtok(NULL, ",");
        if (!token) continue;
        strcpy(movies[movie_count].language, token);

        trim(movies[movie_count].title);
        trim(movies[movie_count].genre);
        trim(movies[movie_count].language);

        movie_count++;
    }

    fclose(file);
}

/* --- Recommendation functions --- */
void recommendByGenre(const char *genre) {
    int found = 0;
    printf("\nMovies matching genre '%s':\n", genre);
    for (int i = 0; i < movie_count; i++) {
        if (containsIgnoreCase(movies[i].genre, genre)) {
            printf("%d. %s (%d) | Genre: %s | Rating: %.1f | Language: %s\n",
                   movies[i].id, movies[i].title, movies[i].year,
                   movies[i].genre, movies[i].rating, movies[i].language);
            found = 1;
        }
    }
    if (!found) printf("No movies found in this genre.\n");
}

void recommendByGenreRating(const char *genre, float minRating) {
    int found = 0;
    printf("\nMovies in genre '%s' with rating >= %.1f:\n", genre, minRating);
    for (int i = 0; i < movie_count; i++) {
        if (containsIgnoreCase(movies[i].genre, genre) && movies[i].rating >= minRating) {
            printf("%d. %s (%d) | Genre: %s | Rating: %.1f | Language: %s\n",
                   movies[i].id, movies[i].title, movies[i].year,
                   movies[i].genre, movies[i].rating, movies[i].language);
            found = 1;
        }
    }
    if (!found) printf("No movies found matching the criteria.\n");
}

void recommendByYear(int year) {
    int found = 0;
    printf("\nMovies released in %d:\n", year);
    for (int i = 0; i < movie_count; i++) {
        if (movies[i].year == year) {
            printf("%d. %s | Genre: %s | Rating: %.1f | Language: %s\n",
                   movies[i].id, movies[i].title, movies[i].genre,
                   movies[i].rating, movies[i].language);
            found = 1;
        }
    }
    if (!found) printf("No movies found for this year.\n");
}

void recommendByLanguage(const char *language) {
    int found = 0;
    printf("\nMovies in language '%s':\n", language);
    for (int i = 0; i < movie_count; i++) {
        if (containsIgnoreCase(movies[i].language, language)) {
            printf("%d. %s (%d) | Genre: %s | Rating: %.1f\n",
                   movies[i].id, movies[i].title, movies[i].year,
                   movies[i].genre, movies[i].rating);
            found = 1;
        }
    }
    if (!found) printf("No movies found in this language.\n");
}

void highestRatedMovies() {
    if (movie_count == 0) {
        printf("No movies loaded.\n");
        return;
    }

    float maxRating = movies[0].rating;
    for (int i = 1; i < movie_count; i++)
        if (movies[i].rating > maxRating)
            maxRating = movies[i].rating;

    printf("\nHighest Rated Movies (Rating: %.1f):\n", maxRating);
    for (int i = 0; i < movie_count; i++) {
        if (movies[i].rating == maxRating) {
            printf("%d. %s (%d) | Genre: %s | Language: %s\n",
                   movies[i].id, movies[i].title, movies[i].year,
                   movies[i].genre, movies[i].language);
        }
    }
}

void displayMovies() {
    printf("\nAll Movies (%d):\n", movie_count);
    for (int i = 0; i < movie_count; i++) {
        printf("%d. %s | Genre: %s | Rating: %.1f | Year: %d | Language: %s\n",
               movies[i].id, movies[i].title, movies[i].genre,
               movies[i].rating, movies[i].year, movies[i].language);
    }
}

/* --- Main Menu --- */
int main() {
    loadMovies();
    printf("Loaded %d movies successfully.\n", movie_count);

    int choice;
    char input[256];
    float minRating;
    int year;

    while (1) {
        printf("\n--- Movie Recommendation System ---\n");
        printf("1. Recommend Movies by Genre\n");
        printf("2. Recommend by Genre & Min Rating\n");
        printf("3. Recommend Movies by Release Year\n");
        printf("4. Recommend Movies by Language\n");
        printf("5. Show Highest Rated Movies\n");
        printf("6. View All Movies\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("Invalid input.\n");
            continue;
        }
        getchar(); // consume newline

        switch (choice) {
            case 1:
                printf("Enter genre (e.g. Action, Drama, Romance): ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';
                trim(input);
                recommendByGenre(input);
                break;

            case 2:
                printf("Enter genre: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';
                trim(input);
                printf("Enter minimum rating: ");
                scanf("%f", &minRating);
                getchar();
                recommendByGenreRating(input, minRating);
                break;

            case 3:
                printf("Enter release year: ");
                scanf("%d", &year);
                getchar();
                recommendByYear(year);
                break;

            case 4:
                printf("Enter language: ");
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = '\0';
                trim(input);
                recommendByLanguage(input);
                break;

            case 5:
                highestRatedMovies();
                break;

            case 6:
                displayMovies();
                break;

            case 7:
                printf("Goodbye!\n");
                return 0;

            default:
                printf("Invalid choice. Try again.\n");
        }
    }
}

