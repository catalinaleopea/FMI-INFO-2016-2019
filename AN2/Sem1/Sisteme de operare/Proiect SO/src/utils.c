#include <unistd.h>
#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <sys/resource.h>

#define SIZE 1024
#define STAT_ENTRY_NUM 52
#define STAT_ENTRY_SIZE 64

#define NICENESS 18
#define UTIME 13
#define STIME 14

enum {PID = 0, COMM, STATE, PPID};

typedef char statResult[STAT_ENTRY_NUM][STAT_ENTRY_SIZE];
typedef void (*callback)(char *);

typedef struct {
    char key[SIZE];
    char value[SIZE];
} dictionaryEntry;

typedef struct {
    dictionaryEntry entries[SIZE];
    size_t capacity;
    size_t length;
} dictionary;

int getInt(const char *input);
int parse(const char *file, dictionary *resultDictionary);
char *trim(char *input);

char *getValue(const char *key, dictionary *dict);
char *getKey(const char *value, dictionary *dict);
char *readCmdLine(const char *path, char *content);

int getNiceness(pid pd);
int isElf(const char *binaryPath);

int getInt(const char *input) {
    if (input == NULL || *input == '\0' || isspace(*input))
        return 0;
    return strtol(input, NULL, 0);
}

int parse(const char *file, dictionary *resultDictionary) {
    FILE * fp;
    char *line = NULL;
    size_t len = 0;
    size_t idx = 0;
    ssize_t read;

    fp = fopen(file, "r");
    if (fp == NULL) {
        fprintf(stderr, "failed to open %s\n", file);
        return -1;
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        char * key = line;
        char * value = strchr(line, ':');
        *value = 0;
        strcpy(resultDictionary->entries[idx].key, key);
        strcpy(resultDictionary->entries[idx].value, trim(value + 1));
        idx++;
    }
    resultDictionary->length = idx;
    free(line);
    fclose(fp);
    return idx;
}

char *trim(char *input) {
    if (input == NULL || *input == '\0')
        return NULL;

    while (isspace((unsigned char)*input))
        input++;

    if (*input == 0)
        return input;

    char * end = input + strlen(input) - 1;
    while (end > input && isspace((unsigned char)*end))
        end--;

    *(end + 1) = 0;

    return input;
}

char *getValue(const char *key, dictionary *dict) {
    if (key == NULL || *key == '\0')
        return NULL;

    for (size_t i = 0; i < dict->length; i++)
        if(!strcmp(key, dict->entries[i].key))
            return dict->entries[i].value;

    return NULL;
}

char *getKey(const char *value, dictionary_t *dict) {
    if (value == NULL || *value == '\0')
        return NULL;

    for (size_t i = 0; i < dict->length; i++)
        if (!strcmp(value, dict->entries[i].value))
            return dict->entries[i].key;

    return NULL;
}

char *read_cmdline(const char *path, char *content) {
    FILE * fp = fopen(path, "r");
    size_t len = 0;

    getline(&content, &len, fp);

    fclose(fp);

    return content;
}

int get_niceness(pid_t pid) {
    return getpriority(PRIO_PROCESS, pid);
}

int is_ELF(const char *binary_path) {
    char magic[4];
    int fd = open(binary_path, O_RDONLY);
    if(fd < 0) {
        fprintf(stderr, "failed to open %s\n", binary_path);
        return -1;
    }

    read(fd, magic, sizeof magic);

    if(!strncmp(magic, "\177ELF", sizeof magic))
        return 1;

    close(fd);
    return 0;
}
