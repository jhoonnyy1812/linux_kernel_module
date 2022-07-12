#define _GNU_SOURCE
// #include <linux/init.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/stat.h>
#include <sys/dir.h>
#include <fcntl.h>
#include <string.h>
#include <sys/types.h>
#include <stdlib.h>
#include <time.h>

const char *get_filename_ext(const char *filename) {
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename) return "";
    return dot + 1;
}

void searchInDirectory(char *dirname, char *file_type, char *path){
    DIR *dir;
    struct dirent *dirp;
    dir=opendir(dirname);
    chdir(dirname); // Systemcall
    while((dirp=readdir(dir))!=NULL){
        if(dirp->d_type==4){
            if(strcmp(dirp->d_name, ".")==0 || strcmp(dirp->d_name, "..")==0){
                continue;
            }
            searchInDirectory(dirp->d_name, file_type, path);
        }
        else{
            if(strcmp(get_filename_ext(dirp->d_name), file_type)==0){
                printf("Found file!!!\n");
                printf("%s:  %s\n", "FILE", dirp->d_name);
                int fd_in, fd_out;
                struct stat stat;
                off64_t len, ret;
                char *backup;
                fd_in = open(dirp->d_name, O_RDONLY);
                if (fd_in == -1) {
                    printf("Erro ao fazer backup de %s, problema com leitura do arquivo.\n", dirp->d_name);
                }


                if (fstat(fd_in, &stat) == -1) {
                    printf("Erro ao fazer backup de %s, problema com leitura de tamanho.\n", dirp->d_name);
                }

                len = stat.st_size;

                backup = malloc(1035);

                strcat(backup, path);
                strcat(backup, "/");
                strcat(backup, dirp->d_name);

                fd_out = open(backup, O_CREAT | O_WRONLY | O_TRUNC, 0644);
                if (fd_out == -1) {
                    printf("Erro ao fazer backup de %s, problema com arquivo.\n", dirp->d_name);
                }

                do {
                    ret = copy_file_range(fd_in, NULL, fd_out, NULL, len, 0); // System call
                    if (ret == -1) {
                        printf("Erro ao fazer backup de %s, problema com armazenamento de bytes.\n", dirp->d_name);
                    }

                    len -= ret;
                } while (len > 0 && ret > 0);
                close(fd_out);
            }
        }
    }
    chdir("..");
    closedir(dir);
}

int main(int argc, char *argv[]){
    clock_t c1, c2; // System call
    printf("Starting backup...\n");
    c1 = clock();
    char *original_backup_dir;
    FILE *fp = popen("date", "r");
    char path[1035];
    original_backup_dir = malloc(1035);
    strcat(original_backup_dir, "/home/joao.pinto/backups/");
    while (fgets(path, sizeof(path), fp) != NULL) {
    }
    strcat(original_backup_dir, path);

    printf("Directory path: %s", original_backup_dir);

    path[strcspn(original_backup_dir, "\n\t\r")] = 0;

    int status = mkdir(original_backup_dir, S_IRWXU | S_IRWXG | S_IRWXO); // System call
    if(status == 0){
        searchInDirectory(argv[1], argv[2], original_backup_dir);
    }
    c2 = clock();

    printf("Tempo de exceussão: %ld\n", c2-c1/1000);
    return 0;
}