#include <stdio.h>
#include <string.h>
#include <dirent.h>
#include <stdlib.h>
char* locate(const char* dirname, char archivo[]) {
    DIR* dir = opendir(dirname);
    if (dir == NULL) {
        return "Archivo No encontrado";
    }

    printf("Leyendo archivos en: %s\n", dirname);

    struct dirent* entity;
    entity = readdir(dir);
    while (entity != NULL) {
	char res[strlen(dirname) + strlen(archivo) + 2];
	char *respuesta = res;

        printf("%hhd %s/%s\n", entity->d_type, dirname, entity->d_name);

	if (strcmp(entity->d_name,  archivo) == 0) {
		printf(" ---- %s/%s ----\n", dirname, entity->d_name);
		strcat(res, dirname);
		strcat(res, "/");
		strcat(res, entity->d_name);
		printf(" **** %s  ****", res);
		return respuesta;
		}

        if (entity->d_type == DT_DIR && strcmp(entity->d_name, ".") != 0 && strcmp(entity->d_name, "..") != 0) {
            char path[100] = { 0 };
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
    char *ojo = locate(root, "A3");
    printf("\n El archivo se encuentra en: %s \n", ojo);
    free(ojo);
    return 0;
}
