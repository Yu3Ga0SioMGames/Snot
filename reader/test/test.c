#include "test.h" // подключаем заголовочный файл

/*char* read_data_from_file(const char* file_path) {
    FILE *file = fopen(file_path, "r");
    if(file == NULL) {
        printf("Error: Cannot open file %s\n", file_path);

        return NULL;
    }

    fseek(file, 0, SEEK_END);
    long length = ftell(file);
    fseek(file, 0, SEEK_SET);

    char* buffer = (char*)malloc(length + 1);
    if(!buffer) {
        printf("Error: Memory allocation failed\n");

        fclose(file);
        return NULL;
    }

    fread(buffer, 1, length, file);

    buffer[length] = '\0';

    fclose(file);
    return buffer;
}*/
