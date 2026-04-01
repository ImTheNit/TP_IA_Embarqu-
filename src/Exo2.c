#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


#define ROWS 6
#define COLLUMN 8

#define TETA 0.5
#define EPSILON 0.01

#define MAX_ERROR 50
#define LEARNING_TRESHOLD 0.001

#define FILE_0 "../par/zero.txt"
#define FILE_1 "../par/un.txt"
#define DIR_TEST_FILE "../par/noise/"

#define OUTPUT_DIR "../dat/Exo2/Exo2_"
#define OUTPUT_FILE_COMMON_NOISE "common_noise_output.csv" 
#define OUTPUT_FILE_SPECIFIC_TRAIN "_train_output.csv"
#define OUTPUT_FILE_SPECIFIC_NOISE "_noise_output.csv"


//#define ERROR
//#define FILE_DEBUG
//#define DEBUG
//#define WEIGHT

int writeCSV(char * file, int valueA, double valueB){
    FILE *fp = fopen(file, "a");  
    if (!fp) {
        perror("Erreur d'ouverture du fichier");
        return -1;
    }

    fprintf(fp, "%d;%lf", valueA, valueB);

    fprintf(fp, "\n");
    fclose(fp);
    return 0;

}

void printArray(double array [ROWS*COLLUMN]){
    int i = 0;
    int j = 0;

    for (i; i < ROWS*COLLUMN; i++){
        fprintf(stdout,"%lf |",array[i]);
        if ( (i+1) % ROWS == 0){
            fprintf(stdout,"\n");
        }
    }
    fprintf(stdout,"\n");
}

void initWeight(double weight [ROWS*COLLUMN]){
    srand( time( NULL ) );
    int i = 0;

    for (i; i<ROWS*COLLUMN;i++){
        weight[i] = rand();
        weight[i] = weight[i] / RAND_MAX;
        weight[i] = weight[i] / (ROWS * COLLUMN);
    }
    #if defined DEBUG || defined WEIGHT
    printArray(weight);
    fprintf(stdout,"Fin de l'initialisation des poids\n");
    #endif
}

int loadArray(double array[ROWS*COLLUMN], char * file){
    #ifdef FILE_DEBUG
    fprintf(stdout,"Ouverture du fichier : %s\n",file);
    #endif

    FILE *fp = fopen(file, "r");

     if (!fp) { 
        perror("Impossible d'ouvrir le fichier"); 
        return EXIT_FAILURE; 
    } 
    int c = 0;
    int classe = 0;
    int i = 0;

    while ((c = fgetc(fp)) != EOF) { 
        if(c == '.'){
            array[i++] = 0;
        }else if (c == '*'){
            array[i++] = 1;
        }else if (c != '\n'){
            classe = c - '0';
        }
    }
    fclose(fp);

    return classe;
}

int loadArrayRandom(double array[ROWS*COLLUMN],int count){

    char * file ;
    if (count % 2 == 0){
        file = FILE_0;
    }else{
        file = FILE_1;
    }
    return loadArray(array,file);
}

double calculPotentielNeuroneSortie(double neurones[ROWS*COLLUMN], double weight[ROWS*COLLUMN]){
    int i = 0;
    double pot = 0;
    for(i; i < ROWS*COLLUMN; i ++){
        pot = pot + weight[i] * neurones[i];
    }
    return pot;
}

int reponseNeuroneSortie(double potentiel){
    if (potentiel < TETA){
        return 0;
    }else{
        return 1;
    }
}

double getError(int classe, double potentiel){
    return classe - potentiel;
}

void apprendre(double weight[ROWS*COLLUMN], double neurones[ROWS*COLLUMN], double error){
    #ifdef LEARN
    fprintf(stdout,"error");
    #endif
    int i =0;
    for (i; i< ROWS*COLLUMN; i ++){
        weight[i] = weight[i] + EPSILON * neurones[i] * error;
    }
}

int main(int argc, char *argv[]){
    
    if (argc != 1){
        fprintf(stdout, "usage : exo2 \n");
    }



    fprintf(stdout,"Début du programme\n");
    
    #ifdef DEBUG
    fprintf(stdout,"ROWS : %d\n",ROWS);
    fprintf(stdout,"COLLUMN : %d\n",COLLUMN);
    #endif

    int count = 0;
    double weightArray [ROWS*COLLUMN];
    double entryArray0 [ROWS*COLLUMN];
    double entryArray1 [ROWS*COLLUMN];
    double potentiels [2];
    double reponsesNeurone [2];
    double errors [2];

    //Training
    int classe = 0;
    double potentiel = 0;
    double reponseNeurone = 0;
    double error = 0;
    double entryArray [ROWS*COLLUMN];
    double totalError = 0;

    char filename_0_train[256];
    char filename_1_train[256];

    //Test with noise
    char filename_input[256];
 
    int expectedClasse = 0;
    int noise = 0;
    double entryArrayTest [ROWS*COLLUMN];
    double potentielTest = 0;
    double reponseNeuroneTest = 0;
    double errorTest = 0;
    int nbWrongByNoise = 0;

    int nbWrongByNoiseCommon [25] = {0};

    char filename_specific_noise[256];
    char filename_common_noise[256];


    initWeight(weightArray);


    snprintf(filename_0_train, 256, "%s0%s", OUTPUT_DIR, OUTPUT_FILE_SPECIFIC_TRAIN);
    snprintf(filename_1_train, 256, "%s1%s", OUTPUT_DIR, OUTPUT_FILE_SPECIFIC_TRAIN);
    snprintf(filename_common_noise, 256, "%s%s", OUTPUT_DIR, OUTPUT_FILE_COMMON_NOISE);
    
    FILE *fp = fopen("log", "w");  
    if (!fp) {
        perror("Erreur d'ouverture du fichier");
        return -1;
    }

    while(1){

        fprintf(stdout,"boucle n°%d\n",++count);
        classe = 0;
        potentiel = 0;
        reponseNeurone = 0;
        error = 0;
        double entryArray [ROWS*COLLUMN] = {0};
        totalError = 0;

        classe = loadArrayRandom(entryArray, count);

        #ifdef DEBUG
        printArray(entryArray);
        fprintf(stdout,"Classe lue : %d\n",classe);
        #endif

        potentiel = calculPotentielNeuroneSortie(entryArray, weightArray);
        #ifdef DEBUG
        fprintf(stdout,"Potentiel calculé : %lf\n",potentiel);
        #endif

        reponseNeurone = reponseNeuroneSortie(potentiel);
        #ifdef DEBUG
        fprintf(stdout,"Reponse calculée : %d\n",reponseNeurone);
        #endif

        error = getError(classe, potentiel);
        #ifdef ERROR
        fprintf(stdout, "classe : %d, potentiel : %lf, error : %lf\n", classe, potentiel, error);
        #endif
        
        #ifdef DEBUG
        fprintf(stdout,"Erreur : %lf\n",error);
        #endif
        apprendre(weightArray, entryArray, error);

        /* test */
        loadArray(entryArray0,FILE_0);
        loadArray(entryArray1,FILE_1);

        potentiels[0] = calculPotentielNeuroneSortie(entryArray0, weightArray);
        potentiels[1] = calculPotentielNeuroneSortie(entryArray1, weightArray);

        reponsesNeurone[0] = reponseNeuroneSortie(potentiels[0]);
        reponsesNeurone[1] = reponseNeuroneSortie(potentiels[1]);
        
        errors[0] = getError(0,potentiels[0]);
        errors[1] = getError(1,potentiels[1]);
         
        #if defined DEBUG || defined WEIGHT
        printArray(weightArray);
        #endif

        /*  */
        totalError = fabs(errors[0]) + fabs(errors[1]);
        #ifdef ERROR
        fprintf(stdout,"Erreurs : %lf %lf\n",errors[0],errors[1]);
        fprintf(stdout,"Erreurs : %lf %lf\n",fabs(errors[0]),fabs(errors[1]));
        fprintf(stdout,"totalError : %lf\n\n",totalError);
        #endif

        writeCSV(filename_0_train, count, errors[0]);
        writeCSV(filename_1_train, count, errors[1]);

        if (totalError <= LEARNING_TRESHOLD){
            break;
        }
    }
    fprintf(stdout,"Nombre de tours : %d\n",count);

    fprintf(stdout,"Test de notre modèle :\n");

    for (int i = 0; i < 2; i++){ 
        snprintf(filename_specific_noise, 256, "%s%d%s", OUTPUT_DIR, i, OUTPUT_FILE_SPECIFIC_NOISE);
        
        for (int j = 0; j < 25; j++){
            noise = 2*j + 1 ;

            nbWrongByNoise = 0;

            for (int k = 0 ; k < 50; k++){
                snprintf(filename_input, 256, DIR_TEST_FILE "%d_%d_percent_noise_nb%d.np",i,noise,k); 

                #ifdef DEBUGG
                    fprintf(stdout, "Fichier : %s\nFichier output specifique : %s\n\n", filename_input, filename_specific_noise);
                #endif

                expectedClasse = loadArray(entryArrayTest, filename_input);
                potentielTest = calculPotentielNeuroneSortie(entryArrayTest, weightArray);
                reponseNeuroneTest = reponseNeuroneSortie(potentielTest);
                errorTest = getError(expectedClasse, potentielTest);

                fprintf(fp,"%lf\n",errorTest);
                if (errorTest > TETA || errorTest < 0.0 - TETA ){   //Pas la bonne réponse
                    nbWrongByNoise++;
                    nbWrongByNoiseCommon[j]++;
                }
            }
            
            writeCSV(filename_specific_noise, noise , (MAX_ERROR - nbWrongByNoise ) * 2);
            if (i == 1 ){
                writeCSV(filename_common_noise, noise , MAX_ERROR *2 - nbWrongByNoiseCommon[j]);
            }
        }

    }

    
    fprintf(stdout,"Fin du programme\n");

    return 0;
}