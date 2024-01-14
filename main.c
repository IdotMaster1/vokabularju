// vokabularju | A simple vocabulary trainer
// Copyright (C) 2024 bunkermatty

// This program is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.

// This program is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.

// You should have received a copy of the GNU General Public License
// along with this program.  If not, see <https://www.gnu.org/licenses/>.

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    // Open the Krabbe Text File Format file to get the vocabulary
    FILE *ktff = fopen(argv[1], "r");
    if (ktff == NULL) {
        printf("Error: Could not open file %s\n", argv[1]);
        return 1;
    }

    // Read the file
    size_t len = 0;
    size_t read;
    char *line = NULL;

    int correct = 0;
    int incorrect = 0;

    // Print the comment with color
    while ((read = getline(&line, &len, ktff)) != -1) {
        if(line[0] == '#') {
            printf("\033[0;32m%s\033[0m", line);
        }
        else {
            // Split the line into tokens
            char *token = strtok(line, ":");
            char *answer = strtok(NULL, ";");
            char *explanation = strtok(NULL, "\n");

            // Logic for the trainer/quiz
            while (token != NULL) {
                // COMMENT THESE 3 LINES OUT LATER!
                printf("\033[0;33m%s\033[0m\n", token); 
                printf("\033[0;33m%s\033[0m\n", answer); 
                printf("\033[0;33m%s\033[0m\n", explanation); 

                char input[100];
                printf("What does %s mean?\n", token);
                fgets(input, sizeof(input), stdin);
                input[strcspn(input, "\n")] = 0;

                // Check if the input is correct
                if (answer != NULL) {
                    if(strcmp(input, answer) == 0) {
                        printf("\033[0;32mCorrect!\033[0m\n");
                        printf("%s\n", explanation);
                        correct++;
                    }
                    else {
                        printf("\033[0;31mIncorrect! The correct answer is: %s\033[0m\n", explanation);
                        incorrect++;
                    }
                }
                
                // Get the next line
                token = strtok(NULL, ":");
                explanation = strtok(NULL, ";");
                answer = strtok(NULL, "\n");
            } 
        }
    }
    printf("Correct: %d\n", correct);
    printf("Incorrect: %d\n", incorrect);

    fclose(ktff);
    if (line)
        free(line);

    return 0;
}