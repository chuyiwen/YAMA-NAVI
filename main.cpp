/*-*-c++-*-*/
//
//  main.cpp
//
//  Main program for Dynamic Resource Allocation in ITS (Version 0.83)
//  Last Revised: 11 January 2005
// 


#include "main.h"



int main(int argc, char **argv )
{	
 
  int num_trial     = 1;
  int max_num_objID = 1;//2; 
  int num_obj[12]   = {20,100,500,1000,1500,2000,2500,3000,3500,4000,4500,5000};

  int ratio_Total   = 100;
  int ratio_SD[11]  = {20,20,20,20,20,20,20,20,20,20,20};//{0,10,20,30,40,50}; 
  int ratio_ST[11]  = {80,70,60,50,40,30,20,10, 0,90,100};//{0,10,20,30,40,50};  
  int ratio_RIS[11];
  int max_ratioID   = 9;//9;

  int max_obj = 25000;//25000;
  int num_gen = 65;


  Ctl.delete_graphics = TRUE;

  for(int ratioID = 0; ratioID < max_ratioID; ratioID++){
  //for(int num_objID = 0; num_objID < max_num_objID; num_objID++){
    
    //-- Send Map and Object Information to "Monitor" 
    Monitor     mo;
    mo.getGeoInfo(&Geo);
    mo.getObjInfo(&Obj); 
    mo.getCtlInfo(&Ctl);  
    mo.getMacroInfo(&Macro);      
    
    
    //-- Open Output File for Each Trial 
    Obj.Max_Obj        = max_obj;
    Obj.num_generation = num_gen;

    ratio_RIS[ratioID] = ratio_Total - ratio_SD[ratioID] - ratio_ST[ratioID]; 

    //mo.openOuputFile_trial(argv[2]);
    //mo.openOuputFile_trial(argv[2], num_obj[num_objID], randID);
    //mo.openOuputFile_trial(argv[2], num_obj[num_objID]);
    //mo.openOuputFile_trial(argv[2], ratio_SD[ratioID]);
    mo.openOuputFile_trial(argv[2], Obj.Max_Obj, ratio_SD[ratioID], ratio_ST[ratioID], ratio_RIS[ratioID]);

    
    for(int randID = 50; randID < num_trial+50; randID++){    
  

      //---- Read Map File ----//
      InitData(argv[1]);  

      ratio_RIS[ratioID]             = ratio_Total - ratio_SD[ratioID] - ratio_ST[ratioID]; 
      Obj.ratio_ShortestDistance     = ratio_SD[ratioID];    
      Obj.ratio_SuccessiveReplanning = ratio_ST[ratioID];         
      Obj.ratio_DeclaringPath        = ratio_RIS[ratioID]; 
      
      SetData();  
      my_sleep(500);    
        
 
      //-- Send Map and Object Information to "ObjLocation" 
      ObjLocation ol;  
      ol.getGeoInfo(&Geo);
      ol.getObjInfo(&Obj);     
      ol.getCtlInfo(&Ctl);  
      
      
      //-- Send Map and Object Information to "InfoCenter" 
      InfoCenter  ic;
      ic.getGeoInfo(&Geo);
      ic.getObjInfo(&Obj);  
      ic.idealTrafficInfo();  //(C)meanings?
      

      //-- Simulation Setting        
      //-- Re-setting Obj.Max_Obj and Obj.num_generation
      Obj.Max_Obj        = max_obj;
      Obj.num_generation = num_gen; 

      //randID = randID + 100;
      srand(randID);


      //-- Open Output File for Each Step
      //mo.openOuputFile_step(argv[2]);
      //mo.openOuputFile_step(argv[2], num_obj[num_objID], randID);

      mo.openOuputFile_step(argv[2], Obj.Max_Obj, ratio_SD[ratioID], ratio_ST[ratioID], ratio_RIS[ratioID], randID);

      mo.initializeParameter(); 


      
      //---- Call Graphic Thread ----//    
      if(Ctl.graphics_switch == ON){ 

	while(Ctl.delete_graphics == FALSE)	
	  my_sleep(1000);   

	init_graphics(argc, argv);
	start_graphics();
      }
      
      
      //---- Call Ctl_panel Thread ----// 
      //init_controller(argc, argv);
      //start_controller();
      
      
      //---- Main Simulation Routine ----// 
      printf("\n Now wating \"Start\".\n\n");


      //-- Initialize Origin and Destination of Moving Object
      ol.initializeObjOD(); 


      for(Ctl.step = 0; Ctl.step < Ctl.Max_Step; Ctl.step++){ //Ctl.Max_Step = -999
	
	
	//---- Exit by Pushing "Exit" Button ----//
	if(Ctl.exit == TRUE){
	  printf("\n Exit Simulation.\n\n");
	  exit(0);
	}
       
	
	//---- Calculating Location of Moving Object ----// 
	
	//-- Begin Simulation Loop
	beginSimStep();  
		
	
	//-- Initialize Decision-Making Mechanism of Moving Object
	ol.generateObj();

	
	//-- Update Location of Moving Object
	ol.Update();    

	
	//-- Update Traffic Information
	ic.updateTrafficInfo();  
	ic.collectPlan();  
	
	
	//-- Update Macro Parameter
	mo.updateMacroParameter_step();  	


	//-- Output Macro Parameter in Each Step
	mo.outputMacroParameter_step();  
	
		

	//-- Exit Loop because of no driving objects
	if( ol.checkNumDrivingObj() ){	
	  endSimStep();
	  break;
	}
	

	//-- Leave Simulation Loop
	endSimStep();

	
      }
      

      //-- Output Macro Parameter after Trial  
      mo.outputMicroParameter_trial();  
      

      //-- Close Output File 
      mo.closeOuputFile_step();
            

      //-- Output Macro Parameter after Trial       
      mo.outputMacroParameter_trial();  
                 
    }

    //-- Close Output File 
    mo.closeOuputFile_trial();
       
  }  


  printf("\n All Process are Completed.\n\n");

  return 0;

}

//--------------------------------------------------------------------------//
