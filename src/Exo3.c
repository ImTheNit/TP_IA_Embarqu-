#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>


#define ROWS 6
#define COLLUMN 8

#define TETA 0.5
#define EPSILON 0.01

#define MAX_ERROR 50
#define LEARNING_TRESHOLD 4.001

#define DIR_TEST_FILE "../par/noise/"

#define OUTPUT_DIR "../dat/Exo3/Exo3_"
#define OUTPUT_FILE_COMMON_NOISE "common_noise_output.csv" 
#define OUTPUT_FILE_SPECIFIC_TRAIN "_train_output.csv"
#define OUTPUT_FILE_SPECIFIC_NOISE "_noise_output.csv"

char* FILES[] = {
    "../par/zero.txt",
    "../par/un.txt",
    "../par/deux.txt",
    "../par/trois.txt",
    "../par/quatre.txt",
    "../par/cinq.txt",
    "../par/six.txt",
    "../par/sept.txt",
    "../par/huit.txt",
    "../par/neuf.txt"
};

char* FILES_OUT_TRAIN[] = {
    "../dat/Exo3/Exo3_0_train_output.csv",
    "../dat/Exo3/Exo3_1_train_output.csv",
    "../dat/Exo3/Exo3_2_train_output.csv",
    "../dat/Exo3/Exo3_3_train_output.csv",
    "../dat/Exo3/Exo3_4_train_output.csv",
    "../dat/Exo3/Exo3_5_train_output.csv",
    "../dat/Exo3/Exo3_6_train_output.csv",
    "../dat/Exo3/Exo3_7_train_output.csv",
    "../dat/Exo3/Exo3_8_train_output.csv",
    "../dat/Exo3/Exo3_9_train_output.csv"
};

//#define ERROR
//#define FILE_DEBUG
//#define DEBUG
//#define WEIGHT
//#define LOG

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

void initWeight(double weight [10][ROWS*COLLUMN]){
    srand( time( NULL ) );
    int i = 0;
    int j = 0;
    
    for (i = 0 ; i <= 9 ; i++){
        for (j = 0 ; j<ROWS*COLLUMN;j++){
            weight[i][j] = rand();
            weight[i][j] = weight[i][j] / RAND_MAX;
            weight[i][j] = weight[i][j] / (ROWS * COLLUMN);
        }      
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
    return loadArray(array,FILES[count % 10]);
}

double calculPotentielNeuroneSortie(double neurones[ROWS*COLLUMN], double weight[ROWS*COLLUMN]){
    int i = 0;
    double pot = 0.0;
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

double getError(int classe, double potentiel, int index){
    int target = (index == classe) ? 1 : 0;
    return target - potentiel;
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
        fprintf(stdout, "usage : exo3 \n");
    }

    


    fprintf(stdout,"Début du programme\n");
    
    #ifdef DEBUG
    fprintf(stdout,"ROWS : %d\n",ROWS);
    fprintf(stdout,"COLLUMN : %d\n",COLLUMN);
    #endif

    int count = 0;
    int index = 0;
    double weightArray [10][ROWS*COLLUMN];
    double entryArray_test [10][ROWS*COLLUMN];
    double potentiels [10];
    double reponsesNeurone [10];
    double errors [10];

    //Training
    int classe = 0;
    double potentiel = 0.0;
    double reponseNeurone = 0.0;
    double error = 0.0;
    double entryArray [ROWS*COLLUMN];
    double totalError = 0.0;

    //Test with noise
    char filename_input[256];
 
    int expectedClasse = 0;
    int noise = 0;
    double entryArrayTest [ROWS*COLLUMN];
    double potentielTest [10];
    double reponseNeuroneTest = 0.0;
    double errorTest = 0.0;
    int nbWrongByNoise = 0.0;

    int nbWrongByNoiseCommon [25] = {0};

    char filename_specific_noise[256];
    char filename_common_noise[256];

    #ifdef LOG
    FILE *log = fopen("log", "w");  
    if (!log) {
        perror("Erreur d'ouverture du fichier");
        return -1;
    }
    #endif

    initWeight(weightArray);

    snprintf(filename_common_noise, 256, "%s%s", OUTPUT_DIR, OUTPUT_FILE_COMMON_NOISE);
    
    

    while(1){

        if (count == 150000){
            break;
        }

        fprintf(stdout,"boucle n°%d\n",count+1);
        classe = 0;
        potentiel = 0.0;
        reponseNeurone = 0.0;
        error = 0.0;
        double entryArray [ROWS*COLLUMN] = {0};
        totalError = 0.0;

        classe = loadArrayRandom(entryArray, count);

        #ifdef DEBUG
        printArray(entryArray);
        fprintf(stdout,"Classe lue : %d\n",classe);
        #endif

        for (int i = 0; i <= 9; i++){
            potentiel = calculPotentielNeuroneSortie(entryArray, weightArray[i]);
            #ifdef DEBUG
            fprintf(stdout,"Potentiel calculé : %lf\n",potentiel);
            #endif

            reponseNeurone = reponseNeuroneSortie(potentiel);
            #ifdef DEBUG
            fprintf(stdout,"Reponse calculée : %d\n",reponseNeurone);
            #endif

            error = getError(classe, potentiel,i);
            #ifdef ERROR
            fprintf(stdout, "classe : %d, potentiel : %lf, error : %lf\n", classe, potentiel, error);
            #endif
            
            #ifdef DEBUG
            fprintf(stdout,"Erreur : %lf\n",error);
            #endif
            apprendre(weightArray[i], entryArray, error);
        }
        

        /* test */


        for (index = 0; index <= 9 ; index++){
            loadArray(entryArray_test[index],FILES[index]);
            for (int index2 = 0; index2 <=9; index2++){
                
                potentiels[index2] = calculPotentielNeuroneSortie(entryArray_test[index], weightArray[index2]);
                errors[index2] = getError(index, potentiels[index2],index2); 

                totalError += fabs(errors[index2]);
                #ifdef LOG
                    fprintf(log,"totalError en calcul: %lf\n\n",totalError);
                #endif
                
            }
            writeCSV(FILES_OUT_TRAIN[index], count, errors[index]);
        }
        #ifdef LOG
            fprintf(log,"Erreurs : %lf %lf %lf %lf %lf %lf %lf %lf %lf %lf\n",fabs(errors[0]),fabs(errors[1]),fabs(errors[2]),fabs(errors[3]),fabs(errors[4]),fabs(errors[5]),fabs(errors[6]),fabs(errors[7]),fabs(errors[8]),fabs(errors[9]));
            fprintf(log,"totalError : %lf\n\n",totalError);
        #endif

        if (totalError <= LEARNING_TRESHOLD){
            break;
        }
        count++;
    }
    fprintf(stdout,"Nombre de tours : %d\n",count);

    fprintf(stdout,"Test de notre modèle :\n");
    
    for (int i = 0; i < 10; i++){ 
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

                for (int c = 0; c < 10; c++) {
                    potentielTest[c] = calculPotentielNeuroneSortie(entryArrayTest, weightArray[c]);
                }

                int predictedClasse = 0;
                double bestPot = potentielTest[0];

                for (int c = 1; c < 10; c++) {
                    if (potentielTest[c] > bestPot) {
                        bestPot = potentielTest[c];
                        predictedClasse = c;
                    }
                }

                if (predictedClasse != expectedClasse) {
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