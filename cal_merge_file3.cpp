/*-*-c++-*-*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream.h>
#include <strstream.h>

//このプログラムは, 複数のファイルを読み込んで, 
//一つのファイルに出力するファイルマージプログラムです

//入出力するファイル数とファイル名を事前に指定しておく必要があります



int main()
{

  FILE *input_fp;
  FILE *output_fp1;  

  char input_filename[100]       = "empty";  
  char input_filename_front[100] = "ave_test2_n55_25000_obj25000_SD20";  
  char output_filename1[100]     = "merge";  
  
  int  input_filename_No1[9]     = {80,70,60,50,40,30,20,10,0};
  int  input_filename_No2[9]     = {0, 10,20,30,40,50,60,70,80};

  //int  input_filename_No[12]     = {20,100,500,1000,1500,2000,2500,3000,3500,4000,4500,5000};

  double buffer;
  int    NumFiles      = 9; 
  int    NumParameter  = 84;   
  int    initial_ID    = 0;
  double parameter[NumParameter]; 



  //-- Open Input File 
  sprintf(output_filename1,"%s_%s", output_filename1, input_filename_front);	
  output_fp1 = fopen(output_filename1,"w");


  //-- Read Parametrs from File
  for(int fileID = initial_ID; fileID < NumFiles + initial_ID; fileID++){  
    
    sprintf(input_filename,"%s_ST%d_RIS%d",
	    input_filename_front, 
	    input_filename_No1[fileID], 
	    input_filename_No2[fileID]);  

    //sprintf(input_filename,"%s%d",input_filename_front, input_filename_No[fileID]);

    input_fp = fopen(input_filename,"r"); //average_temp_ave_obj4000
    
    printf("\nNow loading %s ---\n\n",input_filename);
      
    
    for(int parameterID = 0; parameterID < NumParameter; parameterID++){
      
      fscanf(input_fp,"%lf",&buffer);
      fprintf(output_fp1,"%f\t",buffer);
      
      printf("%2d:%f\n",parameterID, buffer);	  
    }  
    
    fprintf(output_fp1,"\n");  

    fclose(input_fp); 
    
    printf("\n");
  }  
  
  fclose(output_fp1);


  printf("\n\n Fin\n");
 
  return 0;
}
