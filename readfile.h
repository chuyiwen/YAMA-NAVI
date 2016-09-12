/*-*-c++-*-*/
//
//  readfile.h
//
//

#ifndef READFILE_H
#define READFILE_H


//--------------------------------------------------------------------------//

void InitData(char *input_file1)
{ 
  
  FILE *fp_map; 
  char map_file[100];
  sprintf(map_file, "%s",input_file1);

  if((fp_map = fopen(map_file,"r"))==NULL){
    fprintf(stderr, "can't open %s.\n",map_file);
    exit(1);
  }


  //-- Read File of Map and Moving Object Infomation

  printf("\n Now reading file \"%s\"...\n\n",map_file);
  
  char data_type[100];
  char *str_frame     = "Frame";   
  char *str_node      = "node"; 
  char *str_arc       = "arc";
  char *str_obj       = "object";  
  char *str_max_obj   = "MaxObject";      
  char *str_max_step  = "MaxStep";  

  char *str_graphics  = "Graphics";  
  char *str_chart     = "Chart";  
  char *str_start     = "AutoStart";  

  char graphics_switch[100];
  char *str_ON        = "ON";  
  char *str_OFF       = "OFF";

  char *str_SD        = "ShortestDistance"; 
  char *str_RO        = "ReplanningInOrigin"; 
  char *str_SR        = "SuccessiveReplanning";
  char *str_CA        = "CongestionAvoidance";
  char *str_DP        = "DeclaringPath";

  Geo.num_node        = 0;
  Geo.num_arc         = 0;  

  Ctl.graphics_switch = ON;  	  
  Ctl.chart_switch    = ON;    
  Ctl.Max_Step        = -999;

  Obj.num_move        = 0;
  Obj.Max_Obj         = -999;  

  Obj.ratio_ShortestDistance           = 0; 
  Obj.ratio_ReplanningInOrigin         = 0;
  Obj.ratio_SuccessiveReplanning       = 0;
  Obj.ratio_CongestionAvoidance        = 0; 
  Obj.ratio_DeclaringPath              = 0;

  Obj.present_num_ShortestDistance     = 0;
  Obj.present_num_ReplanningInOrigin   = 0;
  Obj.present_num_SuccessiveReplanning = 0;
  Obj.present_num_CongestionAvoidance  = 0; 
  Obj.present_num_DeclaringPath        = 0;



  while(fscanf(fp_map,"%s",&data_type)!=EOF)
    {  

      //-- Read Fram Size
      if(strncmp(data_type,str_frame,strlen(str_frame)) == COINCIDENCE){

	fscanf(fp_map,"%d",&(Frame.width));
	fscanf(fp_map,"%d",&(Frame.height)); 

	printf("%s\t x=%d\t y=%d\n",
	       data_type,Frame.width,Frame.height);
      }     

      //-- Read Node 
      if(strncmp(data_type,str_node,strlen(str_node)) == COINCIDENCE){  
		
  	fscanf(fp_map,"%d",&(Geo.node[Geo.num_node].no));
      	fscanf(fp_map,"%d",&(Geo.node[Geo.num_node].x));
	fscanf(fp_map,"%d",&(Geo.node[Geo.num_node].y));
	
	Geo.node[Geo.num_node].no = Geo.num_node;
	
	printf("%s %d\t x=%d\t y=%d\n",
	       data_type,Geo.node[Geo.num_node].no,
	       Geo.node[Geo.num_node].x,Geo.node[Geo.num_node].y);	

	Geo.num_node++;
      }     	
      
      //-- Read Arc 
      if(strncmp(data_type,str_arc,strlen(str_arc)) == COINCIDENCE){
	fscanf(fp_map,"%d",&(Geo.arc[Geo.num_arc].no));
	fscanf(fp_map,"%d",&(Geo.arc[Geo.num_arc].start));
      	fscanf(fp_map,"%d",&(Geo.arc[Geo.num_arc].end));
	//fscanf(fp_map,"%d",&(arc[num_arc].length));  
	fscanf(fp_map,"%lf",&(Geo.arc[Geo.num_arc].weight) );

	Geo.arc[Geo.num_arc].no = Geo.num_arc;

	printf("%s %d\t x=%d\t y=%d w:%f\n",
	       data_type,
	       Geo.arc[Geo.num_arc].no,
	       Geo.arc[Geo.num_arc].start,
	       Geo.arc[Geo.num_arc].end,
	       Geo.arc[Geo.num_arc].weight);	

	Geo.num_arc++;
      }	

      
 
      //-- Read Objet Information
      if(strncmp(data_type,str_obj,strlen(str_obj)) == COINCIDENCE){
	fscanf(fp_map,"%d",&(Obj.move[Obj.num_move].no));

	fscanf(fp_map,"%d",&(Obj.move[Obj.num_move].origin));	
      	fscanf(fp_map,"%d",&(Obj.move[Obj.num_move].destination)); 

	fscanf(fp_map,"%d",&(Obj.move[Obj.num_move].origin_arc));
	fscanf(fp_map,"%d",&(Obj.move[Obj.num_move].origin_side));
	fscanf(fp_map,"%d",&(Obj.move[Obj.num_move].origin_block));	

      	fscanf(fp_map,"%d",&(Obj.move[Obj.num_move].destination_arc));   	
	fscanf(fp_map,"%d",&(Obj.move[Obj.num_move].destination_side));   	
	fscanf(fp_map,"%d",&(Obj.move[Obj.num_move].destination_block));


	//fscanf(fp_map,"%d",&(Obj.move[Obj.num_move].arc));		
	//fscanf(fp_map,"%d",&(Obj.move[Obj.num_move].start));	
	//fscanf(fp_map,"%d",&(Obj.move[Obj.num_move].end));	
	//fscanf(fp_map,"%d",&(Obj.move[Obj.num_move].distance));
	//fscanf(fp_map,"%f",&(Obj.move[Obj.num_move].velocity));
	
	printf("%s %d\t arc %d side %d block %d -> arc %d side %d block %d,vel=%3.1f\n",
	       data_type,
	       Obj.move[Obj.num_move].no,
	       Obj.move[Obj.num_move].origin_arc,	     
	       Obj.move[Obj.num_move].origin_side,	  
	       Obj.move[Obj.num_move].origin_block,
	       Obj.move[Obj.num_move].destination_arc,		       
	       Obj.move[Obj.num_move].destination_side,  
	       Obj.move[Obj.num_move].destination_block,	
	       //Obj.move[Obj.num_move].arc,
	       //Obj.move[Obj.num_move].start
	       //Obj.move[Obj.num_move].end
	       //Obj.move[Obj.num_move].distance,
	       Obj.move[Obj.num_move].velocity
	       );
	
	Obj.num_move++;
      }	

      //-- Read Maximum Number of Object
      if(strncmp(data_type,str_max_obj,strlen(str_max_obj)) == COINCIDENCE){
	fscanf(fp_map,"%d",&(Obj.Max_Obj));
	
	printf("Max_Obj\t %d\n",Obj.Max_Obj);
      }


      //-- Read Maximum Step of Iteration
      if(strncmp(data_type,str_max_step,strlen(str_max_step)) == COINCIDENCE){
	fscanf(fp_map,"%d",&(Ctl.Max_Step));
	
	printf("Max_Obj\t %d\n",Ctl.Max_Step);
      }


      //-- Read Graphics On or Off
      if(strncmp(data_type,str_graphics,strlen(str_graphics)) == COINCIDENCE){

	fscanf(fp_map,"%s",&(graphics_switch));

	if(strncmp(graphics_switch,str_ON,strlen(str_ON)) == COINCIDENCE){
	  Ctl.graphics_switch = ON;  	  
	}

	if(strncmp(graphics_switch,str_OFF,strlen(str_OFF)) == COINCIDENCE){
	  Ctl.graphics_switch = OFF;  	  
	  Ctl.chart_switch    = OFF;  
	}
	
	printf("Graphics\t");
	
	if(Ctl.graphics_switch == ON)
	  printf("ON\n");

	if(Ctl.graphics_switch == OFF)
	  printf("OFF\n");

      }


      //-- Read Chart On or Off
      if(strncmp(data_type,str_chart,strlen(str_chart)) == COINCIDENCE){

	fscanf(fp_map,"%s",&(graphics_switch));

	if(strncmp(graphics_switch,str_ON,strlen(str_ON)) == COINCIDENCE){
	  Ctl.chart_switch = ON;  
	}

	if(strncmp(graphics_switch,str_OFF,strlen(str_OFF)) == COINCIDENCE){
	  Ctl.chart_switch = OFF;  
	}

	printf("Chart\t\t");
	
	if(Ctl.chart_switch == ON)
	  printf("ON\n");

	if(Ctl.chart_switch == OFF)
	  printf("OFF\n");

      }


      //-- Read Auto Start On or Off
      if(strncmp(data_type,str_start,strlen(str_start)) == COINCIDENCE){

	fscanf(fp_map,"%s",&(graphics_switch));

	if(strncmp(graphics_switch,str_ON,strlen(str_ON)) == COINCIDENCE){
	  Ctl.auto_start = ON;  
	}

	if(strncmp(graphics_switch,str_OFF,strlen(str_OFF)) == COINCIDENCE){	 
	  Ctl.auto_start = OFF;  
	}

	printf("Auto Start\t");
	
	if(Ctl.auto_start == ON)
	  printf("ON\n");

	if(Ctl.auto_start == OFF)
	  printf("OFF\n");

      }


      //-- Read Ratio of Object with Shortest Distance 
      if(strncmp(data_type,str_SD,strlen(str_SD)) == COINCIDENCE){
	fscanf(fp_map,"%d",&(Obj.ratio_ShortestDistance));
	
	printf("Ratio of ShortestDistance\t %d\n",Obj.ratio_ShortestDistance);
      }

     //-- Read Ratio of Object with Replanning in Origin  
      if(strncmp(data_type,str_RO,strlen(str_RO)) == COINCIDENCE){
	fscanf(fp_map,"%d",&(Obj.ratio_ReplanningInOrigin));
	
	printf("Ratio of Replanning in Origin\t %d\n",Obj.ratio_ReplanningInOrigin);
      }

     //-- Read Ratio of Object with Successive Replanning
      if(strncmp(data_type,str_SR,strlen(str_SR)) == COINCIDENCE){
	fscanf(fp_map,"%d",&(Obj.ratio_SuccessiveReplanning));
	
	printf("Ratio of Successive Replanning\t %d\n",Obj.ratio_SuccessiveReplanning);
      }

     //-- Read Ratio of Object with Congestion Avoidance  
      if(strncmp(data_type,str_CA,strlen(str_CA)) == COINCIDENCE){
	fscanf(fp_map,"%d",&(Obj.ratio_CongestionAvoidance));
	
	printf("Ratio of Congestion Avoidance \t %d\n",Obj.ratio_CongestionAvoidance );
      }

      //-- Read Ratio of Object with Congestion Avoidance  
      if(strncmp(data_type,str_DP,strlen(str_DP)) == COINCIDENCE){
	fscanf(fp_map,"%d",&(Obj.ratio_DeclaringPath));
	
	printf("Ratio of Declaring Path \t %d\n",Obj.ratio_DeclaringPath );
      }


    }

  fclose(fp_map);

  printf("\n\n\n");

  
}

//--------------------------------------------------------------------------//

void SetData(void)
{

  
//-- Detect Arc that Connects Two Nodes
  

  //-- Check Arc Double Count

  int count =0;

  for(int arcID1 = 0; arcID1 < Geo.num_arc; arcID1++){
    for(int arcID2 = 0; arcID2 < Geo.num_arc; arcID2++){
      
      
      if(arcID1 != arcID2){
	
	if((Geo.arc[arcID1].start == Geo.arc[arcID2].end)&&
	   (Geo.arc[arcID2].start == Geo.arc[arcID1].end)){
	    
	    Geo.arc[arcID1].start  = -999;	
	    Geo.arc[arcID1].end    = -999;
	    Geo.arc[arcID1].weight = (double)-999;
	    
	    count++;

	    printf("double arcs No.%d \t No.%d\n\n",arcID1, arcID2);

	}
	/*
	if(Geo.arc[arcID1].start == Geo.arc[arcID2].start){ 
	  if(Geo.arc[arcID2].end == Geo.arc[arcID1].end){
	    
	    Geo.arc[arcID1].start  = -999;	
	    Geo.arc[arcID1].end    = -999;
	    Geo.arc[arcID1].weight = -999;
	  }
	  }
	*/
	
      }
      
      
    }//-for2
  }//-for1
  
  printf("count %d\n\n",count);

  int num_double_count_arc = 0;
      
  for(int arcID = 0; arcID < Geo.num_arc; arcID++){
    
    //printf("before \n");
    //printf("Geo.arc[arcID].no     %d\n",Geo.arc[arcID].no);
    //printf("Geo.arc[arcID].weight %f\n",Geo.arc[arcID].weight);
    //printf("Geo.arc[arcID].start  %d\n",Geo.arc[arcID].start);
    //printf("Geo.arc[arcID].end    %d\n",Geo.arc[arcID].end);


    if(Geo.arc[arcID].weight == -999){
      num_double_count_arc++;
      Geo.num_arc--;
    }
    
    if(Geo.arc[arcID + num_double_count_arc].weight == -999){
      num_double_count_arc++;
      Geo.num_arc--;
    }

    Geo.arc[arcID].no     = arcID;	
    Geo.arc[arcID].start  = Geo.arc[arcID + num_double_count_arc].start;	
    Geo.arc[arcID].end    = Geo.arc[arcID + num_double_count_arc].end;
    Geo.arc[arcID].weight = Geo.arc[arcID + num_double_count_arc].weight;
    
    //printf("after \n");
    //printf("Geo.arc[arcID].no     %d\n",Geo.arc[arcID].no);
    //printf("Geo.arc[arcID].weight %f\n",Geo.arc[arcID].weight);
    //printf("Geo.arc[arcID].start  %d\n",Geo.arc[arcID].start);
    //printf("Geo.arc[arcID].end    %d\n\n",Geo.arc[arcID].end);

  }
  
  //Geo.num_arc -= num_double_count_arc;
  
  printf("\n num_double_count_arc = %d\n\n",num_double_count_arc);
  
  
  
  //-- Initialize
  for(int nodeID = 0; nodeID < Geo.num_node; nodeID++){
    Geo.node[nodeID].num_connect_arc = 0;
  }
  
  //-- Detect
  for(int nodeID = 0; nodeID < Geo.num_node; nodeID++){
    for(int arcID = 0; arcID < Geo.num_arc; arcID++){

      if( Geo.node[nodeID].no == Geo.arc[arcID].start){
	Geo.node[nodeID].connect_arc[Geo.node[nodeID].num_connect_arc] 
	  = Geo.arc[arcID].no;	
	Geo.node[nodeID].num_connect_arc++;
      }

      if( Geo.node[nodeID].no == Geo.arc[arcID].end){
	Geo.node[nodeID].connect_arc[Geo.node[nodeID].num_connect_arc] 
	  = Geo.arc[arcID].no;	
	Geo.node[nodeID].num_connect_arc++;
      }

    }
  }




  //-- Detect Node that Connects with Another Node 

  //-- Initialize
  for(int nodeID = 0; nodeID < Geo.num_node; nodeID++){
    Geo.node[nodeID].num_connect_node = 0;
  }

  //-- Detect
  for(int arcID = 0; arcID < Geo.num_arc; arcID++){

    int start = Geo.arc[arcID].start;  
    int end   = Geo.arc[arcID].end;
    
    printf("arc = %d\n",Geo.arc[arcID].no);
    
    Geo.node[start].connect_node[ Geo.node[start].num_connect_node ] = end;
    Geo.node[end].connect_node[ Geo.node[end].num_connect_node ]     = start;

    printf("node %d\t",Geo.node[start].no);
    printf("start node No.%d = %d\t %d\n",  Geo.node[start].num_connect_node, 
	   Geo.node[start].connect_node[ Geo.node[start].num_connect_node ],start );
    
    printf("node %d\t",Geo.node[end].no);
    printf("end   node No.%d = %d\t %d\n\n",  Geo.node[end].num_connect_node,
	   Geo.node[end].connect_node[ Geo.node[end].num_connect_node ],end);

    Geo.node[start].num_connect_node++;
    Geo.node[ end ].num_connect_node++;
  }


  //-- Calculate Length and Distance of Arc
  for(int arcID = 0; arcID < Geo.num_arc; arcID++){
    
    int start = Geo.arc[arcID].start;  
    int end   = Geo.arc[arcID].end;

    int x_2   = (int)(pow(Geo.node[start].x - Geo.node[end].x, 2.0));    
    int y_2   = (int)(pow(Geo.node[start].y - Geo.node[end].y, 2.0));

    
    Geo.arc[arcID].length   = (int)(sqrt( (double)(x_2 + y_2)  ) );
   
   
    /*
    
if(arcID == 17 || arcID == 18 || arcID == 20 || arcID == 21 || 
       arcID == 23 || arcID == 24 || arcID == 26 || arcID == 27 ){
      
      
Geo.arc[arcID].length = Geo.arc[0].length;
    }
    */

    Geo.arc[arcID].distance = Geo.arc[arcID].weight * (double)Geo.arc[arcID].length*LENGTH_UNIT; 


    //
    printf("arc:%d distance:%f\n",arcID,Geo.arc[arcID].distance);
  }


  
  //-- Initialize "Adjacency[][]" & "ExpectedTravelTime[][]"
  for(int nodeID1 = 0; nodeID1 < Geo.num_node; nodeID1++){
    for(int nodeID2 = 0; nodeID2 < Geo.num_node; nodeID2++){

      Geo.Adjacency[nodeID1][nodeID2]           = MAX_VALUE;
      Geo.ExpectedTravelTime[nodeID1][nodeID2]  = MAX_VALUE;
      Geo.IdealTravelTime[nodeID1][nodeID2]     = MAX_VALUE;
      Geo.CongestionAvoidance[nodeID1][nodeID2] = MAX_VALUE;

      Geo.DeclaredPlan[nodeID1][nodeID2]        = 1.0; 
      
      Geo.BOOL_Adjacency[nodeID1][nodeID2]      = FALSE; 

    }
  }

  for(int arcID = 0; arcID < Geo.num_arc; arcID++){
    
    int start = Geo.arc[arcID].start;  
    int end   = Geo.arc[arcID].end;

    Geo.Adjacency[start][end]           = Geo.arc[arcID].distance;
    Geo.Adjacency[end][start]           = Geo.arc[arcID].distance;

    Geo.ExpectedTravelTime[start][end]  = Geo.arc[arcID].distance/(13.89*TIME_UNIT);
    Geo.ExpectedTravelTime[end][start]  = Geo.arc[arcID].distance/(13.89*TIME_UNIT);

    Geo.CongestionAvoidance[start][end] = Geo.arc[arcID].distance/(13.89*TIME_UNIT);
    Geo.CongestionAvoidance[end][start] = Geo.arc[arcID].distance/(13.89*TIME_UNIT);

    Geo.BOOL_Adjacency[start][end]      = TRUE; 
    Geo.BOOL_Adjacency[end][start]      = TRUE; 
   
  }




  //-- (RART 1) Initialize Block in Arc 
  for(int arcID = 0; arcID < Geo.num_arc; arcID++){

    Geo.arc[arcID].unit_block = 13.89*TIME_UNIT; //-- dL = 自由流速度(時速50km=秒速13.89m)×1sec
    Geo.arc[arcID].num_block  = (int)((double)Geo.arc[arcID].distance/Geo.arc[arcID].unit_block);

    //Geo.arc[arcID].num_block  
    //= 1 + (int)((double)Geo.arc[arcID].distance/Geo.arc[arcID].unit_block);
    //
    //printf("Geo.arc[%d].num_block:%d Geo.arc[arcID].distance:%f\n",
    //   arcID, Geo.arc[arcID].num_block,Geo.arc[arcID].distance);
  }
 
  
  int    sum_block                = 0;
  int    int_sum_avairable_obj    = 0;
  double double_sum_avairable_obj = 0;  
  double total_road_length        = 0;  


  for(int arcID = 0; arcID < Geo.num_arc; arcID++){    
    for(int sideID = 0; sideID < NUM_SIDE; sideID++){
      for(int blockID = 0; blockID < Geo.arc[arcID].num_block; blockID++){
	
	Geo.arc[arcID].block[sideID][blockID].block_length = Geo.arc[arcID].unit_block;//-- =13.89*TIME_UNIT
	

	//-- Last Block is longer than ohters.
	if(blockID == Geo.arc[arcID].num_block - 1){
	  Geo.arc[arcID].block[sideID][blockID].block_length       
	    = Geo.arc[arcID].block[sideID][blockID].block_length 
	    + (Geo.arc[arcID].distance - 
	       (double)Geo.arc[arcID].num_block * Geo.arc[arcID].block[sideID][blockID].block_length);
	}	
	

	//-- Last Block is shorter than ohters.
	/*
	if(blockID == Geo.arc[arcID].num_block - 1){
	  Geo.arc[arcID].block[sideID][blockID].block_length       
	    =  Geo.arc[arcID].distance - 
	       ((double)(Geo.arc[arcID].num_block-1) * Geo.arc[arcID].block[sideID][blockID].block_length);
	}
	*/

	
	//printf("arc:%d side:%d block:%d length:%f\n",
	//      arcID,sideID,blockID,Geo.arc[arcID].block[sideID][blockID].block_length);
	

	Geo.arc[arcID].block[sideID][blockID].K                   = 0;
	Geo.arc[arcID].block[sideID][blockID].K_saturation        = 0.14;
	Geo.arc[arcID].block[sideID][blockID].K_critical          = 0.07;
	Geo.arc[arcID].block[sideID][blockID].block_num_move      = 0;	
	Geo.arc[arcID].block[sideID][blockID].block_num_wait      = 0;
	Geo.arc[arcID].block[sideID][blockID].block_num_generated = 0;

	int num_route = 0;

	if(num_route == 2){
	  if(arcID == 2 || arcID == 5 ){
	    Geo.arc[arcID].block[sideID][blockID].K_saturation   = 0.14/2.0;
	  }
	}

	if(num_route == 3){
	  if(arcID == 2 || arcID == 5  || arcID == 16){
	    Geo.arc[arcID].block[sideID][blockID].K_saturation   = 0.14/3.0;
	  }
	}

	if(num_route == 4){
	  if(arcID == 2 || arcID == 5  || arcID == 16 || arcID == 19){
	    Geo.arc[arcID].block[sideID][blockID].K_saturation   = 0.14/4.0;
	  }
	}

	if(num_route == 5){
	  if(arcID == 2 || arcID == 5  || arcID == 16 || arcID == 19 || arcID == 22){
	    Geo.arc[arcID].block[sideID][blockID].K_saturation   = 0.14/5.0;
	  }
	}

	if(num_route == 6){
	  if(arcID == 2 || arcID == 5  || arcID == 16 || arcID == 19 || arcID == 22 || arcID == 25){
	    Geo.arc[arcID].block[sideID][blockID].K_saturation   = 0.14/6.0;
	  }
	}
	


	//Geo.arc[arcID].block[sideID][blockID].M_in           = 0;   	
	//Geo.arc[arcID].block[sideID][blockID].M_out          = 0;   
	//Geo.arc[arcID].block[sideID][blockID].E_out          = 0.0; 
	//Geo.arc[arcID].block[sideID][blockID].A_in           = 0.0;   
	//Geo.arc[arcID].block[sideID][blockID].A_out          = 0.0; 

	for(int block_objID = 0;block_objID < 20 ;block_objID++)
	  Geo.arc[arcID].block[sideID][blockID].block_move[block_objID] = -999;


	
	sum_block++;

	int_sum_avairable_obj    += 
	  (int)(Geo.arc[arcID].block[sideID][blockID].K_saturation
		*Geo.arc[arcID].block[sideID][blockID].block_length);
	
	double_sum_avairable_obj += 
	  Geo.arc[arcID].block[sideID][blockID].K_saturation
	  *Geo.arc[arcID].block[sideID][blockID].block_length; 

	total_road_length        +=  
	  Geo.arc[arcID].block[sideID][blockID].block_length; 

      }    
      
      Geo.arc[arcID].block_start_node[UPTOWN]   = Geo.arc[arcID].start;
      Geo.arc[arcID].block_end_node[UPTOWN]     = Geo.arc[arcID].end;
      
      Geo.arc[arcID].block_start_node[DOWNTOWN] = Geo.arc[arcID].end;
      Geo.arc[arcID].block_end_node[DOWNTOWN]   = Geo.arc[arcID].start; 
      

      /*
      if(sideID == DOWNTOWN){
	printf("arcID:%d sideID:%d up_start node  :%d\n",
	arcID,UPTOWN, Geo.arc[arcID].block_start_node[UPTOWN]); 
	printf("arcID:%d sideID:%d up_end node    :%d\n",
	arcID,UPTOWN, Geo.arc[arcID].block_end_node[UPTOWN]); 
	printf("arcID:%d sideID:%d down_start node:%d\n",
	arcID,DOWNTOWN, Geo.arc[arcID].block_start_node[DOWNTOWN]); 
	printf("arcID:%d sideID:%d down_end node  :%d\n",
	arcID,DOWNTOWN, Geo.arc[arcID].block_end_node[DOWNTOWN]);
	printf("\n");
      }
      */
      
    }
  }

  printf("sum_block               :%d\n",sum_block);	
  printf("int_sum_available_obj   :%d\n",int_sum_avairable_obj);	
  printf("double_sum_available_obj:%f\n",double_sum_avairable_obj);
  printf("total_road_length       :%f\n",total_road_length);      



  //-- Initialize Parameters of Object  
  for(int objID = 0; objID < Obj.num_move;objID++){

    int arcID    = Obj.move[objID].origin_arc;
    int sideID   = Obj.move[objID].origin_side;
    int blockID  = Obj.move[objID].origin_block;
    
    int num_move = Geo.arc[arcID].block[sideID][blockID].block_num_move;

    Obj.move[objID].arc            = arcID;
    Obj.move[objID].side           = sideID;   
    Obj.move[objID].block          = blockID;
    Obj.move[objID].end            = Geo.arc[arcID].block_end_node[sideID];
    Obj.move[objID].start          = Geo.arc[arcID].block_start_node[sideID];

    Obj.move[objID].plan_progress  = 0;    
    Obj.move[objID].plan_direction = OUTWARD;

    Obj.move[objID].gain           = 0;
    Obj.move[objID].velocity       = 0; 
    
    Obj.move[objID].driving_status = STANDBY;

    Obj.move[objID].last_required_time             = 0;          
    Obj.move[objID].last_required_distance         = 0;         

    Obj.move[objID].efficiency_time                = 0;         
    Obj.move[objID].efficiency_distance            = 0;        
    Obj.move[objID].present_efficiency_time        = 0;         
    Obj.move[objID].present_efficiency_distance    = 0;  
    
    for(int direction = 0; direction < ROUND_TRIP; direction++){  
      Obj.move[objID].num_arrival[direction]       = 0;
      Obj.move[objID].required_time[direction]     = 0;   
      Obj.move[objID].required_distance[direction] = 0;
    }


    //-- Initialize Number of Object in Block 
    Geo.arc[arcID].block[sideID][blockID].block_move[num_move] = Obj.move[objID].no;
    Geo.arc[arcID].block[sideID][blockID].block_num_move++;


    int    last_block  = Geo.arc[arcID].num_block - 1;
    double block_distance_from_start;

    if(blockID == last_block){
      Obj.move[objID].distance = Geo.arc[arcID].block[sideID][last_block].block_length 
	- Geo.arc[arcID].block[sideID][blockID].block_num_move;
    }
    else{
      Obj.move[objID].distance = 
	Geo.arc[arcID].block[sideID][last_block].block_length 
	+ (last_block - blockID)*Geo.arc[arcID].block[sideID][blockID].block_length
	- Geo.arc[arcID].block[sideID][blockID].block_num_move/Geo.arc[arcID].block[sideID][blockID].K_saturation;
    }

    printf("obj %d -- distance %f\n", objID,Obj.move[objID].distance);
    
  }


  //--  Initialize Number of Objects with Each Navigation Type

  if(Obj.Max_Obj == -999){
    Obj.Max_Obj = MAX_MOVE;
  }

  
  double sum_ratio = Obj.ratio_ShortestDistance + Obj.ratio_ReplanningInOrigin 
                      + Obj.ratio_SuccessiveReplanning + Obj.ratio_CongestionAvoidance 
                      + Obj.ratio_DeclaringPath;
  
  Obj.num_ShortestDistance     = (int)((Obj.Max_Obj)* Obj.ratio_ShortestDistance/sum_ratio);
  Obj.num_ReplanningInOrigin   = (int)((Obj.Max_Obj)* Obj.ratio_ReplanningInOrigin/sum_ratio);  
  Obj.num_SuccessiveReplanning = (int)((Obj.Max_Obj)* Obj.ratio_SuccessiveReplanning/sum_ratio);
  Obj.num_CongestionAvoidance  = (int)((Obj.Max_Obj)* Obj.ratio_CongestionAvoidance/sum_ratio); 
  Obj.num_DeclaringPath        = (int)((Obj.Max_Obj)* Obj.ratio_DeclaringPath/sum_ratio);

  
  double sum_num  = Obj.num_ShortestDistance + Obj.num_ReplanningInOrigin 
                   + Obj.num_SuccessiveReplanning + Obj.num_CongestionAvoidance 
                   + Obj.num_DeclaringPath;
 
  /*
  if( Obj.Max_Obj != sum_num){
    printf("Error of Number of Navi Type SetData at in readfile.h \n");
    printf("Number of Shortest Distance\t %d\n",Obj.num_ShortestDistance);
    printf("Number of Replanning In Origin\t %d\n",Obj.num_ReplanningInOrigin);
    printf("Number of Successive Replanning\t %d\n",Obj.num_SuccessiveReplanning);
    printf("Number of Congestion Avoidance\t %d\n",Obj.num_CongestionAvoidance);  
    printf("Number of Declaring Path \t %d\n",Obj.num_DeclaringPath);
    printf("Number of Moving Objects\t %d\n\n",Obj.Max_Obj );
    exit(1);
  }
  */  


  /*
  Obj.num_navi_type[0]         =  Obj.num_ShortestDistance;
  Obj.num_navi_type[1]         =  Obj.num_ReplanningInOrigin;
  Obj.num_navi_type[2]         =  Obj.num_SuccessiveReplanning;
  Obj.num_navi_type[3]         =  Obj.num_CongestionAvoidance;
  Obj.num_navi_type[4]         =  Obj.Max_Obj;
  */

  printf("Number of Shortest Distance\t %d\n",Obj.num_ShortestDistance);
  printf("Number of Replanning In Origin\t %d\n",Obj.num_ReplanningInOrigin);
  printf("Number of Successive Replanning\t %d\n",Obj.num_SuccessiveReplanning);
  printf("Number of Congestion Avoidance\t %d\n",Obj.num_CongestionAvoidance);  
  printf("Number of Declaring Path \t %d\n",Obj.num_DeclaringPath);



  //-- Initialize Parameters of Simulation Control 
   Ctl.step = 0;



  //-- (RART 2) Initialize Density of Block in Arc  
  for(int arcID = 0; arcID < Geo.num_arc; arcID++){ 
    for(int sideID = 0; sideID < NUM_SIDE; sideID++){
      for(int blockID = 0; blockID < Geo.arc[arcID].num_block; blockID++){
      
	int    num_move = Geo.arc[arcID].block[sideID][blockID].block_num_move;
	double dL       = Geo.arc[arcID].block[sideID][blockID].block_length;
	
	Geo.arc[arcID].block[sideID][blockID].K = (double)num_move/dL;

	//printf("arc:%2d side:%d block%2d obj:%d k:%f\n",
	//       arcID,sideID,blockID,num_move,Geo.arc[arcID].block[sideID][blockID].K);

      }
    }
  }
  //printf("\n"); 



  //-- Test Printout
  for(int objID = 0;objID < Obj.num_move;objID++){
      printf("obj %d in arc%d side%d block%d --start:%d -> end:%d -- distance %4.1f\n",
	     Obj.move[objID].no,
	     Obj.move[objID].arc,	     
	     Obj.move[objID].side,	     
	     Obj.move[objID].block,
	     Obj.move[objID].start,
	     Obj.move[objID].end,
	     Obj.move[objID].distance);
  }
  printf("\n");
  

  for(int nodeID = 0; nodeID < Geo.num_node; nodeID++){
    printf("node %d\t has %d\t arcs ",
	   Geo.node[nodeID].no,Geo.node[nodeID].num_connect_arc);
    
    for(int arcID = 0; arcID < Geo.node[nodeID].num_connect_arc;arcID++){
      printf(" %d\t",Geo.node[nodeID].connect_arc[arcID]);	
    }
    printf("\n");
  }
  

  for(int nodeID = 0; nodeID < Geo.num_node; nodeID++){
    printf("node %d (%d) has %d nodes\t",
	   Geo.node[nodeID].no, nodeID,
	   Geo.node[nodeID].num_connect_node);
    
    for(int next_node = 0; next_node < Geo.node[nodeID].num_connect_node; next_node++){
      printf("%d\t",Geo.node[nodeID].connect_node[next_node]);
    }
    printf("\n");
  }


  for(int arcID = 0; arcID < Geo.num_arc; arcID++){ 
    for(int sideID = 0; sideID < NUM_SIDE; sideID++){
      
      printf("arc:%d side:%d\t",arcID,sideID);

      printf("start:%d ",Geo.arc[arcID].block_start_node[sideID]);
      printf("end:%d\t",Geo.arc[arcID].block_end_node[sideID]);     
      printf("block:%d",Geo.arc[arcID].num_block); 

      printf("\n");
    }
  }


  
}


#endif //READFILE_H
