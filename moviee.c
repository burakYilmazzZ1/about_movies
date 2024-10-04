#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
void listBudgetArray(const char *fileName);
void listNameArray(const char *fileName);
void listGenres(const char *fileName);
void listMovieByYear(const char *fileName);
void listMovieByScore(const char *fileName);
void showMovieInfo(const char *fileName, const char *title);
void countGenreFrequency(const char *fileName);
typedef struct {
    int budget;
    int year;
    char *runtime;
    char *title;
    char *titletype;
    char *top250;
}Budget;
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
}Name;
typedef struct{
    int count;
    char *genre;
}GenreCount;
int countLines(const char *fileName){
    FILE *fp;
    char line[1024];
    int linecounts=0;
    fp=fopen(fileName,"r");
    if(fp==NULL) exit(1);
    while (fgets(line,sizeof(line),fp))
    {
        linecounts++;
    }
    fclose(fp);
    return linecounts;
}
void parseLine(const char *line, Budget *budget ){
   char buffer[1024];
   char *token;
   int fieldIndex=0;
   strcpy(buffer, line);
   token=strtok(buffer, ";");
   budget->title = NULL;
   budget->titletype = NULL;
   budget->top250 = NULL;

   while(token !=NULL){
     switch (fieldIndex) {
            case 0:
                budget->budget = atoi(token);
                break;
            case 1:
                budget->title = strdup(token);
                break;
            case 2:
                budget->titletype = strdup(token);
                break;
            case 5:
                budget->runtime = strdup(token);
                break;
            case 6:
                budget->year = atoi(token);
                break;
            case 9:
                budget->top250 = strdup(token);
                break;
        }
   fieldIndex++;
   token=strtok(NULL,";");
   }
}
void parse1line(const char *line, Name *name) {
    char buffer[1024];
    char *token;
    int fieldIndex = 0;
    strcpy(buffer, line);
    token = strtok(buffer, ";");
    name->title = NULL;
    name->directors = NULL;
    name->genre = NULL;
    name->mustsee = NULL;
    name->url = NULL;
    while (token != NULL) {
        switch (fieldIndex) {
            case 1:
                name->title = strdup(token);
                break;
            case 3:
                name->directors = (char **)malloc(sizeof(char *));
                name->directors[0]=strdup(token);
                name->directorCount=1;
                break;
            case 4:
                name->rating=atof(token);
                break;
            case 7:
                name->genre=(char **)malloc(sizeof(char *));
                name->genre[0] = strdup(token);
                name->genreCount=1;
                break;
            case 8:
                name->score = atof(token); 
                break;
            case 10:
                name->mustsee = strdup(token);
                break;
            case 11:
                name->url = strdup(token);
                break;
        }
        fieldIndex++;
        token = strtok(NULL, ";");  
    }
}
int main(int argc, char *argv[]) {
    if (argc < 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    const char *filename = argv[1];
    int choice;
    char title[1024];

    do {
        printf("------------------------------------------------\n");
        printf("*                                              *\n");
        printf("*   1. List of budget array                    *\n");
        printf("*   2. List of name array                      *\n");
        printf("*   3. List of Genres                          *\n");
        printf("*   4. List of the Movie Through the Years     *\n");
        printf("*   5. List of the Movie Through the Scores    *\n");
        printf("*   6. All information of a Single Movie       *\n");
        printf("*   7. Frequency of the Genres                 *\n");
        printf("*   8. Exit                                    *\n");
        printf("*                                              *\n");
        printf("------------------------------------------------\n");
        printf("Enter your choice from 1 to 8: ");
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n');
            printf("\nWrong selection, Please try again.\n");
            continue;
        }
        while (getchar() != '\n');

        if (choice < 1 || choice > 8) {
            printf("\nWrong selection, Please try again.\n");
        } else {
            switch (choice) {
                case 1:
                    listBudgetArray(filename);
                    break;
                case 2:
                    listNameArray(filename);
                    break;
                case 3:
                    listGenres(filename);
                    break;
                case 4:
                    listMovieByYear(filename);
                    break;
                case 5:
                    listMovieByScore(filename);
                    break;
                case 6:
                    printf("Enter the title of movie: ");
                    if (fgets(title, sizeof(title), stdin) != NULL) {
                        title[strcspn(title, "\n")] = '\0';
                        showMovieInfo(filename, title);
                    } else {
                        printf("Error reading input.\n");
                    }
                    break;
                case 7:
                    countGenreFrequency(filename);
                    break;
                case 8:
                    printf("Exiting...\n");
                    exit(0);
            }
        }
    } while (1);

    return 0;
}
void listNameArray(const char *fileName) {
    int lineCount = countLines(fileName);
    Name *name = (Name *)malloc(lineCount * sizeof(Name));
    if (name == NULL) {
        perror("Failed to allocate memory for name array");
        exit(1);
    }
    char line[1024];
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) {
        perror("Failed to open file");
        free(name);
        exit(1);
    }
    int index = 0;
    while (fgets(line, sizeof(line), fp)) {
        parse1line(line, &name[index]); 
        index++;
    }
    fclose(fp);
    for (int i = 1; i < lineCount; i++) {
        printf("-----------------------\n");
        printf("Title: %s\n", name[i].title ? name[i].title : "N/A");
        printf("Directors: %s\n", (name[i].directors && name[i].directorCount > 0) ? name[i].directors[0] : "N/A");
        printf("Rating: %lf\n", name[i].rating);
        printf("Genres: %s\n", (name[i].genre && name[i].genreCount > 0) ? name[i].genre[0] : "N/A");
        printf("Votes: %lf\n", name[i].score);
        printf("Must see: %s\n", name[i].mustsee ? name[i].mustsee : "N/A");
        printf("URL: %s\n", name[i].url ? name[i].url : "N/A");
        printf("-----------------------\n");
    }
    for (int i = 1; i < lineCount; i++) {
        if (name[i].directors) {
            for (int j = 1; j < name[i].directorCount; j++) {
                free(name[i].directors[j]);
            }
            free(name[i].directors);
        }
        if (name[i].genre) {
            for (int j = 1; j < name[i].genreCount; j++) {
                free(name[i].genre[j]);
            }
            free(name[i].genre);
        }
        free(name[i].title);
        free(name[i].mustsee);
        free(name[i].url);
    }
    free(name);
}
void listBudgetArray(const char *fileName) {
    int lineCount = countLines(fileName);
    Budget *budget = (Budget *)malloc(lineCount * sizeof(Budget));
    if (budget == NULL) {
        perror("Failed to allocate memory for budget array");
        free(budget);
        exit(1);
    }
    char line[1024];
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) {
        perror("Failed to open file");
        free(budget);
        exit(1);
    }
    int index = 0;
    while (fgets(line, sizeof(line), fp)) {
        parseLine(line, &budget[index]);
        index++;
    }
    fclose(fp);
    for (int i = 1; i < lineCount; i++) {
        printf("-----------------------\n");
        printf("Budget: %d\n", budget[i].budget);
        printf("Year: %d\n", budget[i].year);
        printf("Runtime: %s\n",budget[i].runtime ? budget[i].runtime:"N/A");
        printf("Title: %s\n", budget[i].title ? budget[i].title : "N/A");
        printf("Title type: %s\n", budget[i].titletype ? budget[i].titletype : "N/A");
        printf("Top 250: %s\n", budget[i].top250 ? budget[i].top250 : "N/A");
        printf("-----------------------\n");
    }
    for (int i = 1; i < lineCount; i++) {
        free(budget[i].title);
        free(budget[i].titletype);
        free(budget[i].top250);
        free(budget[i].runtime);
    }
    free(budget);
}
void listGenres(const char *fileName) {
    int lineCount = countLines(fileName);
    Name *name = (Name*)malloc(lineCount * sizeof(Name));
    if (name == NULL) exit(1);
    char line[1024];
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) exit(1);
    int index = 0;
    while (fgets(line, sizeof(line), fp)) {
        parse1line(line, &name[index]);
        index++;
    }
    fclose(fp);
    printf("Genres:\n");
    for (int i = 1; i < lineCount; i++) {
        if (name[i].genre != NULL) {
            for (int j = 0; j < 1; j++) {
                if (name[i].genre[j] != NULL) {
                    printf("%s\n", name[i].genre[j]);
                }
            }
        }
    }
    for (int i = 1; i < lineCount; i++) {
        free(name[i].directors ? name[i].directors[0] : NULL);
        free(name[i].directors);
        free(name[i].genre ? name[i].genre[0] : NULL);
        free(name[i].genre);
        free(name[i].title);
        free(name[i].mustsee);
        free(name[i].url);
    }
    free(name);
}
void listMovieByYear(const char *fileName) {
    int lineCount = countLines(fileName);
    Budget *budget = (Budget*)malloc(lineCount * sizeof(Budget));
    if (budget == NULL) exit(1);
    char line[1024];
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) exit(1);
    int index = 0;
    while (fgets(line, sizeof(line), fp)) {
        parseLine(line, &budget[index]);
        index++;
    }
    fclose(fp);
    int min = budget[0].year, max = budget[0].year;
    for (int i = 1; i < lineCount; i++) {
        if (budget[i].year < min) min = budget[i].year;
        if (budget[i].year > max) max = budget[i].year;
    }

    for (int year = min; year <= max; year++) {
        printf("Year: %d\n", year);
        for (int i = 1; i < lineCount; i++) {
            if (budget[i].year == year) {
                printf(" Title: %s\n", budget[i].title ? budget[i].title : "N/A");
            }
        }
        printf("-----------------------\n");
    }
    for (int i = 1; i < lineCount; i++) {
        free(budget[i].title);
        free(budget[i].titletype);
        free(budget[i].top250);
    }
    free(budget);
}
void listMovieByScore(const char *fileName) {
    int lineCount = countLines(fileName);
    Name *name = (Name*)malloc(lineCount * sizeof(Name));
    if (name == NULL) exit(1);
    char line[1024];
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) exit(1);
    int index = 0;

    while (fgets(line, sizeof(line), fp)) {
        parse1line(line, &name[index]);
        index++;
    }
    fclose(fp);

    for (int i = 1; i < lineCount - 1; i++) {
        for (int j = 0; j < lineCount - i - 1; j++) {
            if (name[j].score < name[j + 1].score) {
                Name temp = name[j];
                name[j] = name[j + 1];
                name[j + 1] = temp;
            }
        }
    }
    for (int i = 1; i < lineCount; i++) {
        printf("-----------------------\n");
        printf("Title: %s\n", name[i].title ? name[i].title : "N/A");
        printf("Votes: %lf\n", name[i].score);
        printf("Directors: %s\n", name[i].directors ? name[i].directors[0] : "N/A");
        printf("Rating: %lf\n", name[i].rating);
        printf("Genres: %s\n", name[i].genre ? name[i].genre[0] : "N/A");
        printf("Must see: %s\n", name[i].mustsee ? name[i].mustsee : "N/A");
        printf("URL: %s\n", name[i].url ? name[i].url : "N/A");
        printf("-----------------------\n");
    }
    for (int i = 1; i < lineCount; i++) {
        free(name[i].directors ? name[i].directors[0] : NULL);
        free(name[i].directors);
        free(name[i].genre ? name[i].genre[0] : NULL);
        free(name[i].genre);
        free(name[i].title);
        free(name[i].mustsee);
        free(name[i].url);
    }
    free(name);
}
void showMovieInfo(const char* fileName, const char *title) {
    int lineCount = countLines(fileName);
    Name *name = (Name*)malloc(lineCount * sizeof(Name));
    if (name == NULL) exit(1);
    Budget *budget= (Budget*)malloc(lineCount*sizeof(Budget));
    if(budget==NULL) exit(1);
    char line[1024];
    FILE *fp = fopen(fileName, "r");
    if (fp == NULL) exit(1);
    int index = 0;

    while (fgets(line, sizeof(line), fp)) {
        parse1line(line, &name[index]);
        parseLine(line,&budget[index]);
        index++;
    }
    
    fclose(fp);
    for (int i = 1; i < lineCount; i++) {
        if (strcmp(name[i].title, title) == 0) {
            printf("-----------------------\n");
            printf("Budget: %d\n", budget[i].budget);
            printf("Title: %s\n", name[i].title ? name[i].title : "N/A");
            printf("Title type: %s\n", budget[i].titletype ? budget[i].titletype : "N/A");
            printf("Directors: %s\n", name[i].directors ? name[i].directors[0] : "N/A");
            printf("Rating: %lf\n", name[i].rating);
            printf("Runtime: %s\n",budget[i].runtime ? budget[i].runtime:"N/A");
            printf("Year: %d\n", budget[i].year);
            printf("Genres: %s\n", name[i].genre ? name[i].genre[0] : "N/A");
            printf("Votes: %lf\n", name[i].score);
            printf("Top 250: %s\n", budget[i].top250 ? budget[i].top250 : "N/A");
            printf("Must see: %s\n", name[i].mustsee ? name[i].mustsee : "N/A");
            printf("URL: %s\n", name[i].url ? name[i].url : "N/A"); 
            printf("-----------------------\n");
            break;
        }
    }
    for (int i = 1; i < lineCount; i++) {
        free(name[i].directors ? name[i].directors[0] : NULL);
        free(name[i].directors);
        free(name[i].genre ? name[i].genre[0] : NULL);
        free(name[i].genre);
        free(name[i].title);
        free(name[i].mustsee);
        free(name[i].url);
        free(budget[i].runtime);
        free(budget[i].titletype);
        free(budget[i].top250);
    }
    free(budget);
    free(name);
}
void countGenreFrequency(const char *fileName) {
    int lineCount = countLines(fileName); 
    Name *name = (Name*)malloc(lineCount * sizeof(Name)); 
    if (name == NULL) exit(1);
    char line[1024];
    FILE *fp = fopen(fileName, "r"); 
    if (fp == NULL) {
        perror("Failed to open file");
        free(name);
        exit(EXIT_FAILURE);
    }

    int index = 0;
    while (fgets(line, sizeof(line), fp)) {
        parse1line(line, &name[index]); 
        index++;
    }
    fclose(fp);
    GenreCount *genreCounts = (GenreCount*)malloc(lineCount * sizeof(GenreCount));
    if (genreCounts == NULL) exit(1);

    int genreCount = 0;
    for (int i = 1; i < lineCount; i++) {
        if (name[i].genre != NULL) { 
            for (int j = 0; j < 1; j++) {
                if (name[i].genre[j] != NULL) { 
                    int found = 0;
                    for (int k = 0; k < genreCount; k++) {
                        if (strcmp(genreCounts[k].genre, name[i].genre[j]) == 0) {
                            genreCounts[k].count++;
                            found = 1;
                            break;
                        }
                    }
                    if (!found) {
                        genreCounts[genreCount].genre = strdup(name[i].genre[j]);
                        genreCounts[genreCount].count = 1;
                        genreCount++;
                    }
                }
            }
        }
    }
    for (int i = 1; i < genreCount; i++) {
        printf("Genres: %s, Frequency: %d\n", genreCounts[i].genre, genreCounts[i].count);
        free(genreCounts[i].genre);
    }
    free(genreCounts);
    for (int i = 1; i < lineCount; i++) {
        free(name[i].directors ? name[i].directors[0] : NULL);
        free(name[i].directors);
        free(name[i].genre ? name[i].genre[0] : NULL);
        free(name[i].genre);
        free(name[i].title);
        free(name[i].mustsee);
        free(name[i].url);
    }
    free(name);
}


