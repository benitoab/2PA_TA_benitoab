#include "database.h"
#include <stdlib.h>
#include "character.h"



int callbackProffesion(void *proffdata, int argc,
                       char **argv, char **azcolname){
        
  Character_Stats* p_data = (Character_Stats*)proffdata;
  
  int i = atoi(argv[0])-1;
 
  (p_data+i)->hp = atoi(argv[1]);
  (p_data+i)->mana = atoi(argv[2]);
  (p_data+i)->physical_att = atoi(argv[3]);
  (p_data+i)->magic_att = atoi(argv[4]);
  (p_data+i)->armor = atoi(argv[5]);
  (p_data+i)->magic_resist = atoi(argv[6]);
  (p_data+i)->movement = atoi(argv[7]);
  (p_data+i)->mana_regen = atoi(argv[8]);
  (p_data+i)->crit_chance = atoi(argv[9]);
  return 0;
}