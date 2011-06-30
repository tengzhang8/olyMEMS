//Base Station
//File: gui.h
//Implements high level functions in controlling the GUI on the graphics LCD
//Copyright C. Au and T. Zhang, 2010

/*
int prev_menu_option = 1;
int lift_select = 0;
int weight_select = 0;
int connect_screen = 0;
int summary_screen = 0;
int acc_screen = 0;
int temp = 0;
int temp2 = 0;
char msg[50];
*/

// program states
#define WELCOME_SCR				0
#define MAIN_MENU				1
#define OPTIONS					2
#define WEIGHT_SEL				3
#define CONNECT_SCR				5
#define DATA_COLLECTED			7
#define SUMMARY_SCR				6
#define GRAPH_SELECT			8
#define ACC_GRAPH				9
#define VEL_GRAPH				10
#define PC_MODE					11




// encoder functions
void encoder_logic(void);
void init_encoders(void);
void init_switches(void);

// menu functions
void LoadBitmap(unsigned char *bitmap); // by scienceprog
void welcome_screen(void);
//void update_menu(int back);
void update_encoder(double max, uint8_t pgm_state);
void main_menu_setup(void);
int weight_menu_setup(void);
void connect_setup(uint8_t pgm_state);
//void connect_setup();
void summary_setup(float max_acc, float max_vel);
void graph_setup(double max);
void graph_scroll(double max, char direction);

// string functions
char *reverse(char *input);
void display_message(char fontnum,char co_ord_x, char co_ord_y,char *input);


//void check_time(int timer);



volatile double datatest[500];
