#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <Windows.h>
#include <math.h>

static int slowWriter(char *, float);
static double normal(float, int);
static int slowWriterMain(int, const char *[]);
static int firstMain(int, const char *[]);

static int i;

static void weirdForInitializer(int initValue)
{
    i = initValue;
}

static int weirdForCondition(int limit)
{
    // return TRUE;
    return i < limit;
}

static void weirdForAfterCycle()
{
    i++;
}

struct ImageFile
{
    char *filename;
    byte *data;
};

int main(int argc, char const *argv[])
{
    // slowWriterMain(argc,argv);
    // struct ImageFile img1;
    // strcpy(img1.filename, "filename");

    // printf("%s", img1.filename);

    for (int i2 = 0; i2 < 10; i2++)
    {
        printf("%d\n", i2);
    }
    for (weirdForInitializer(5); weirdForCondition(15); weirdForAfterCycle())
    {
        printf("%d\n", i);
    }
}

static int firstMain(int argc, char const *argv[])
{
    int a = 3;
    int b = 6;
    for (int i = 0; i < a; i++)
    {
        printf("i = %d, b = %d\n", i, b);
        b--;
    }

    char name[] = "Test";

    printf("Hello %s \n", name);
    printf("Hello world (:\n");
    return 0;
}

static int slowWriterMain(int argc, char const *argv[])
{
    int running = 1;
    char *text = malloc(sizeof(char) * (100 + 1));
    float average;

    printf("Enter average:");
    scanf("%f", &average);

    while (running)
    {
        printf("Enter text:");
        // scanf("%s" , text);
        fgets(text, 100, stdin);
        // printf("\nText: %s\nAverage: %f\nVariance: %f\n",text,average,variance);
        if (strcmp(text, "quit") == 0)
        {
            running = 0;
            continue;
        }
        slowWriter(text, average);
    }
}

static int slowWriter(char *text, float average)
{
    char *c = text;
    while (*c != '\0')
    {
        printf("%c", *c);
        Sleep(normal(average * 2, 30));
        c += sizeof(char);
    }
    printf("\n");
    return 0;
}

static double normal(float max_range, int iterations)
{
    double result = 0;
    for (int i = 0; i < iterations; i++)
    {
        result += (double)rand() / (RAND_MAX)*max_range;
    }
    // printf("%f",result);
    return result / iterations;
}