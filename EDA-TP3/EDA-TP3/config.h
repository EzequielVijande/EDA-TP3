#ifndef CONFIG_H
#define CONFIG_H


#define NOT_SELECTED 9898
#define INC_DATA -1
#define OUT_OF_RANGE -2
#define MAX_WIDTH 70
#define MAX_HEIGTH 100
#define NO_ROBOTS 0
#define MAX_MODES 1
#define AUX_LEN 20
#define EOT '\0'


typedef struct {
	unsigned int width;
	unsigned int height;
	unsigned int mode;
	unsigned int robots;
}	CleanerParams_t;

void init_CleanerParams(CleanerParams_t *pC);
int check_Cleaner_mode(CleanerParams_t *pC);
int parseCallback(char *key, char *value, void *userData);


#endif  //CONFIG_H