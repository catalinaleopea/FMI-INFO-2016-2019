#include <stdio.h>
#include <unistd.h>
#include <dirent.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <libgen.h>
#include <string.h>
#include "utils.h"

char target_binary_path[SIZE];
void parse_fd(char *fd_path);
void parse_stat(char *stat_path, stat_result_t result);

void traverse(char * path, callback_t action) {
    char backup_cwd[SIZE];
    DIR * target_dir = NULL;
    struct dirent *entry = NULL;

    target_dir = opendir(path);
    if (target_dir == NULL)
        return;

    if(!getcwd(backup_cwd, SIZE)) {
        fprintf(stderr, "error at %s:%d", __FUNCTION__, __LINE__);
        return;
    }

    chdir(path);
    while ((entry = readdir(target_dir)) != NULL) {
        char abs_path[SIZE];
        if(get_int(entry->d_name)) {
            realpath(entry->d_name, abs_path);
            action(abs_path);
        }
    }
    chdir(backup_cwd);
}

void extract_info(char * path) {
    dictionary_t result_dict;
    result_dict.capacity = SIZE;
    char stat[SIZE];
    char io[SIZE];
    char cmdline[SIZE];
    char real_cmdline[SIZE];
    char real_cwd[SIZE];
    char cwd[SIZE];
    char fdinfo[SIZE];

    strcpy(stat, path);
    strcpy(io, path);
    strcpy(cmdline, path);
    strcpy(cwd, path);
    strcpy(fdinfo, path);

    strcat(stat, "/stat");
    strcat(io, "/io");
    strcat(cmdline, "/cmdline");
    strcat(cwd, "/cwd");
    strcat(fdinfo, "/fdinfo");

    char stat_result[STAT_ENTRY_NUM][STAT_ENTRY_SIZE];
    parse_stat(stat, stat_result);

    printf("Pid: %s\n", stat_result[PID]);
    printf("PPid: %s\n", stat_result[PPID]);

    printf("Command line: %s\n", read_cmdline(cmdline, real_cmdline));

    realpath(cwd, real_cwd);
    printf("Current directory: %s\n", real_cwd);

    traverse(fdinfo, parse_fd);

    printf("State: %s\n", stat_result[STATE]);

    parse(io, &result_dict);

    printf("Chars read: %s\n", get_value("syscr", &result_dict));
    printf("Chars written: %s\n", get_value("syscw", &result_dict));

    printf("Niceness: %s\n", stat_result[NICENESS]);

    printf("Clock interrupts UM: %s\n", stat_result[UTIME]);
    printf("Clock interrupts kernel: %s\n", stat_result[STIME]);

    printf("\n");
}

void parse_fd(char * fd_path) {
    if (!strcmp(basename(fd_path), "1") || !strcmp(basename(fd_path), "2") || !strcmp(basename(fd_path), "3"))
        return;

    dictionary_t result_dict;
    result_dict.capacity = SIZE;

    parse(fd_path, &result_dict);

    printf("fd: %s pos: %s\n", basename(fd_path), get_value("pos", &result_dict));
}

void parse_stat(char *stat_path, stat_result_t result) {
    FILE *fp = fopen(stat_path, "r");
    size_t len = 0;
    size_t idx = 0;
    char *delim = " \n\t";
    char *line = NULL;

    getline(&line, &len, fp);

    char *token;
    token = strtok(line, delim);
    while (token != NULL) {
        strcpy(result[idx++], token);
        token = strtok(NULL, delim);
    }

    free(line);
    fclose(fp);
}

void fuck(char * test) {
    char OG_path[SIZE];
    char result[SIZE];

    strcpy(OG_path, test);

    realpath(strcat(test, "/exe"), result);

    if(!strcmp(result, target_binary_path))
        extract_info(OG_path);

}

int main(int argc, char * argv[]) {
    if(argc != 2) {
        printf("Usage: %s <executable_name>\n", argv[0]);
        exit(-1);
    }

    realpath(argv[1], target_binary_path);

    if(!is_ELF(target_binary_path)) {
        printf("%s is not a valid ELF binary\n", argv[1]);
        exit(-2);
    }

    traverse("/proc", fuck);

    return 0;
}
