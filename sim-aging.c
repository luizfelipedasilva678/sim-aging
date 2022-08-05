#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct _FileInfos {
    int pages;
    int bits;
    int ticks;
} typedef FileInfos;

FileInfos getValuesFromFile(char * fileName) {
    FILE * file;
    char *result = (char*) (malloc(sizeof(char)));
    int pages, bits, ticks = 0;
    FileInfos infos;

    file = fopen(fileName, "r");

    if(file == NULL) {
        printf("Erro ao abrir arquivo \n");
        return infos;
    }

    while((fgets(result, 255, file)) != NULL) {
        if(sscanf(result, "%d %d", &bits, &pages) == 2) {
            infos.pages = pages;
            infos.bits = bits;
        } else {
            ticks++;
        }
    }

    infos.ticks = ticks;

    fclose(file);
    free(result);
    return infos;
}

void initCounter(unsigned int ** counter, int quantityString) {
    int i = 0;

    for(i; i < quantityString; i++) {
        counter[i][0] = 0;
    }
}

char * binaryUnit(int quantityBits, int number, int * n) {
    int i = 0, modDivision, stringIndex = 0;
    char * binaryString = (char *) ( malloc( sizeof(char) * quantityBits ) );

    for(i; i < quantityBits; i++) {
        modDivision = number % 2;
        number /= 2;

        n[i] = modDivision;
    }

    for(i = i - 1; i >= 0; i--) {
        stringIndex += snprintf(&binaryString[stringIndex], quantityBits, "%d", n[i]);
    }

    return binaryString;
}

int findMinor(unsigned int ** counter, int quantity) {
    int minor = counter[0][0];
    int pageMinor = 0;
    int i = 0;

    for(i; i < quantity; i++) {
        if(counter[i][0] < minor) {
            minor = counter[i][0];
            pageMinor = i;
        }
    }

    return pageMinor;
}

void writeFileResult(FileInfos infos, unsigned int ** counter, int minorPage) {
    int * binaryNumber = (int *) (malloc(sizeof(int[infos.bits])));
    int i = 0;
    FILE * file;

    file = fopen("resultados.txt", "w+");

    for(i; i < infos.pages; i++) {
        fprintf(file, "%s \n", binaryUnit(infos.bits, counter[i][0], binaryNumber));
    }

    free(binaryNumber);
    fclose(file);
}

void aging(char * str, unsigned int ** counter, FileInfos infos) {
    int i = 0;

    for(i; i < infos.pages; i++) {
        if(str[i] == '1') {
            counter[i][0] = counter[i][0] >> 1;
            counter[i][0] |= (1 << infos.bits - 1);
        } else {
            counter[i][0] = counter[i][0] >> 1;
        }
    }
}

int main(void) {
    int i, line = 0, page = 0;
    char * fileName = (char*)(malloc(sizeof(char)));
    char * result = (char*) (malloc(sizeof(char)));
    FILE * file;

    printf("Digite o nome do arquivo: ");
    scanf("%s", fileName);

    FileInfos infos = getValuesFromFile(fileName);
    unsigned int ** counter = (unsigned int **) (malloc(sizeof(unsigned int*[infos.pages])));

    for(i = 0; i < infos.pages; i++)
        counter[i] = (unsigned int *) malloc(sizeof(unsigned int[1]));

    initCounter(counter, infos.pages);
    file = fopen(fileName, "r");

    while((fgets(result, 255, file)) != NULL) {

        if(line >= 1) {
            aging(result, counter, infos);
        }

        line++;
    }

    int pageMinor = findMinor(counter, infos.pages);

    writeFileResult(infos, counter, pageMinor);

    for(i = 0; i < infos.pages; i++)
        free(counter[i]);
    free(counter);
    free(fileName);
    free(result);
    fclose(file);
    return 0;
}
