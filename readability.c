#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letters(const char *text);
int count_words(const char *text);
int count_sentences(const char *text);

int main(void)
{
    char text[2048];

    printf("Text: ");
    if (fgets(text, sizeof(text), stdin) == NULL)
    {
        return 1;
    }

    text[strcspn(text, "\n")] = '\0';

    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    double L = ((double)letters / (double)words) * 100.0;
    double S = ((double)sentences / (double)words) * 100.0;
    int index = (int)round(0.0588 * L - 0.296 * S - 15.8);

    if (index < 1)
        printf("Before Grade 1\n");
    else if (index >= 16)
        printf("Grade 16+\n");
    else
        printf("Grade %d\n", index);

    return 0;
}

int count_letters(const char *text)
{
    int letters = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (isalpha((unsigned char)text[i]))
            letters++;
    }
    return letters;
}

int count_words(const char *text)
{
    int words = 0;
    int in_word = 0;

    for (int i = 0; text[i] != '\0'; i++)
    {
        if (!isspace((unsigned char)text[i]) && in_word == 0)
        {
            in_word = 1;
            words++;
        }
        else if (isspace((unsigned char)text[i]))
        {
            in_word = 0;
        }
    }

    return words;
}

int count_sentences(const char *text)
{
    int sentences = 0;
    for (int i = 0; text[i] != '\0'; i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
            sentences++;
    }
    return sentences;
}
