# C Movie Recommendation System 🍿
 
![Project Status: Completed](https://img.shields.io/badge/Status-Completed-success)

---

## 💡 Project Overview & Motivation

This project is a high-speed, console-based Movie Recommendation System developed entirely in **C programming language**.

The core motivation for building this tool was the personal frustration of wasting excessive time searching for suitable movies across platforms filled with noise, advertisements, and mandatory login procedures. This system provides a **fast, ad-free, and privacy-focused** solution for movie discovery.

It efficiently loads a static local dataset (`movieslist.txt`) and allows users to filter and recommend movies based on concrete criteria: **genre, release year, language, and minimum user rating**.

---

## 💻 Core Technical Features

This project was a deep dive into C fundamentals, allowing me to implement and solidify the following concepts:

* **Data Structures:** Effective definition and use of a custom `Movie` **struct** to logically represent each movie record's ID, title, genre, rating, year, and language.
* **File I/O and Parsing:** Implementation of the `loadMovies` function using `fopen`, `fgets`, and the `strtok` function to **reliably parse comma-separated (CSV) data** from the `movieslist.txt` file into the program's memory.
* **Robust String Handling:** Developed custom utility functions (`trim`, `toLowercase`, `containsIgnoreCase`) to ensure all search criteria (Genre, Language) are **case-insensitive** and correctly handle leading/trailing whitespace, guaranteeing a smooth user experience.
* **Filtering Logic:** Custom searching algorithms implemented within each recommendation function to iterate over the data and apply multiple search filters (e.g., genre **AND** minimum rating) efficiently.
* **User Interface:** Managed the main application flow and user input handling via a simple, loop-driven console **Menu** and `switch` statement logic.

---

## ▶️ How to Compile and Run

This project requires a standard C compiler (like GCC) installed on your system.

1.  **Preparation:** Ensure the three project files (`movie_recommender.c` or your file name, `movieslist.txt`, and `README.md`) are saved in the same local directory.
2.  **Compile:** Open your terminal (or Command Prompt/Git Bash) and run the following command to compile the C code and create an executable named `recommender`:
    ```bash
    gcc movie_recommender.c -o recommender
    ```
3.  **Execute:** Run the compiled program:
    ```bash
    ./recommender
    ```
