#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "relationMethods.h"


relationsInfo* getRelationsData(FILE* file, int* num_of_initRelations) {
    char *line = NULL;
	  size_t len = 0;
    int read;

    // If file is not provided as an argument, get lines from stdin
  	if (file == NULL){
    		printf("Please input init files (End input with the word 'Done'):\n");
    		file = stdin;
  	}
    stringNode *filenamesList = createNameList();

    while ((read = getline(&line, &len, file)) != -1) {
        // Get the binary files, as each of them is a relation
        char* lineStr = strtok(line,"\n");
        if (lineStr == NULL) continue;
        if (strcmp(lineStr, "Done") == 0) break;
        if (insertIntoNameList(filenamesList, lineStr) == 0) return NULL;
        (*num_of_initRelations)++;
    }

    relationsInfo *initRelations;
    initRelations = malloc(*num_of_initRelations * sizeof(relationsInfo));

    for (int i = 0; i < *num_of_initRelations; i++) {
        // Read all relations and their data
        char* tempStr = findNameByIndex(filenamesList, i);
        initRelations[i].relName = malloc((strlen(tempStr)+1)*sizeof(char));
        strcpy(initRelations[i].relName, tempStr);

        // Open the relation binary file
        FILE* relFile = NULL;
    	  relFile = fopen(initRelations[i].relName, "rb");
        // Read the number of rows and columns of current relation
        fread(&initRelations[i].num_of_rows, sizeof(uint64_t), 1, relFile);
        //fseek(relFile, sizeof(uint64_t), SEEK_SET);
        fread(&initRelations[i].num_of_columns, sizeof(uint64_t), 1, relFile);
        if ((initRelations[i].MDCols = malloc(initRelations[i].num_of_columns * sizeof(metadataCol))) == NULL) {
            //critical error, not enough memory for metadata
            return NULL;
        }

        // Fill in the arrays with the values from relation File
        initRelations[i].Rarray = malloc(initRelations[i].num_of_columns * sizeof(uint64_t*));
        for (int j = 0; j < initRelations[i].num_of_columns; j++) {
            initRelations[i].Rarray[j] = malloc(initRelations[i].num_of_rows * sizeof(uint64_t));
            //long int min, max, discrete_values, y;
            for (int k = 0; k < initRelations[i].num_of_rows; k++) {
                fread(&initRelations[i].Rarray[j][k], sizeof(uint64_t), 1, relFile);

                //find min,max and discrete_values
                /*if (!k) { //first element of current column
                  min = initRelations[i].Rarray[j][k];
                  max = min;
                  discrete_values = 1;
                }
                else { //every other element of current column
                  if (min > initRelations[i].Rarray[j][k]) {
                    min = initRelations[i].Rarray[j][k];
                  }
                  else if (max < initRelations[i].Rarray[j][k]) {
                    max = initRelations[i].Rarray[j][k];
                  }

                  //calculate discrete_values
                  for (y = 0; y < k; y++) {
                    if (initRelations[i].Rarray[j][k] == initRelations[i].Rarray[j][y]) {
                      break;
                    }
                  }
                  if (k == y) {
                    discrete_values++;
                  }
              }*/
            }
            /*initRelations[i].MDCols[j].num_of_rows = initRelations[i].num_of_rows;
            initRelations[i].MDCols[j].min = (uint32_t)min;
            initRelations[i].MDCols[j].max = (uint32_t)max;
            initRelations[i].MDCols[j].discrete_values = (uint32_t)discrete_values;*/
        }
        fclose(relFile);
    }

    // Free dynamically allocated structures
    deleteNameList(&filenamesList);
  	if (line) free(line);
  	if (file != NULL && file != stdin) fclose(file);            // Close file

    return initRelations;
}


// Delete relations array
void deleteRelationsData(relationsInfo* initRelations, int* num_of_initRelations) {
    if(initRelations == NULL || num_of_initRelations <= 0){
      return;
    } 
    for (int i = 0; i < *num_of_initRelations; i++) {
        for (int j = 0; j < initRelations[i].num_of_columns; j++) {
            free(initRelations[i].Rarray[j]);
        }
        free(initRelations[i].relName);
        free(initRelations[i].Rarray);
        free(initRelations[i].MDCols);
    }
    free(initRelations);
    *num_of_initRelations = -1;
    initRelations = NULL;
}


// Create a list to store the names of data files
stringNode* createNameList() {
  	stringNode* nameList;
  	if ((nameList = malloc(sizeof(stringNode))) == NULL) return NULL;
  	nameList->isEmptyList = 1;
  	nameList->next = NULL;
    nameList->name = NULL;
  	return nameList;
}

// Insert strings into the list (helps while reading files)
int insertIntoNameList(stringNode* nameList, char* name) {
    if(name == NULL || nameList == NULL){
      return 0;
    }
  	stringNode *currentNode, *newNode;
  	if (nameList->isEmptyList == 1){
        nameList->name = malloc((strlen(name)+1)*sizeof(char));
    		strcpy(nameList->name, name);
    		nameList->isEmptyList = 0;
    		return 1;
  	}
  	currentNode = nameList;
  	while (currentNode->next != NULL) {
  		  currentNode = currentNode->next;
  	}
  	if ((newNode = malloc(sizeof(stringNode))) == NULL) return 0;
    newNode->name = malloc((strlen(name)+1)*sizeof(char));
  	strcpy(newNode->name, name);
  	newNode->next = NULL;
  	currentNode->next = newNode;
  	return 1;
}

// Look for the "index" node and retrieve the name value
char* findNameByIndex(stringNode* nameList, int index) {
    if(nameList == NULL || index < 0){
      return NULL;
    }
  	stringNode *currentNode = nameList;
  	int currentIndex = 0;
  	do {
    		if (currentIndex == index) {
    			return currentNode->name;
    		}
    		currentNode = currentNode->next;
    		currentIndex++;
  	} while (currentNode != NULL);
  	return NULL;
}

// Delete above list
void deleteNameList(stringNode** nameList) {
  	stringNode *currentNode = *nameList;
    stringNode *tempNode;
  	while (currentNode != NULL){
  		tempNode = currentNode;
  		currentNode = currentNode->next;
      free(tempNode->name);
  		free(tempNode);
  	}
    *nameList = NULL;
}
