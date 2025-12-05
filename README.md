---

# 🎬 Movie Data Processing Program

*A C-based command-line application for processing IMDb-like movie datasets*

This project reads a movie dataset from a file, parses all information into structured data types, and provides various listing, searching, and statistical analysis options through a menu-driven interface.

---

## 🚀 Features

### ✔ **Budget Array Listing**

Displays movies with:

* Budget
* Year
* Runtime
* Title
* Title Type
* Top 250 Information

### ✔ **Name Array Listing**

Shows detailed film metadata:

* Title
* Directors
* Genres
* Rating
* Score
* Must-see status
* URL

### ✔ **List All Genres**

Prints all unique genres found in the dataset.

### ✔ **List Movies by Years**

Groups and displays movies according to their release years.

### ✔ **Sort Movies by Score**

Sorts movies in descending order based on their score value.

### ✔ **Display Full Information of a Single Movie**

Given a movie title, the program prints:

* Budget
* Year
* Genres
* Directors
* Runtime
* Rating
* Score
* Top 250
* URL

### ✔ **Genre Frequency Calculation**

Counts how many times each genre appears across all movies.

---

## 📁 Data Structures

### **Budget Structure**

```c
typedef struct {
    int budget;
    int year;
    char *runtime;
    char *title;
    char *titletype;
    char *top250;
} Budget;
```

### **Name Structure**

```c
typedef struct {
    char **genre;
    int genreCount;
    char *title;
    char **directors;
    int directorCount;
    char *mustsee;
    double rating;
    double score;
    char *url;
} Name;
```

---

## 🧩 Program Menu

The program provides the following menu to the user:

```
1. List of Budget Array
2. List of Name Array
3. List All Genres
4. List Movies Through the Years
5. List Movies Through the Scores
6. Display All Information of a Single Movie
7. Genre Frequency
8. Exit
```

---

## 📦 Usage

Compile and run the program:

```bash
gcc project.c -o movieapp
./movieapp data.csv
```

---

## 🛠 Techniques Used

* CSV-style file parsing (`strtok`)
* Dynamic memory allocation (`malloc`, `free`)
* Struct-based data modelling
* Sorting algorithms (Bubble Sort)
* String manipulation and comparison
* Multi-field data processing (Directors, Genres, etc.)

---

## 📌 Notes

* The first row of the dataset is treated as a header; loops commonly start from index `1`.
* All dynamically allocated memory for strings is freed at the end.
* Both `Budget` and `Name` structures are populated from the same dataset.

---

