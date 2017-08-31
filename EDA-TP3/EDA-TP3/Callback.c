#include "config.h"
#include <stdlib.h>
#include <string.h>

const char *lookup_table[] = {"width","height","mode","robots","EOTable"};

void init_CleanerParams (CleanerParams_t *pC){
	pC->width = NOT_SELECTED;
	pC->height= NOT_SELECTED;
	pC->mode  = NOT_SELECTED;
	pC->robots= NOT_SELECTED;
}

int check_Cleaner_mode (CleanerParams_t *pC){
	int ret;
	if((pC->width == NOT_SELECTED ) || (pC->height == NOT_SELECTED ) || (pC->mode == NOT_SELECTED ) || (pC->robots == NOT_SELECTED )){
		ret = INC_DATA;
	}
	else if((pC->width > MAX_WIDTH) || (pC->height > MAX_HEIGTH) || (pC->robots == NO_ROBOTS) || (pC->mode > MAX_MODES))
		ret = OUT_OF_RANGE;
	else
		ret = (pC->mode);
	return ret;
}
	

int parseCallback(char *key, char *value, void *userData) {

	CleanerParams_t *pC	= (CleanerParams_t *)userData;
	int i, ret = 0;

	if ((key != NULL)&&(value != NULL)) {

		i = 0;

		while ((lookup_table[i] != "EOTable") && (strcmp(lookup_table[i], key))) { // Looking for option
			i++;
		}
		if (lookup_table[i] == "EOTable") {
			ret = 0; // No option in table
		}
		else{ 
			if (!strcmp(key, "width")) {
				if (pC->width == NOT_SELECTED) {
					pC->width = atoi(value);
					ret = 1;
				}
				else {
					ret = 0; // Already selected width!
				}
			}
			else if (!strcmp(key, "height")) {
				if (pC->height == NOT_SELECTED) {
					pC->height = atoi(value);
					ret = 1;
				}
				else {
					ret = 0; // Already selected height!
				}
			}
			else if (!strcmp(key, "mode")) {
				if (pC->mode == NOT_SELECTED) {
					pC->mode = atoi(value);
					ret = 1;
				}
				else {
					ret = 0; // Already selected mode!
				}
			}
			else if ((!strcmp(key, "robots"))&&(atoi(value)>0)) {
				if (pC->robots == NOT_SELECTED) {
					pC->robots = atoi(value);
					ret = 1;
				}
				else {
					ret = 0; // Already selected robots!
				}
			}
		
		}
	}
	else {
		ret =0 ; // No Key
	}
	
	return ret;
}