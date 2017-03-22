#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <errno.h>
#include <limits.h>

/* Base of the number system
   NOT TO BE ALTERED BY THE USER!
 */
const unsigned int BASE_N = 4;
#define BASE uintpow(10,BASE_N)

/*Buffer used when allocating space for strings.
  All strings made by this library are thus some multiple of this number.
  Can be altered by user.
  Larger = faster but taking up more space.
 */
const unsigned int ITERATED_BUFFER_SIZE = 100;

typedef struct intnode { 
  unsigned int x;
  struct intnode * next;
  struct intnode * prev;
} intnode;

typedef struct ALInt { 
  int sign;
  intnode * head;
  intnode * tail;
} ALInt;

const char IntCompList[11] = "-0123456789";
const char * digitList = IntCompList+1;

// Functions for use by user
void ali_free (ALInt *i);
ALInt * int2ali (int i);
int ali2int (ALInt *i);
ALInt * long2ali (long i);
long ali2long (ALInt *a);
ALInt * str2ali (char * s);
char * ali2str (ALInt *a);

ALInt * ali_add (ALInt *a, ALInt *b);
ALInt * ali_subtract (ALInt *a, ALInt *b);
ALInt * ali_multiply (ALInt *a, ALInt *b);
ALInt * ali_quotient (ALInt *a, ALInt *b);
ALInt * ali_remainder (ALInt *a, ALInt *b);

int compare(ALInt *a, ALInt *b);
ALInt * ali_copy(ALInt * x);

// Functions for library use
intnode * newnode(intnode * previous, unsigned int value);
ALInt * newALInt(int sign_of_value);
ALInt * removeLeadingZeros_ali(ALInt * i);
char * removeLeadingZeros_str(char * s);
int isInt_str(char * x);
int isDigit(char * x);
int isZeroChr(char * x);
int isZeroIntnode(intnode * node);
int isZero(ALInt * x);
char * strrev(char *str);
unsigned int uintpow(unsigned int base, unsigned int exp);
unsigned int getNthComponent(ALInt * x, unsigned int n);

//// Implementations
void ali_free(ALInt * num){
  intnode * node = num->head;
  intnode * afternode = NULL;
  while (node != NULL){
    afternode = node->next;
    free(node);
    node = afternode;
  }
  free(num);
  return;
}

ALInt * int2ali (int i){
  ALInt * out = NULL;
  if (i==0){
    out =  str2ali("0");
  }else{
    int numDigits = floor (log10 (abs (i))) + 1;
    char * tmp = malloc((sizeof(char)*numDigits)+1);
    sprintf(tmp, "%d",i);
    out = str2ali(tmp);
    free(tmp);
  }
  return out;
}

int ali2int (ALInt *i){
  errno = 0;
  char * s = ali2str(i);
  long l = strtol(s,NULL,10);
  if (errno){
    switch(errno){
      case EDOM:
        printf("domain error");
        break;
      case EILSEQ:
        printf("illegal sequence");    
        break;
      case ERANGE:
        printf("range error");
        break;
    }
    printf(": could not convert ALInt to int\n");
    l = 0;
  }else{
    if ((l < INT_MIN)||(l > INT_MAX)){
      printf("range error: could not convert ALInt %s to int\nreturning 0 instead\n", s);
      l = 0;
    }
  }
  free(s);
  return l;
}


ALInt * long2ali (long i){
  ALInt * out = NULL;
  if (i==0){
    out =  str2ali("0");
  }else{
    int numDigits = floor (log10 (abs (i))) + 1;
    char * tmp = malloc((sizeof(char)*numDigits)+1);
    sprintf(tmp, "%ld",i);
    out = str2ali(tmp);
    free(tmp);
  }
  return out;
}


long ali2long (ALInt *a){
  errno = 0;
  char * s = ali2str(a);
  long l = strtol(s,NULL,10);
  if (errno){
    switch(errno){
      case EDOM:
        printf("domain error");
        break;
      case EILSEQ:
        printf("illegal sequence");    
        break;
      case ERANGE:
        printf("range error");
        break;
    }
    printf(": could not convert ALInt %s to long\nreturning 0 instead\n",s);
    l = 0;
  }
  free(s);
  return l;
}

ALInt * str2ali (char * s){
  if (!isInt_str(s)){
    printf("Unable to convert string %s to ALInt: It must contain only digits and a minus sign in leftmost position\n", s);
    return NULL;
  }
  s = removeLeadingZeros_str(s);
  //printf("removed zeros %s\n",s);
  char * head = s;
  char * tail = s;
  int sig;
  while (tail[0] != '\0'){
    tail++;
  }
  tail--;
  if (tail < head){
    printf("Error converting string to ALInt: Argumant is not string of integer\nreturning 0 instead\n");
    return NULL;
  }
  if (head[0] == '-'){
    if (head[1] == '0'){
      sig = 0;
    }else{
      sig = -1;
    }
    head++;
  }else{
    if (head[1] == '0'){
      sig = 0;
    }else{
      sig = 1;
    }
  }
  ALInt * out = newALInt(sig);
  //printf("sig %d\n\n",sig);
  int isFirst = 1;
  intnode * current = NULL;
  char * bufferhead = NULL;
  while (tail >= head){
    if ((tail-3)<head){
      bufferhead = head;
    }else{
      bufferhead = tail-3;
    }
    if (isFirst){
      out->head = newnode(NULL, ((unsigned int) atoi(bufferhead)));
      current = out->head;
      //printf("%u\n",current->x);
      isFirst = 0;
    }else{
      current->next = newnode(current, ((unsigned int) atoi(bufferhead)));
      current = current->next;
      //printf("%u\n",current->x);
    }
    tail = tail-4;
    *bufferhead = '\0';
  }
  out->tail = current;
  //printf("Finished converting to ali\n");
  //printf("another line\n");
  //ALInt * tmp = removeLeadingZeros_ali(out);
  //ali_free(tmp);
  //printf("str2ali tmp %p",tmp);
  //if (isZero(tmp))
  //  tmp->sign = 0;
  return out;
}

char * ali2str(ALInt * x){
  int n = 1;
  int charsdone = 0;
  char * out = malloc(sizeof(char)*ITERATED_BUFFER_SIZE);
  char * new = NULL;
  char tmp[20];
  intnode * current = x->tail;
  if (x->sign < 0){
    out[0] = '-';
    charsdone = charsdone+1;
  }
  while (current != NULL){
    if ((charsdone+4) >= (ITERATED_BUFFER_SIZE*n)){
      out[ITERATED_BUFFER_SIZE*n] = '\0';
      n++;
      new = malloc(sizeof(char)*ITERATED_BUFFER_SIZE*n);
      strcpy(new,out);
      free(out);
      out = new;
  }
    if (current->x < 10){
      sprintf(tmp,"000%u",current->x);
    }else if (current->x < 100){
      sprintf(tmp,"00%u",current->x);
    }else if (current->x < 1000){
      sprintf(tmp,"0%u",current->x);
    }else{
      sprintf(tmp,"%u",current->x);
    }
    strcpy(out+charsdone,tmp);
    charsdone = charsdone + strlen(tmp);
    current = current->prev;
  }
  new = removeLeadingZeros_str(out);
  free(out);
  return new;
}

ALInt * ali_add (ALInt *a, ALInt *b){
  int ais0 = isZero(a);
  int bis0 = isZero(b);
  //printf("In add: ais0 %d, bis0 %d\n",ais0,bis0);
  if ((ais0)||(bis0)){
    if (ais0){
      if (bis0){
        ALInt * out = ali_copy(a);
        return out;
      }else{
        ALInt * out = ali_copy(b);
        return out;
      }
    }else{
      ALInt * out = ali_copy(a);
      return out;
    }
  }
  if ((a->sign < 0)||(b->sign < 0)){
    if ((a->sign < 0)&&(b->sign < 0)){
      //printf("Both neg\n");
      ALInt newa, newb;
      newa.sign = 1;
      newb.sign = 1;
      newa.head = a->head;
      newb.head = b->head;
      newa.tail = a->tail;
      newb.tail = b->tail;
      ALInt *out = ali_add(&newa, &newb);
      out->sign = -1;
      return out;
    }else if (a->sign <0){
      //printf("a neg\n");
      ALInt newa;
      newa.sign = 1;
      newa.head = a->head;
      newa.tail = a->tail;
      return ali_subtract(b,&newa);
    }else{
      //printf("b neg\n");
      ALInt newb;
      newb.sign = 1;
      newb.head = b->head;
      newb.tail = b->tail;
      return ali_subtract(a,&newb);
    }
  }else{
    //printf("both pos\n");
    intnode * a_current = a->head;
    intnode * b_current = b->head;
    intnode * outcurrent = NULL;
    unsigned int carry = 0;
    ALInt * out = newALInt(1);
    int isFirst = 1;
    unsigned int sum, aval, bval;
    while ((a_current != NULL)||(b_current != NULL)||(carry)){
      if (a_current == NULL){
        aval = 0;
      }else{
        aval = a_current->x;
      }
      if (b_current == NULL){
        bval = 0;
      }else{
        bval = b_current->x;
      }
      sum = aval+bval+carry;
      //printf("sum before reduction: %u\n",sum);
      if (sum >= BASE){
        //printf("carrying\n");
        sum = sum - BASE;
        carry = 1;
      }else{
        //printf("no carry\n");
        carry = 0;
      }
      //printf("sum %u\n",sum);
      if (isFirst){
        out->head = newnode(outcurrent,sum);
        outcurrent = out->head;
        isFirst = 0;
      }else{
        outcurrent->next = newnode(outcurrent,sum);
        outcurrent = outcurrent->next;
      }
      if (a_current != NULL){
        a_current = a_current->next;
      }
      if (b_current != NULL){
        b_current = b_current->next;
      }
    }
    out->tail = outcurrent;
    return out;
  }
}

ALInt * ali_subtract (ALInt *a, ALInt *b){
  int ais0 = isZero(a);
  int bis0 = isZero(b);
  if ((ais0)||(bis0)){
    if (ais0){
      if (bis0){
        ALInt * out = newALInt(0);
        out->head = newnode(NULL,0);
        out->tail = out->head;
        return out;
      }else{
        ALInt * out = ali_copy(b);
        if (out->sign == 1){
          out->sign = -1;
        }else if (out->sign == -1){
          out->sign = 1;
        }else{
          out->sign = 0;
        }
        return out;
      }
    }else{
      return ali_copy(a);
    }
  }
  if ((a->sign < 0)||(b->sign < 0)){
    if ((a->sign < 0)&&(b->sign < 0)){
      ALInt newa, newb;
      newa.sign = 1;
      newb.sign = 1;
      newa.head = a->head;
      newb.head = b->head;
      newa.tail = a->tail;
      newb.tail = b->tail;
      return ali_subtract(&newb, &newa);
    }else if (a->sign < 0){
      ALInt newa;
      newa.sign = 1;
      newa.head = a->head;
      newa.tail = a->tail;
      ALInt * out = ali_add(&newa, b);
      if (isZero(out)){
        out->sign = 0;
      }else{
        out->sign = -1;
      }
      return out;
    }else{
      ALInt newb;
      newb.sign = 1;
      newb.head = b->head;
      newb.tail = b->tail;
      return ali_add(a, &newb);
    }
  }else{
    int comp = compare(a,b);
    ALInt * out = NULL;
    switch (comp){
      case -1:
        out = ali_subtract(b,a);
        if (isZero(out)){
          out->sign = 0;
        }else{
          out->sign = -1;
        }
        return out;
      case 0:
        out = newALInt(0);
        out->head = newnode(NULL,0);
        out->tail = out->head;
        return out;
      case 1:
        out = newALInt(1);
        intnode * a_current = a->head;
        intnode * b_current = b->head;
        intnode * out_current;
        unsigned int borrowed = 0;
        unsigned int difference, bval;
        int isFirst = 1;
        while (a_current != NULL){
          if (b_current == NULL){
            bval = 0;
          }else{
            bval = b_current->x;
          }
          if (a_current->x < (bval + borrowed)){
            difference = (a_current->x + BASE) - (bval + borrowed);
            borrowed = 1;
          }else{
            difference = a_current->x - (bval + borrowed);
            borrowed = 0;
          }
          if (isFirst){
            out->head = newnode(NULL, difference);
            out_current = out->head;
            isFirst = 0;
          }else{
            out_current->next = newnode(out_current, difference);
            out_current = out_current->next;
          }
          a_current = a_current->next;
          if (b_current != NULL){
            b_current = b_current->next;
          }
        }
        out->tail = out_current;
        //ALInt * tmp = removeLeadingZeros_ali(out);
        if (isZero(out))
          out->sign = 0;
        //ali_free(out);
        return out;
    }
  }
}

ALInt * ali_multiply (ALInt *a, ALInt *b){
  unsigned int ahighestbase = 0;
  unsigned int bhighestbase = 0;
  intnode * acurrent = a->head;
  acurrent = acurrent->next;
  intnode * bcurrent = b->head;
  bcurrent = bcurrent->next;
  while ((acurrent != NULL)||(bcurrent != NULL)){
    if (acurrent != NULL){
      ahighestbase++;
      acurrent = acurrent->next;
    }
    if (bcurrent != NULL){
      bhighestbase++;
      bcurrent = bcurrent->next;
    }
  }
  printf("%u %u\n",ahighestbase,bhighestbase);
  ALInt * sum = newALInt(0);
  sum->head = newnode(NULL, 0);
  sum->tail = sum->head;
  ALInt * tmp1, * tmp2;
  long product;
  unsigned int i,j;
  for(i = 0; i <= ahighestbase; i++){
    for(j = 0; j <= bhighestbase; j++){
      product = getNthComponent(a,i)*getNthComponent(b,j);
      printf("get*get %ld\n",product);
      product = product*uintpow(BASE, (i+j));
      printf("after %lu\n",product);
      tmp1 = long2ali(product);
      printf("tmp1 %s\n",ali2str(tmp1));
      printf("sum %s\n",ali2str(sum));
      tmp2 = ali_add(sum, tmp1);
      printf("tmp2 %s\n",ali2str(tmp2));
      ali_free(tmp1);
      ali_free(sum);
      sum = tmp2;
      ali_free(tmp2);
    }
  }
  sum->sign = a->sign*b->sign;
  return sum;
}


ALInt * ali_quotient (ALInt *a, ALInt *b);


ALInt * ali_remainder (ALInt *a, ALInt *b);

int compare(ALInt *a, ALInt *b){
  //check the signs
  if (a->sign != b->sign){
    if (a->sign > b->sign){
      return 1;
    }else{
      return -1;
    }
  }else if (a->sign == 0){
    return 0;
  }
  //check how many nodes it takes to represent them
  intnode * a_current = a->head;
  intnode * b_current = b->head;
  while ((a_current != NULL)&&(b_current != NULL)){
    a_current = a_current->next;
    b_current = b_current->next;
  }
  if ((a_current != NULL)||(b_current != NULL)){
    if (a_current == NULL){
      return -1;
    }else{
      return 1;
    }
  }
  //numbers are same sign and represented by same number of nodes
  //check the actual numbers
  a_current = a->tail;
  b_current = b->tail;
  while (a_current != NULL){
    if (a_current->x != b_current->x){
      if (a_current->x > b_current->x){
        return 1;
      }else{
        return -1;
      }
    }
    a_current = a_current->prev;
    b_current = b_current->prev;
  }
  //there are no differences
  return 0;
}

ALInt * ali_copy(ALInt * x){
  ALInt * out = newALInt(x->sign);
  intnode * current = x->head;
  intnode * out_current = NULL;
  int isFirst = 1;
  while (current != NULL){
    if (isFirst){
      out->head = newnode(NULL, current->x);
      out_current = out->head;
      isFirst = 0;
    }else{
      out_current->next = newnode(out_current, current->x);
      out_current = out_current->next;
    }
    current = current->next;
  }
  out->tail = out_current;
  return out;
}

intnode * newnode(intnode * previous, unsigned int value){
  intnode * out = malloc(sizeof(intnode));
  out->x = value;
  out->next = NULL;
  out->prev = previous;
  return out;
}

ALInt * newALInt(int sign_of_value){
  //printf("New sign %d\n", sign_of_value);
  if ((sign_of_value == 1)||(sign_of_value == -1)||(sign_of_value == 0)){
    ALInt * out = malloc(sizeof(ALInt));
    out->sign = sign_of_value;
    out->head = NULL;
    out->tail = NULL;
    return out;
  }else{
    return NULL;
  }
}

ALInt * removeLeadingZeros_ali(ALInt * i){
  intnode * leading = i->tail;
  intnode * nextleading = NULL;
  while ((leading->prev != NULL)&&(isZeroIntnode(leading))){
    nextleading = leading->prev;
    nextleading->next = NULL;
    free(leading);
    leading = nextleading;
  }
  i->tail = leading;
  return i;
}

char * removeLeadingZeros_str(char * s){
  char * front = s;
  while ((front[1] != '\0')&&((front[0]=='0')||(front[0] == '-')))
    front++;
  char * end = front;
  if (front != s){
    while (end[0] != '\0')
      end++;
    if (*(end-1) == 'l'){
      *(end-1) = '\0';
    }
  }
  char * new = malloc(((end-front)+2)*sizeof(char));
  if (s[0] == '-'){
    new[0] = '-';
    strcpy(new+1,front);
  }else{
    strcpy(new, front);
  }
  return new;
}

int isIntComponent(char * x){
  if (strchr(IntCompList, x[0]) == NULL){
    return 0;
  }else{
    return 1;
  }
}

int isInt_str(char * x){
  int firstchar = 1;
  while (*x != '\0'){
    if (!isIntComponent(x)){
      return 0;
    }else{
      if (*x == '-'){
        if (firstchar){
          ;
        }else{
          return 0;
        }
      }
    }
    firstchar = 0;
    x = x+1;
  }
  return 1;
}

int isDigit(char * x){
  if (strchr(digitList, x[0]) == NULL){
    return 0;
  }else{
    return 1;
  }
}

int isZeroChr(char * x){
  if (x[0] == '0'){
    return 1;
  }else{
    return 0;
  }
}

int isZeroIntnode(intnode * node){
  if (node->x == 0){
    return 1;
  }else{
    return 0;
  }
}
unsigned int uintpow(unsigned int base, unsigned int exp){
  unsigned int x = 1;
  while (exp){
    x = x*base;
    exp--;
  }
  return x;
}

int isZero(ALInt * x){
  intnode * current = x->head;
  while (current != NULL){
    if (current->x != 0)
      return 0;
    current = current->next;
  }
  return 1;
}

 unsigned int getNthComponent(ALInt * x, unsigned int n){
   unsigned int p = 0;
   intnode * current = x->head;
   while ((current != NULL)&&(p <= n)){
     if (p == n){
       return current->x;
     }
     p++;
     current = current->next;
   }
   return 0;
 }
 
int main(){
  printf("INT_MAX = %d\nLINT_MAX = %ld\n",INT_MAX,LONG_MAX);
  char * x[] = {"0", "384392", "34958340965023472", "-329576232342", "-849275028347590387402", "-3482345723952382936459", "-00000010000000000000","00000010000000000000"};
  int i;
  printf("test BASE = %u\n",BASE);
  
  // conversion tests
/*
  for(i=0; i< 8; i++){
    printf("Input: %s\n",x[i]);
    ALInt * n = str2ali(x[i]);
    printf("To str: %s\n",ali2str(n));
    printf("To int: %d\n",ali2int(n));
    printf("To long: %ld\n",ali2long(n));
    int ix= ali2int(n);
    ALInt * m = int2ali(ix);
    printf("To str: %s\n",ali2str(m));
    printf("To long: %ld\n\n",ali2long(m));
    ali_free(n);
    ali_free(m);
  }
*/
  // operations tests
  printf("Ops Tests\n");
  for(i=0; i< 1; i++){
    printf("Input n: %s\n",x[i]);
    printf("Input m: %s\n",x[i+1]);
    ALInt * n = str2ali(x[i]);
    ALInt * m = str2ali(x[i+1]);
    //ALInt * a = ali_add(n,m);
    //printf("n+m=%s\n",ali2str(a));
    //ALInt * s = ali_subtract(n,m);
    //printf("n-m=%s\n",ali2str(s));
    ALInt * p = ali_multiply(n,m);
    printf("n*m=%s\n\n",ali2str(p));
    ali_free(n);
    ali_free(p);
    //ali_free(a);
    //ali_free(s);
  }
  return 0;
}
