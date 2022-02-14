#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>

char* locate(char* dirname, char archivo[]) {
    DIR* dir = opendir(dirname);
    struct dirent* entity;

    if (dir == NULL) {
        return "Archivo No encontrado";
    }

    printf("#### Leyendo archivos en: %s\n", dirname);

    entity = readdir(dir);
    while (entity != NULL) {
	int sanity = 0;

        printf("%hhd %s/%s\n", entity->d_type, dirname, entity->d_name);

	if (strcmp(entity->d_name,  archivo) == 0) {
		char *res = malloc(strlen(dirname) + strlen(entity->d_name) + 1);
		printf(" ---- %s/%s ----\n", dirname, entity->d_name);
		strcat(res, dirname);
		strcat(res, "/");
		strcat(res, entity->d_name);
		printf(" **** %s ****\n", res);
		sanity = 1;
		return res;
		}
	if (sanity == 1) { break; }
        if (entity->d_type == DT_DIR && strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, "..") != 0) {
            char path[250] = { 0 };
            strcat(path, dirname);
            strcat(path, "/");
            strcat(path, entity->d_name);



            locate(path, archivo);
	}

        entity = readdir(dir);
    }

    closedir(dir);
}

int main(int argc, char* argv[]) {
    char root[62] = "/home/centurion/01 UTB/Sistemas Operativos/Conducta de Entrada";
    char *delta = locate(root, "A1");
    char *omega = locate(root, "A6");
    printf("\n El archivo se encuentra en: %s \n", delta);
    printf("\n El archivo se encuentra en: %s \n", omega);

    free(delta);
    free(omega);
    return 0;
}
