#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include <sys/types.h>

const char* noms_chiffres[] = {"zero", "un", "deux", "trois", "quatre", "cinq", "six", "sept", "huit", "neuf"};
//const char* noms_chiffres[] = {"zero", "un"};


// Motifs 6x8 pour les chiffres 0 à 9
int motifs[10][48] = {
    // 0
    {0,0,0,0,0,0, 0,1,1,1,1,0, 0,1,0,0,1,0, 0,1,0,0,1,0, 0,1,0,0,1,0, 0,1,0,0,1,0, 0,1,1,1,1,0, 0,0,0,0,0,0}, 
    // 1
    {0,0,0,0,0,0, 0,0,0,1,0,0, 0,0,1,1,0,0, 0,1,0,1,0,0, 0,0,0,1,0,0, 0,0,0,1,0,0, 0,1,1,1,1,0, 0,0,0,0,0,0}, 
    // 2
    {0,0,0,0,0,0, 0,1,1,1,1,0, 0,0,0,0,1,0, 0,1,1,1,1,0, 0,1,0,0,0,0, 0,1,0,0,0,0, 0,1,1,1,1,0, 0,0,0,0,0,0}, 
    // 3
    {0,0,0,0,0,0, 0,1,1,1,1,0, 0,0,0,0,1,0, 0,0,1,1,1,0, 0,0,0,0,1,0, 0,0,0,0,1,0, 0,1,1,1,1,0, 0,0,0,0,0,0}, 
    // 4
    {0,0,0,0,0,0, 0,1,0,0,1,0, 0,1,0,0,1,0, 0,1,1,1,1,0, 0,0,0,0,1,0, 0,0,0,0,1,0, 0,0,0,0,1,0, 0,0,0,0,0,0}, 
    // 5
    {0,0,0,0,0,0, 0,1,1,1,1,0, 0,1,0,0,0,0, 0,1,1,1,1,0, 0,0,0,0,1,0, 0,0,0,0,1,0, 0,1,1,1,1,0, 0,0,0,0,0,0}, 
    // 6
    {0,0,0,0,0,0, 0,1,1,1,1,0, 0,1,0,0,0,0, 0,1,1,1,1,0, 0,1,0,0,1,0, 0,1,0,0,1,0, 0,1,1,1,1,0, 0,0,0,0,0,0}, 
    // 7
    {0,0,0,0,0,0, 0,1,1,1,1,0, 0,0,0,0,1,0, 0,0,0,1,0,0, 0,0,1,0,0,0, 0,0,1,0,0,0, 0,0,1,0,0,0, 0,0,0,0,0,0}, 
    // 8
    {0,0,0,0,0,0, 0,1,1,1,1,0, 0,1,0,0,1,0, 0,1,1,1,1,0, 0,1,0,0,1,0, 0,1,0,0,1,0, 0,1,1,1,1,0, 0,0,0,0,0,0}, 
    // 9
    {0,0,0,0,0,0, 0,1,1,1,1,0, 0,1,0,0,1,0, 0,1,1,1,1,0, 0,0,0,0,1,0, 0,0,0,0,1,0, 0,1,1,1,1,0, 0,0,0,0,0,0}
};

void save(int* tab, int noise_level, int digit, int file_number) {
    char path[256];
    FILE* fd;
    
    sprintf(path, "par/noise/%d_%d_percent_noise_nb%d.np", 
            digit, noise_level, file_number);
    
    fd = fopen(path, "w");
    if (fd == NULL) return;

    for (int i = 0; i < 48; i++) {
        if (i % 6 == 0 && i != 0) fprintf(fd, "\n");
        if (tab[i] == 0) fprintf(fd, ".");
        else fprintf(fd, "*");
    }
    fprintf(fd, "\n%d\n", digit); 
    fclose(fd);
}

void generate_noisy_pattern(int* source, int noise_level, int digit, int file_number) {
    int buff[48];
    int nb_pixels_to_flip = (48 * noise_level) / 100;
    int memory_flipped[48] = {0};

    for (int i = 0; i < 48; i++) buff[i] = source[i];

    for (int i = 0; i < nb_pixels_to_flip; i++) {
        int index_to_flip;
        do {
            index_to_flip = rand() % 48;
        } while (memory_flipped[index_to_flip] == 1);
        
        memory_flipped[index_to_flip] = 1;
        buff[index_to_flip] = 1 - buff[index_to_flip];
    }
    save(buff, noise_level, digit, file_number);
}

int main() {
    srand(time(NULL));



    for (int d = 0; d <= 9; d++) {

        printf("Génération des patterns pour le chiffre : %d\n", d);

        // Niveaux de bruit : 1, 3, 5 ... 49% (comme dans votre ls)
        for (int noise = 1; noise < 50; noise += 2) { 
            // 50 fichiers par niveau de bruit (nb0 à nb49)
            for (int sample = 0; sample < 50; sample++) {
                generate_noisy_pattern(motifs[d], noise, d, sample);
            }
        }
    }

    printf("\nOpération terminée avec succès dans le dossier data/.\n");
    return 0;
}
