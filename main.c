// --------------------------------------------------------------------------------
// AUTHOR: Joshua Wade West
// FILENAME: HW11.cpp
// SPECIFICATION: used to sort through a list of aircrafts via multiple means
// FOR: CS 1412 Lab- Section 502

#include <stdio.h>
#include <string.h>

#define STR_SIZ 25//max name length

#define DESCR_SIZ 80// max description length

#define MIN 1 // minumum value

#define MAX 9999 // maximum value


//structure for plane values
typedef struct {

char name[STR_SIZ]; // name of plane

int speed;// plane speed

double wingspan;// plane wingspan

double length;// plane lenth

char type;// plane type(M/C)

char description[DESCR_SIZ];//plane description

}aircraft_t;



//struct for searching paramters
typedef struct {

char low_name[STR_SIZ];//lowest name search
char high_name[STR_SIZ];//highest name search

int low_speed;//lowest speed
int high_speed;//highest speed

int low_wingspan;//loest wingspan
int high_wingspan;//highest wingspan

int low_length;//smallest length
int high_length;//highest length

char low_Model;//lowest Model
char high_Model;//Highest Model

}search_params_t;




char choose();// function prototype for list and choosing

search_params_t get_params();//function prototype to search 

int match();//check if the parameters match any plane(s)

void show();//prints the match

void convert();// convert text 2 binary

int main(void) {

char air_file[STR_SIZ]; //will become the .txt
char air_file2[STR_SIZ];//will copy air_file for .bin
aircraft_t aircraft;//struct call

search_params_t param;//gets parrameters

int no_matches=0;//used for output
int status=1;//used for the output

FILE *air_binaryp; //creates a file pointer


//user inputes file name
printf("Enter the name of the File with the Plane Data\n(Just Enter File name. EX; enter text NOT text.bin/.txt): ");

scanf("%s", air_file);//inputs the file name into variable
strcpy(air_file2,air_file);// does the same as above
printf("\n\n");

convert(air_file);//function call to convert txt to bin

//opens air_file2 as a bin and copies it into air_binaryp
air_binaryp = fopen(strcat(air_file2,".bin"), "rb");

//makes sure that bin file exists
if(air_binaryp == NULL ){printf("\nNO BINATY FILE FOUND\n");}

else{

param = get_params();//gets the parameters

printf("\nAircraft Name Speed Wingspan Length Type Descritption");//outputs the list of variables for the plane(s)

while(status>0){//loops aslong as status is greater than 0

if(match(aircraft, param)){//function call. if aircraft info == parameters

show(aircraft);//outputs plane info

no_matches++;//makes matches > 0

}

status=fread(&aircraft, sizeof (aircraft_t), 1, air_binaryp);//makes status == to the number of values in the file

}}

if (no_matches==0)//if loop above finds no match

printf("\nNo Planes Fit Into Parameters \n");

fclose(air_binaryp);//closes the *File

return(0);

}


char choose(search_params_t params){//Function for List and choosing an option
char choice;//variable for choice
printf("Enter a Letter to alter a parameter\n ");

printf("Enter 'E', to Find Planes witin Parameters.\n\n");

printf("[a] Lower bound for name\t\t %s\n", params.low_name);//outputs the names lower bound
printf("[b] Higher bound for name\t\t %s\n", params.high_name);//outputs the names higher bound
printf("[c] Lower bound for speed\t\t %d\n", params.low_speed);//outputs the speeds lower bound
printf("[d] Higher bound for speed\t\t %d\n", params.high_speed);//outputs the speeds higher bound
printf("[e] Lower bound for wingspan\t %d\n", params.low_wingspan);//outputs the wingspans lower bound
printf("[f] Higher bound for wingspan\t %d\n", params.high_wingspan);//outputs the wingspans higher bound
printf("[g] Lower bound for length\t\t %d\n", params.low_length);//outputs the lengths lower bound
printf("[h] Higher bound for length\t\t %d\n", params.high_length);//outputs the lengths higher bound
printf("[i] lower bound for Type\t\t %c\n", params.low_Model);//outputs the types lower bound
printf("[j] Higher bound for Type\t\t %c\n\n", params.high_Model);//outputs the types higher bound

printf("Selection : ");

scanf(" %c", &choice);//inputs the user's choice

return (choice);//returns the coive the user gave

}

//function call that inputs the parameters
search_params_t get_params() {

search_params_t params;//variable

strcpy(params.low_name,"AAAA");//parmeter for Lower name
strcpy(params.high_name,"zzzz");//paramter for higher name
params.low_speed=MIN;// sets min speed
params.high_speed=MAX;//sets max speed
params.low_wingspan=MIN;//sets min wingS
params.high_wingspan=MAX;//sets max wingS
params.low_length=MIN;//Sets in length
params.high_length=MAX;//Sets max length
params.low_Model='C';//Sets Lower Model
params.high_Model='M';//Sets Higer Model

char chosen;//variable for the value the user chose

do{

chosen= choose(params);//retrieves the letter the user inputed

switch (chosen){
/////////////////////////////////////////////////////////////////FOR NAME
case 'a': //if user inputs 'a'

printf(" New Lower Bound: ");
scanf("%s", params.low_name);//inputs a new value for lower name
break;

case 'b': //if user inputs 'b'

printf(" New Higher Bound: "); 
scanf("%s", params.high_name);//inputs a new value for lower name
break;
////////////////////////////////////////////////////////////////FOR SPEED
case 'c':

printf(" New Lower Bound: ");
scanf("%d", &params.low_speed);
break;

case 'd':

printf(" New Higher Bound: ");
scanf("%d", &params.high_speed);
break;
////////////////////////////////////////////////////////////////FOR WINGSPAN
case 'e':

printf(" New Lower Bound: ");
scanf("%d",  &params.low_wingspan);
break;

case 'f':

printf(" New Higher Bound: ");
scanf("%d",  &params.high_wingspan);
break;
////////////////////////////////////////////////////////////////FOR LENGTH
case 'g':

printf(" New Lower Bound: ");
scanf("%d",  &params.low_length);
break;

case 'h':

printf(" New Higher Bound: ");
scanf("%d",  &params.high_length);
break;
////////////////////////////////////////////////////////////////FOR MODEL/TYPE
case 'i':

printf(" New Lower Bound: ");
scanf("%s",  &params.low_Model);
break;

case 'j':

printf(" New High bound for Type> ");
scanf("%s",  &params.high_Model);
break;

}

}while(chosen!='E');//If user inputted an 'E', then end 

return params;

}

//function call to match 
int match(aircraft_t airc, search_params_t params) {
//MASSIVE STATWMNT THAT CHECKS IF ALL VALUES FIT
return(strcmp(params.low_name, airc.name) <= 0 && strcmp(params.high_name, airc.name) >= 0 
&&
params.low_speed <= airc.speed && params.high_speed >= airc.speed //if lower speed is =< speed =< higher speed
&&
params.low_wingspan <= airc.wingspan && params.high_wingspan >= airc.wingspan //if lower wingS is =< speed =< higher wingS
&&
params.low_length <= airc.length && params.high_length >= airc.length //if lower Length is =< speed =< higher length
&&
params.low_Model <= airc.type && params.high_Model >= airc.type);//if lower model is =< speed =< higher model
}


//Function to Output
void show(aircraft_t airc) {

//used to make value line up
if (airc.name[0]=='C'){
printf("\n%s\t\t%d\t%2.2f\t%2.2f\t%c\t%s\n", airc.name, airc.speed, airc.wingspan, airc.length, airc.type, airc.description);

}
else//outputs plane's values
printf("\n%s\t%d\t%2.2f\t%2.2f\t%c\t%s\n", airc.name, airc.speed, airc.wingspan, airc.length, airc.type, airc.description);

}

//function to convert .txt into .bin
void convert(char* air_file){


//open pointer files
FILE *air_filep, *air_binaryp;

char air_file2[STR_SIZ];//variable to copy STR
strcpy(air_file2,air_file);//copies the string from air1 to air 2


air_filep = fopen(strcat(air_file,".txt"), "r");//open file.txt
air_binaryp = fopen(strcat(air_file2,".bin"), "wb");//opens file.bin

int status=1;//set status

aircraft_t aircr;//variable for struct

//checks if file exists
if(air_filep == NULL )
printf("NO TEXT FILE FOUND.");

else{
while(status>0){//loops while statues isnt 0

//inputs value into status whilst there is value sin the file
status=fscanf(air_filep,"%s %d %lf %lf %c %s",aircr.name, &aircr.speed, &aircr.wingspan, &aircr.length, &aircr.type, aircr.description);

if(status==6){
//writes the values into bin
fwrite(&aircr, sizeof (aircraft_t), 1, air_binaryp);

}}}

fclose(air_filep);//closes the txt

fclose(air_binaryp);//closes the bin

}