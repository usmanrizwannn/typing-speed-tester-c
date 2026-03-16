#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>

void trim_whitespace(char *str) {
    char *start = str;
    char *end;

    while (isspace((unsigned char)*start)) start++;

    if (*start == '\0') {
        *str = '\0';
        return;
    }

    end = start + strlen(start) - 1;
    while (end > start && isspace((unsigned char)*end)) end--;

    *(end + 1) = '\0';
    memmove(str, start, strlen(start) + 1);
}

double calculate_accuracy(const char *original, const char *typed) {
    int correct = 0;
    int total = strlen(original);
    int min = strlen(typed) < total ? strlen(typed) : total;
    int i;

    for (i = 0; i < min; i++) {
        if (original[i] == typed[i]) {
            correct++;
        }
    }

    return total > 0 ? (double)correct / total * 100.0 : 0.0;
}

int calculate_wpm(double time_seconds, const char *input) {
    double words = strlen(input) / 5.0;

    if (time_seconds > 0) {
        return (int)((words * 60) / time_seconds);
    }
    return 0;
}

int main() {
    int num_rounds, i, total_wpm = 0;
    double total_accuracy = 0;

    const char *sentences[] = {
        "The quick brown fox jumps over the lazy dog.",
        "C programming is fun and exciting to learn.",
        "Practice typing daily to improve your speed.",
        "Arrays store multiple values in one variable.",
        "Loops repeat code execution efficiently.",
        "Functions make code reusable and organized.",
        "Pointers store memory addresses in C language.",
        "Data structures organize complex information.",
        "Algorithms solve computational problems.",
        "Debugging finds and fixes code errors."
    };

    int num_sentences = sizeof(sentences) / sizeof(sentences[0]);

    printf("=== Advanced Typing Speed Test ===\n");
    printf("How many rounds? (1-5): ");
    scanf("%d", &num_rounds);
    getchar();

    if (num_rounds < 1 || num_rounds > 5) num_rounds = 3;

    srand(time(NULL));

    for (i = 1; i <= num_rounds; i++) {
        printf("\n--- Round %d/%d ---\n", i, num_rounds);

        int idx = rand() % num_sentences;
        const char *target = sentences[idx];

        printf("Type this sentence:\n");
        printf("%s\n\n", target);
        printf("Press Enter to start...");
        getchar();

        printf("3...");
        sleep(1);
        printf("2...");
        sleep(1);
        printf("1...\n");
        sleep(1);

        clock_t start = clock();
        char input[512];
        fgets(input, sizeof(input), stdin);
        clock_t end = clock();

        double time_sec = (double)(end - start) / CLOCKS_PER_SEC;

        trim_whitespace(input);

        int wpm = calculate_wpm(time_sec, input);
        double acc = calculate_accuracy(target, input);

        printf("\nTime: %.2f sec\n", time_sec);
        printf("WPM: %d\n", wpm);
        printf("Accuracy: %.1f%%\n", acc);

        total_wpm += wpm;
        total_accuracy += acc;

        printf("Press Enter to continue...");
        getchar();
    }

    printf("\n=== FINAL RESULTS ===\n");
    printf("Average WPM: %d\n", total_wpm / num_rounds);
    printf("Average Accuracy: %.1f%%\n", total_accuracy / num_rounds);

    return 0;
}

