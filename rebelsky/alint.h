typedef struct ALint ALint
ALInt* uint_to_ali (unsigned int unit);
void ali_delete (ALInt* val);
char* ali_to_str (struct ALInt* val);
ALInt* ali_create_size (unsigned long length);
void ali_copy (ALInt* dest, ALINT* src);
ALInt* ali_add (ALInt *ali1, ALInt *ali2);
ALInt* ali_mult (ALInt *ali1, ALInt *ali2);
ALInt* ali_sub (ALInt *ali1, ALInt *ali2);
