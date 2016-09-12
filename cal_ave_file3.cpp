/*-*-c++-*-*/
//
//  cal_ave_files.cpp
//
//  Program Applied after Simulation for Arrenging Result
//  Last Revised: 12 November 2003
// 


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <iostream.h>
#include <strstream.h>

//このプログラムは, 1つのファイルを読み込んで, 
//複数のデータ時系列のそれぞれの平均を一つのファイルに出力するプログラムです
//入出力ファイル名とパラメータ数を事前に指定しておく必要があります



int main(int argc, char **argv )
{

  FILE *input_fp;
  FILE *output_fp;  

  char input_filename[100]       = "empty"; 
  char input_filename_front[100] = "test_Ave_obj500"; //test_Ave_obj10 
  char output_filename[100]      = "ave";


  //--  1  Defined File Name
  //sprintf(output_filename,"%s_%s",output_filename, input_filename_front); 
  //sprintf(input_filename,"%s",input_filename_front);  


  //--  2  File Name from Command Line
  sprintf(output_filename,"%s_%s",output_filename, argv[1]);
  sprintf(input_filename,"%s",argv[1]);


  double buffer;
  int    NumFiles      = 10;  
  int    NumParameter  = 84;
  
  double parameter[NumParameter];  
  double sum_parameter[NumParameter];
  double ave_parameter[NumParameter];


  //-- Initialize "sum_parameter"
  for(int parameterID = 0;parameterID < NumParameter; parameterID++){

    sum_parameter[parameterID] = 0;
  }

  
           
  //-- Open Input File 
  input_fp = fopen(input_filename,"r"); 
  printf("\nNow loading %s ---\n\n",input_filename);  


  //-- Read Parametrs from File
  for(int fileID = 0; fileID < NumFiles; fileID++){  
      
    for(int parameterID = 0; parameterID < NumParameter; parameterID++){
	            
      fscanf(input_fp,"%lf",&buffer);
      
      parameter[parameterID]      = buffer;
      sum_parameter[parameterID] += parameter[parameterID];

      printf("parameter[%d]:%f\n", parameterID, parameter[parameterID]);

    }

  }
  fclose(input_fp); 



  //-- Calculate Average of Each Parameter
  for(int parameterID = 0; parameterID < NumParameter; parameterID++){
    
    ave_parameter[parameterID] = sum_parameter[parameterID]/NumFiles;
  }  
  
  
  //-- Write Average to Output File
  output_fp = fopen(output_filename,"w");

  for(int parameterID = 0; parameterID < NumParameter; parameterID++){
    
    fprintf(output_fp,"%f\t",ave_parameter[parameterID]);
  }  
  fclose(output_fp);


  printf("\n\n Fin\n");
 
  return 0;
}
