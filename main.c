#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct library
{
    char *book_name;
    char *author_name;
    float cost;
    int no_of_pages;
};

void saveBooks(struct library *lib, int count)
{
    FILE *file = fopen("books.txt", "w");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%s\n", lib[i].book_name);
        fprintf(file, "%s\n", lib[i].author_name);
        fprintf(file, "%.2f\n", lib[i].cost);
        fprintf(file, "%d\n", lib[i].no_of_pages);
    }

    fclose(file);
}

int loadBooks(struct library **lib)
{
    FILE *file = fopen("books.txt", "r");
    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 0;
    }

    int count = 0;
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file) != NULL)
    {
        (*lib) = (struct library *)realloc(*lib, (count + 1) * sizeof(struct library));
        (*lib)[count].book_name = strdup(buffer);

        fgets(buffer, sizeof(buffer), file);
        (*lib)[count].author_name = strdup(buffer);

        fgets(buffer, sizeof(buffer), file);
        (*lib)[count].cost = atof(buffer);

        fgets(buffer, sizeof(buffer), file);
        (*lib)[count].no_of_pages = atoi(buffer);

        count++;
    }

    fclose(file);
    return count;
}

void freeMemory(struct library *lib, int count)
{
    for (int i = 0; i < count; i++)
    {
        free(lib[i].book_name);
        free(lib[i].author_name);
    }
    free(lib);
}

void issueBook(struct library *lib, int count)
{
    if (count == 0)
    {
        printf("\nThere are no books stored!!\n\n");
        return;
    }

    printf("\nEnter the index of the book you want to issue: ");
    int index;
    scanf("%d", &index);

    if (index >= 0 && index < count)
    {
        printf("\nBook '%s' has been issued to the user.\n\n", lib[index].book_name);
    }
    else
    {
        printf("\nInvalid book index.\n\n");
    }
}

void reissueBook(struct library *lib, int count)
{
    if (count == 0)
    {
        printf("\nThere are no books stored!!\n\n");
        return;
    }

    printf("\nEnter the index of the book you want to reissue: ");
    int index;
    scanf("%d", &index);
    index=+1;

    if (index >= 0 && index < count)
    {
        printf("\nBook '%s' has been reissued to the user.\n\n", lib[index].book_name);
    }
    else
    {
        printf("\nInvalid book index.\n\n");
    }
}

int main()
{
    struct library *lib = NULL;
    int count = 0;

    count = loadBooks(&lib);

    int i, j;
    i = 0;
    j = 0;

    while (j != 5)
    {
        printf("\n\n1. Add Book details\n");
        printf("2. Display the list of books and its details\n");
        printf("3. Display the total no. of books in the library\n");
        printf("4. Issue a book\n");
        printf("5. Reissue a book\n");
        printf("6. Exit\n\n");
        printf("Enter the number: ");
        scanf("%d", &j);

        switch (j)
        {
            case 1:
                printf("\nYou can add the details of the book\n");
                lib = (struct library *)realloc(lib, (count + 1) * sizeof(struct library));

                printf("Enter the book name: ");
                char buffer[100];
                scanf(" %[^\n]s", buffer);
                lib[i].book_name = strdup(buffer);

                printf("Enter the author name: ");
                scanf(" %[^\n]s", buffer);
                lib[i].author_name = strdup(buffer);

                printf("Enter the number of pages: ");
                scanf("%d", &lib[i].no_of_pages);

                printf("Enter the cost of the book: ");
                scanf("%f", &lib[i].cost);

                count++;
                i++;
                break;

            case 2:
                if (count == 0)
                {
                    printf("\nThere are no books stored!!\n\n");
                }
                else
                {
                    printf("\nYou can view the list of books\n");
                    printf("The list of books are:\n\n");
                    for (i = 0; i < count; i++)
                    {
                        printf("Book name: %s\n", lib[i].book_name);
                        printf("Author name: %s\n", lib[i].author_name);
                        printf("Number of pages: %d\n", lib[i].no_of_pages);
                        printf("Cost of the book: %.2f\n", lib[i].cost);
                        printf("Index: %d\n\n",i);

                    }
                }
                break;

            case 3:
                printf("\nTotal number of books in the library: %d\n\n", count);
                break;

            case 4:
                issueBook(lib, count);
                break;

            case 5:
                reissueBook(lib, count);
                break;

            case 6:
                saveBooks(lib, count);
                freeMemory(lib, count);
                exit(0);

            default:
                printf("\nInvalid number entered\n\n");
        }
    }
    return 0;
}
