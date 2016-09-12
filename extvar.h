 /*-*-c++-*-*/
//
//  extvar.h
//
//  Header file for Definision of Variables
//

#ifndef EXTVAR_H
#define EXTVAR_H


//--------------------------------------------------------------------------//
//-- External Fixed Parameters

#define MAX_VALUE              999999999.0

#define TRUE                   1
#define FALSE                  0

#define ON                     1
#define OFF                    0

#define STANDBY                3
#define WAITING                2
#define ARRIVAL                1
#define DRIVING                0

#define MAX_FRAME_SIZE         600
#define MIN_FRAME_SIZE         300

#define MAX_NODE               300
#define MAX_ARC                700
#define MAX_MOVE               30000
#define MAX_BLOCK              150
#define MAX_CROSS              10

#define MAX_NUM_WAITING        150

#define NUM_SIDE               2
#define UPTOWN                 0     //
#define DOWNTOWN               1     //

#define MAX_STEP               30000

#define TIME_UNIT              10
#define LENGTH_UNIT            10

#define ROUND_TRIP             2
#define OUTWARD                0
#define HOMEWARD               1

#define COINCIDENCE            0

#define NUM_CHART              3
#define MAX_CHART_FACTOR       10

#define NAVI_TYPE              5
#define NUM_AVERAGE            6

#define SHORTEST_DISTANCE      0
#define REPLANNING_ORIGIN      1
#define SUCCESSIVE_REPLANNING  2
#define CONGESTION_AVOIDANCE   3
#define DECLARING_PATH         4
#define ALL_AVERAGE            5

#define IDEAL_DISTANCE         6
#define IDEAL_TIME             7

#define NOT_JAM                0
#define JAM                    1




//--------------------------------------------------------------------------//
//-- External Variables for Map and Object


//-- Frame Size
struct FRAME_SIZE{
    int width;
    int height;
};

//-- Map Information

struct MAP_BLOCK{
    double K;            /* density of block */
    double K_saturation;
    double K_critical;
    
    double ave_K;
    
    int block_num_generated;
    
    int block_num_move;
    int block_move[50];
    
    int block_num_wait;
    int block_wait[MAX_NUM_WAITING];
    
    int traffic_status;  /*JAM or NOT_JAM*/
    
    double block_length;
    double velocity;
    double ideal_velocity;
    
};

struct GEO_INFO{
    
    //-- NODE
    struct MAP_NODE{
        int no;          /* 番号             */
        int x;           /* Ｘ座標           */
        int y;           /* Ｙ座標           */
        
        //int *connect_node;   /* つながっているノードの番号 */
        int connect_node[MAX_CROSS];  /* つながっているノードの番号 */
        int num_connect_node;         /* つながっているノードの数 */
        
        //int *connect_arc;    /* つながっているアークの番号 */
        int connect_arc[MAX_CROSS];   /* つながっているアークの番号 */
        int num_connect_arc;          /* つながっているアークの数 */
    };
    struct MAP_NODE node[MAX_NODE];
    
    int num_node;
    
    
    //-- ARC
    struct MAP_ARC{
        int    no;         /* number of the arc */
        int    start;      /* アークの始点のノード番号 */
        int    end;        /* アークの終点のノード番号 */
        int    length;     /* 距離             */
        double distance;   /* 道程             */
        double weight;     /* 重み             */
        
        MAP_BLOCK block[NUM_SIDE][MAX_BLOCK];
        int    num_block;
        double unit_block;
        
        int    block_start_node[NUM_SIDE];
        int    block_end_node[NUM_SIDE];
    };
    struct MAP_ARC arc[MAX_ARC];
    
    int num_arc;
    
    
    double Adjacency[MAX_NODE][MAX_NODE];              /* 隣接行列           */
    double ExpectedTravelTime[MAX_NODE][MAX_NODE];     /* 予想移動時間行列    */
    double IdealTravelTime[MAX_NODE][MAX_NODE];        /* 理想移動時間行列    */
    double CongestionAvoidance[MAX_NODE][MAX_NODE];    /* 混雑回避行列       */
    double DeclaredPlan[MAX_NODE][MAX_NODE];           /* 予告経路行列       */
    
    int    BOOL_Adjacency[MAX_NODE][MAX_NODE];         /* 隣接行列 パス有 1 パス無 0  */
    
};


//--------------------------------------------------------------------------//
//-- Object
struct OBJECTS{
    struct MOVING_OBJECT{
        int     no;          /* 移動体の番号        */
        
        int    origin;            /* 移動体の出発地ノード      */
        int    destination;       /* 移動体の目的地ノード      */
        
        int    origin_arc;        /* 移動体の出発地アーク      */
        int    origin_side;       /* 移動体の出発地サイド      */
        int    origin_block;      /* 移動体の出発地ブロック    */
        
        int    destination_arc;   /* 移動体の目的地アーク      */
        int    destination_side;  /* 移動体の目的地サイド      */
        int    destination_block; /* 移動体の目的地ブロック    */
        
        int    arc;               /* 現在位置のアーク番号 */
        int    side;              /* 現在位置のサイド番号 */
        int    block;             /* 現在位置のブロック番号 */
        
        int    end;               /* 現在位置のアークの進行方向のノード番号      */
        int    start;             /* 現在位置のアークの進行方向と反対のノード番号 */
        double distance;          /* 進行方向の反対のノードからの距離 */
        
        //int order_in_block;  /* ブロックの中での順番 */
        
        int    choice_node;       /* 現在位置から移動を希望するノード */
        int    choice_arc;        /* 現在位置から移動を希望するアーク */
        
        double velocity;          /* 移動体の速度        */
        
        int    generation_step;   /* 車両発生のステップ数    */
        int    start_step;        /* 車両走行開始のステップ数 */
        int    arrival_step;      /* 目的地到着のステップ数  */
        
        int    travel_plan[MAX_NODE];            /* 移動計画           */
        int    travel_plan_length;               /* 移動計画の長さ      */
        
        int    ideal_plan[ROUND_TRIP][MAX_NODE]; /* 理想移動計画        */
        int    ideal_plan_length[ROUND_TRIP];    /* 理想移動計画の長さ   */
        
        int    actual_plan[MAX_NODE]; /* 実際の移動経路        */
        int    actual_plan_length;    /* 実際の移動経路の長さ   */
        
        int    plan[ROUND_TRIP][MAX_NODE];   /* 移動計画           */
        int    plan_length[ROUND_TRIP];      /* 移動計画の長さ      */
        int    plan_progress;                /* 移動計画の進捗度    */
        int    plan_direction;               /* 移動計画の往路or復路 */
        
        
        double gain;                         /* 前進した距離       */
        int    num_arrival[ROUND_TRIP];      /* 目的地への到着回数  */
        
        int    required_time[ROUND_TRIP];           /* 出発地⇔目的地の所要時間 */
        int    last_required_time;                  /* 前回の出発地→目的地の所要時間 */
        
        double required_distance[ROUND_TRIP];       /* 出発地⇔目的地の所要距離 */
        double last_required_distance;              /* 前回の出発地→目的地の所要距離 */
        
        double ideal_required_time[ROUND_TRIP];     /* 出発地⇔目的地の理想所要時間 */
        double ideal_required_distance[ROUND_TRIP]; /* 出発地⇔目的地の理想所要距離 */
        
        double last_ideal_required_time;            /* 前回の出発地⇔目的地の理想所要時間 */
        double last_ideal_required_distance;        /* 前回の出発地⇔目的地の理想所要距離 */
        
        double efficiency_time;                     /* 出発地⇔目的地の所要時間/理想所要時間 */
        double efficiency_distance;                 /* 出発地⇔目的地の所要時間/理想所要距離 */
        double present_efficiency_time;             /* 出発地⇔目的地の所要時間/理想所要時間 */
        double present_efficiency_distance;         /* 出発地⇔目的地の所要時間/理想所要距離 */
        
        int    navi_type;                           /* ナビゲーションから提供される情報の種類         */
        int    flag_move_new_block;                 /* 現在のブロックから新しいブロックへの移動の有無  */
        int    flag_move_turn;                      /* 移動の機会の有無                            */
        int    flag_stop;                           /* 前進の有無                                 */
        
        int    arrival;
        int    driving_status;                      /* STANDBY(出発前) WAITING(出発準備中) DRIVING(運転中) ARRIVAL(到着後) のどれか*/
        
        
        
    };
    struct MOVING_OBJECT move[MAX_MOVE];
    
    int    num_move;                               /* 現在の移動体数        */
    int    Max_Obj;                                /* 最大移動体数          */
    int    num_navi_type[NUM_AVERAGE];             /* 移動体の用いる経路決定アルゴリズムのの種類     */
    int    num_generation;                         /* 1ステップでの車両発生数 */
    
    int    num_standby[NUM_AVERAGE];
    int    num_driving[NUM_AVERAGE];
    int    num_waiting[NUM_AVERAGE];

    int    num_arrival[NUM_AVERAGE   ];
    
    
    double ratio_ShortestDistance;
                    ratio_ReplanningInOrigin;
    double ratio_SuccessiveReplanning;
    double ratio_CongestionAvoidance;
    double ratio_DeclaringPath;
    
    int    num_ShortestDistance;
    int    num_ReplanningInOrigin;
    int    num_SuccessiveReplanning;
    int    num_CongestionAvoidance;
    int    num_DeclaringPath;
    
    int    present_num_ShortestDistance;
    int    present_num_ReplanningInOrigin;
    int    present_num_SuccessiveReplanning;
    int    present_num_CongestionAvoidance;
    int    present_num_DeclaringPath;
    
    int    generate_num_SD;
    int    generate_num_RO;
    int    generate_num_SR;
    int    generate_num_CA;
    int    generate_num_DP;
    
    
};


//--------------------------------------------------------------------------//
//-- Macro Parameter
struct MACRO_PARAMETER{
    
    double ave_gain[NUM_AVERAGE];                              /* 平均移動距離           */
    double ave_num_stop[NUM_AVERAGE];                          /* 前進できなかった移動体数 */
    double ave_num_arrival[NUM_AVERAGE];                       /* 目的地への平均到着回数  */
    double ave_velocity[NUM_AVERAGE];                          /* 平均速度              */
    double ave_required_time[NUM_AVERAGE];                     /* 目的地への平均所要時間  */
    double ave_required_distance[NUM_AVERAGE];                 /* 目的地への平均所要距離  */
    double ave_present_required_time[NUM_AVERAGE];             /* 目的地への現在の平均所要時間 */
    double ave_present_required_distance[NUM_AVERAGE];         /* 目的地への現在の平均所要距離 */
    double ave_ideal_required_time[NUM_AVERAGE];               /* 目的地への理想所要時間 */
    double ave_ideal_required_distance[NUM_AVERAGE];           /* 目的地への理想所要距離 */
    
    double ave_efficiency_time[NUM_AVERAGE];                   /* 出発地⇔目的地の所要時間/理想所要時間 */
    double ave_efficiency_distance[NUM_AVERAGE];               /* 出発地⇔目的地の所要時間/理想所要距離 */
    double ave_present_efficiency_time[NUM_AVERAGE];           /* 出発地⇔目的地の現在の所要時間/理想所要時間 */
    double ave_present_efficiency_distance[NUM_AVERAGE];       /* 出発地⇔目的地の現在の所要時間/理想所要距離 */
    
    double variance_efficiency_time[NUM_AVERAGE];              /* 出発地⇔目的地の所要時間/理想所要時間 */
    
    
    double ave_gain_trial[NUM_AVERAGE];                        /* 平均移動距離         */
    double ave_num_stop_trial[NUM_AVERAGE];                    /* 前進できなかった移動体数 */
    double ave_num_arrival_trial[NUM_AVERAGE];                 /* 目的地への平均到着回数 */
    double ave_velocity_trial[NUM_AVERAGE];                    /* 平均速度             */
    double ave_required_time_trial[NUM_AVERAGE];               /* 目的地への平均所要時間 */
    double ave_required_distance_trial[NUM_AVERAGE];           /* 目的地への平均所要距離 */
    double ave_present_required_time_trial[NUM_AVERAGE];       /* 目的地への現在の平均所要時間 */
    double ave_present_required_distance_trial[NUM_AVERAGE];   /* 目的地への現在の平均所要距離 */
    double ave_ideal_required_time_trial[NUM_AVERAGE];         /* 目的地への理想平均所要時間 */
    double ave_ideal_required_distance_trial[NUM_AVERAGE];     /* 目的地への理想平均所要距離 */
    
    double ave_efficiency_time_trial[NUM_AVERAGE];             /* 出発地⇔目的地の所要時間/理想所要時間 */
    double ave_efficiency_distance_trial[NUM_AVERAGE];         /* 出発地⇔目的地の所要時間/理想所要距離 */
    double ave_present_efficiency_time_trial[NUM_AVERAGE];     /* 出発地⇔目的地の所要時間/現在の理想所要時間 */
    double ave_present_efficiency_distance_trial[NUM_AVERAGE]; /* 出発地⇔目的地の所要時間/現在の理想所要距離 */
    
    double ave_variance_efficiency_time_trial[NUM_AVERAGE];              /* 出発地⇔目的地の所要時間/理想所要時間 */
    
};

//--------------------------------------------------------------------------//
//-- Chart
struct CHART{
    
    int    num_factor[NUM_CHART];
    double chart_factor[NUM_CHART][MAX_CHART_FACTOR][MAX_STEP]; 
    
};

//--------------------------------------------------------------------------//
//-- Simulation Control
struct ITERATION_CONTROL{
    int start;
    int pause;
    int restart;
    int exit;
    
    int drawing;
    int simulation;
    
    int step;
    int Max_Step;
    
    int auto_start;      
    int graphics_switch;  
    int chart_switch;  
    int delete_graphics;  
    
    
};

//--------------------------------------------------------------------------//
//-- Window Settings
struct WINDOW_SIZE{
    
    int display_text_margin_y; 
    int button_margin_y;       
    
    int graphics_height;         
    int graphics_width;        
    int chart_width;           
};




#endif //EXTVAR_H