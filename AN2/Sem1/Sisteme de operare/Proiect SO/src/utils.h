#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <sys/resource.h>

#define SIZE 1024
#define STAT_ENTRIES_NUM 52
#define STAT_ENTRY_SIZE 64

#define NICENESS 18
#define UTIME 13
#define STIME 14

enum {PID = 0, COMM, STATE, PPID};

typedef char stat_result_t[STAT_ENTRIES_NUM][STAT_ENTRY_SIZE];
typedef void (*callback_t)(char *);

typedef struct {
    char key[SIZE];
    char value[SIZE];
} dictionary_entry_t;

typedef struct {
    dictionary_entry_t entries[SIZE];
    size_t capacity;
    size_t length;
} dictionary_t;

int get_int(const char *input);
int parse(const char *file, dictionary_t *result_dictionary);
char *trim(char *input);

char *get_value(const char *key, dictionary_t *dict);
char *get_key(const char *value, dictionary_t *dict);
char *read_cmdline(const char *path, char *content);

int get_niceness(pid_t pid);
int is_ELF(const char *binary_path);
