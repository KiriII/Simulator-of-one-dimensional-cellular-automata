#include <stdio.h>
#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <memory.h>

int n = 0;
int rules[8];
int * readFirst();
int * readtf(char * filename , int space_separated);
int * readpbmf(char * filename);

int main(void)
{
  int i , j;
  readRules();
  int * fist = readFirst();
  int array[n][n]; // объявляем массив
  //printf("%d" , n);
  for ( i = 0; i < 8; i++ ) {
    printf("%d" , rules[i]);
  }
  printf( "\n" );

  for ( i = 0; i < n; i++ ) {
    printf("%d" , fist[i]);
  }
  printf( "\n" );

  firstRow(fist , array);
  for ( i = 1 ; i < n ; i++){
    evolve(array , i);
  }


  for ( i = 0; i < n; i++ ) {
    for ( j = 0; j < n; j++ )
    {
        printf( "[%d][%d]=%d ", i, j, array[i][j] );
    }
    printf( "\n" );
  }
  getchar();
  writepbmf("output.pbm" , n , array);
}

void firstRow (int first[n] , int map[n][n])
{
    int i;
    for (int i = 0 ; i < n ; i++){
        map[0][i] = first[i];
    }
}

void evolve (int map[n][n] , int row){
    int i , j , octal;
    for (int i = 0 ; i < n ; i ++){
            octal = getParents(map , row , i);
            if (octal == 0) map[row][i] = rules[7];
            if (octal == 1) map[row][i] = rules[6];
            if (octal == 10) map[row][i] = rules[5];
            if (octal == 11) map[row][i] = rules[4];
            if (octal == 100) map[row][i] = rules[3];
            if (octal == 101) map[row][i] = rules[2];
            if (octal == 110) map[row][i] = rules[1];
            if (octal == 111) map[row][i] = rules[0];
            //printf("%d%s" , getParents(map , row , i) , " ");
    }
    //printf( "\n" );
};

int getParents(int map[n][n] , int row  , int collumn){
    if ((row == 0) || (row >= n)) {
        printf("Error in parent searching");
        return 0;
    }
    int i;
    if (collumn == 0)
        i = map[row - 1][n - 1] * 100 + map[row - 1][0] * 10 + map[row - 1][1];
    else if (collumn == n - 1)
        i = map[row - 1][collumn - 1] * 100 + map[row - 1][collumn] * 10 + map[row - 1][0];
    else i = map[row - 1][collumn - 1] * 100 + map[row - 1][collumn] * 10 + map[row - 1][collumn + 1];
    //printf(i);
    return i;
}

int toOctal(int octal[8] , int dec){
    if ((dec < 0) || (dec > 255)) return ;
    int i ;
    int result[8];
    for (i = 7 ; i > 0; i --){
        //printf("%d" , dec % 2);
        result[i] = dec % 2;
        dec = dec / 2;

    }
    result[0] = dec;
    for (i = 0; i < 8; i++){
       octal[i] = result[i];
    }
}

void readRules(){
    printf("Insert rules (1 - number , 2 - in standart order(1 0 1 0 1 0 1 0) , 3 - chaoticly(1 0 1 1))" );
    printf( "\n" );
    int first , i;
    scanf("%d" , &first);
    while ((first < 1) || (first > 3)){
        printf("Just 1, 2 or 3");
        printf( "\n" );
        scanf("%d" , &first);
    }
    if (first == 1){
        int dec;
        scanf("%d" , &dec);
        toOctal(rules , dec);
    }
    if (first == 2){
        int i;
        int two[8];
        int s;
        for (i = 0; i < 8 ; i++){
           scanf("%d" , &s);
           while ((s != 1) && (s != 0)){
               printf("Just 1 and 0" );
               printf( "\n" );
               scanf("%d" , &s);
           }
           two[i] = s;
        }
        for (i = 0; i < 8; i++){
           rules[i] = two[i];
        }
    }
    if (first == 3){
        int third[8];
        bool compl = false;
        int t , s , i;
        int rule[4];
        for (i = 0 ; i < 8 ; i++){
           third[i] = -1;
        }
        while (compl == false){
            for (s = 0 ; s < 4; s ++){
                scanf ("%d" , &t);
                rule[s] = t;
            }
            for (s = 0 ; s < 4; s ++){
                printf("%d" , rule[s]);
            }
           while ((( rule[0] != 0) && ( rule[0] != 1)) || (( rule[1] != 0) && ( rule[1] != 1)) ||
                  (( rule[2] != 0) && ( rule[2] != 1)) || (( rule[3] != 0) && ( rule[3] != 1))) {
                printf("Just 1 and 0" );
                printf( "\n" );
                for (s = 0 ; s < 4; s ++){
                scanf ("%d" , &t);
                rule[s] = t;
                }
           }
           if ((rule[0] == 0) && (rule[1] == 0) && (rule[2] == 0)) third[7] = rule[3];
           if ((rule[0] == 0) && (rule[1] == 0) && (rule[2] == 1)) third[6] = rule[3];
           if ((rule[0] == 0) && (rule[1] == 1) && (rule[2] == 0)) third[5] = rule[3];
           if ((rule[0] == 0) && (rule[1] == 1) && (rule[2] == 1)) third[4] = rule[3];
           if ((rule[0] == 1) && (rule[1] == 0) && (rule[2] == 0)) third[3] = rule[3];
           if ((rule[0] == 1) && (rule[1] == 0) && (rule[2] == 1)) third[2] = rule[3];
           if ((rule[0] == 1) && (rule[1] == 1) && (rule[2] == 0)) third[1] = rule[3];
           if ((rule[0] == 1) && (rule[1] == 1) && (rule[2] == 1)) third[0] = rule[3];
           printf( "\n" );
           compl = true;
           for (s = 0; s < 8; s++){
             if (third[s] == -1) compl = false;
           }

         }
         for (i = 0; i < 8; i++){
           rules[i] = third[i];
        }
    }
}

int * readFirst(){
   printf("Insert first row (1 - console , 2 - text file , 3 - PBM image )" );
    printf( "\n" );
    int first , i;
    size_t length = 0;
    int * arr = malloc(sizeof(int) * length);
    scanf("%d" , &first);
    while ((first < 1) || (first > 3)){
        printf("Just 1, 2 or 3");
        printf( "\n" );
        scanf("%d" , &first);
    }
    if (first == 1){
        printf("2 to stop");
        printf( "\n" );
        int s , i , c;
        while (s != 2){
           scanf("%d" , &s);
           while ((s != 1) && (s != 0) && (s != 2)){
               printf("Just 1 and 0" );
               printf( "\n" );
               scanf("%d" , &s);
           }
           if (s != 2){
           arr = realloc(arr, sizeof(int) * ++length);
           arr[length - 1] = s;
           }
        }
        n = (int)length;
        return arr;
    }
    if (first == 2){
        printf("input file name is ");
        printf( "\n" );
        char cha[20];
        scanf("%20s" , cha);
        return readtf( cha , 1);
    }
    if (first == 3){
        printf("input PBM-file name is ");
        printf( "\n" );
        char cha[20];
        scanf("%20s" , cha);
        return readpbmf( cha );
    }
}

int * readtf(char * filename, int space_separated) {
FILE * input_file = fopen(filename, "r"); //Открыли файл для чтения
int c;
size_t length = 0;
//Если не использовать malloc, а просто локальную переменную, то данные могут перезаписаться после завершения ф-ии
int * arr = malloc(sizeof(int) * length);
while ((c = fgetc(input_file)) != EOF) {
arr = realloc(arr, sizeof(int) * ++length); //Добавляем дополнительный элемент в массив
arr[length - 1] = ((char) c - '0') % 2; //Записываем число
if (space_separated)
fgetc(input_file); //Читаем еще раз, чтобы пропустить пробел
}
fclose(input_file);
n = (int)length;
return arr;
}

char * readln(FILE * file) {
char * line = malloc(sizeof(char) * 1);
int length = 1;
int c;
while ((c = fgetc(file)) != EOF) {
if (c == '\n' || c == '\r') {
if (c == '\r')
fgetc(file);
break;
}
line = realloc(line, sizeof(char) * ++length);
line[length - 2] = (char)c;
}
line[length - 1] = '\0';
return line;
}

int * readpbmf(char * filename) {
FILE * input = fopen(filename, "r");
char * line = readln(input);
if (line[0] != 'P' || (line [1] != '1' && line [2] != '4') && line[3] != '\0')
return 0;
line = readln(input);
//Пропускаем строки с комментариями
while (line[0] == '#')
line = readln(input);
size_t width = (size_t)strtol(line, &line, 10); //Читаем первое число
line++; // пропускаем пробел
size_t height = (size_t)strtol(line, &line, 10); //Читаем второе число
if (width != height)
return 0;
//Пропускаем все строки, кроме последней
for (int i = 0; i < width; i++)
line = readln(input);
int * arr = malloc(sizeof(int) * width);
for (int i = 0; i < width; i++) {
arr[i] = (*line - '0') % 2;
line += 2;
}
n = (int)width;
fclose(input);
return arr;
}

void writepbmf(char * filename, int size, int data[size][size]) {
FILE * output = fopen(filename, "w+");
fwrite("P1\r\n", sizeof(char), 4, output);
int n = size;
int length = 0;
char s[11];
while (n > 0) {
s[length++] = (char)((n % 10) + '0');
n /= 10;
}
char num[length];
for (int i = 0; i < length; i++) {
num[i] = s[length - i - 1];
}
fwrite(num, (size_t)length, 1, output);
fputc(' ', output);
fwrite(num, (size_t)length, 1, output);
fwrite("\r\n", 1, 2, output);
for (int i = 0; i < size; i++) {
for (int j = 0; j < size; j++) {
fputc(data[i][j] + '0', output);
fputc(' ', output);
}
if (i != size - 1)
fwrite("\r\n", 1, 2, output);
}
fclose(output);
}
