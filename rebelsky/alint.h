typedef struct ALint ALint
ALInt* uint_to_ali (unsigned int uint);
ALInt* int_to_ali (int uint); 
void ali_delete (ALInt* val);
ALInt* ulong_to_ali (unsigned long uint);
ALInt* long_to_ali (long uint); 
ALInt* str_to_ali (char* num);
char* ali_to_str (struct ALInt* val);
ALInt* ali_create_size (unsigned long length);
void ali_copy (ALInt* dest, ALINT* src);
ALInt* ali_add (ALInt *ali1, ALInt *ali2);
ALInt* ali_mult (ALInt *ali1, ALInt *ali2);
ALInt* ali_sub (ALInt *ali1, ALInt *ali2);
