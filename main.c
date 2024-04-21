#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define LENGTH 100

bool notInBase(char[]);  // проверяет есть ли логин и пароль в базе
void voting();  // голосование и последующая запись ответа в базу
void show_diagram();  // читает данные из файла и выводит диаграмму
void write_new_user(char[], int);  // записывает нового пользователя в базу

int main(void)
{
    char c;
    char login[LENGTH];
    char pass[LENGTH];
    int login_len;
    int pass_len;
    
    printf("Welcome, mother fucker!\n");
    printf("Now, you will vote in one simple poll!\n");
    printf("But, firstly you must register\n");

    while(true) {
        printf("\nEnter your login: ");
        for (login_len = 0; (c = getchar()) != '\n'; login_len++)
            login[login_len] = c;
        login[login_len] = '\0';
        
        printf("\nEnter your pass: ");
        for (pass_len = 0; (c = getchar()) != '\n'; pass_len++)
            pass[pass_len] = c;
        pass[pass_len] = '\0';

        if(notInBase(login)) {  // если нету такого пользователя 
            write_new_user(login, login_len);
            voting();
            break;
        }
        else {  // если есть такой пользователь
            printf("\nI see that you already voted, little mother fucker -_-\n");
            continue;
        }
    }
    show_diagram();
    return 0;
}

bool notInBase(char login[])
{
    FILE *file = fopen("D:\\Coding\\C\\projects\\voting-system\\data\\database.txt", "r");

    char *lines[LENGTH];
    char current_line[LENGTH];
    int len = 0;

    // Записываем строки с логинами
    while (fgets(current_line, LENGTH, file) != NULL) 
        lines[len++] = strdup(current_line);
    fclose(file);

    // Проверка на совпадения
    for (int i = 0; i < len; i++) {
        // Удаляем символ новой строки в конце строки, если он есть
        if (strlen(lines[i]) > 0 && lines[i][strlen(lines[i]) - 1] == '\n') 
            lines[i][strlen(lines[i]) - 1] = '\0';

        // Сравниваем строки
        if (strlen(login) == strlen(lines[i]) && strcmp(login, lines[i]) == 0) {
            // Освобождаем память, выделенную для строк
            for (int j = 0; j < len; j++) free(lines[j]);
            return false;
        }
    }

    // Освобождаем память, выделенную для строк
    for (int i = 0; i < len; i++) free(lines[i]);
    return true;
}

void voting()
{
    char choice;

    printf("\nNow, i just ask you one simple question:\n");
    printf("How you think, what subjects in school could be a really useless?\n");
    printf("[1] - History\n");
    printf("[2] - Even more History\n");
    printf("[3] - Not history");

    while(true) {
        printf("\n>>> ");
        scanf("%c", &choice);
        while(getchar() != '\n');

        if(choice != '1' && choice != '2' && choice != '3') {
            printf("You are fucken dumbass! You just had to choose between 1 and 2 or 3, bastard!\n");
            continue;
        }
        
        FILE *file = fopen("D:\\Coding\\C\\projects\\voting-system\\data\\votes.txt", "a");
        fprintf(file, "%c", choice);
        fclose(file);
        printf("Your answer was saved successfully!\n");
        break;
    }
}

void show_diagram()
{
    FILE *file = fopen("D:\\Coding\\C\\projects\\voting-system\\data\\votes.txt", "r");
    char line[LENGTH];
    
    int good_ans = 0;
    int dumb_ans = 0;

    fgets(line, LENGTH, file);
    fclose(file);
    
    for (int i = 0; i < strlen(line); i++) {
        if(line[i] == '1' || line[i] == '2') good_ans++;
        else if(line[i] == '3') dumb_ans++;
    }

    printf("\n==============================================\n");
    printf("History:\t");
    for(int i = 0; i < good_ans; i++) printf("+");
    printf("\n");
    printf("Not History:\t");
    for(int i = 0; i < dumb_ans; i++) printf("+");
    printf("\n");
    printf("==============================================\n\n");
}

void write_new_user(char login[], int login_len)
{
    FILE *file = fopen("D:\\Coding\\C\\projects\\voting-system\\data\\database.txt", "a");
    login[login_len++] = '\n';
    login[login_len] = '\0';
    fprintf(file, "%s", login);
    fclose(file);
    printf("\nRegistration was successfully!\n");
}