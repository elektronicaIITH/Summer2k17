#include <MaxMatrix.h>
#include <Keypad.h>

int DIN = 50;   // DIN pin of MAX7219 module
int CS = 48;    // CS pin of MAX7219 module
int CLK = 46;   // CLK pin of MAX7219 module
int maxInUse = 9;
const byte ROWS = 4; //four rows
const byte COLS = 4; //four columns

char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

byte rowPins[ROWS] = {2,3,4,5}; //connect to the row pinouts of the keypad'black'
byte colPins[COLS] = {6,7,8,9}; //connect to the column pinouts of the keypad'white'

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, ROWS, COLS);

MaxMatrix m(DIN, CS, CLK, maxInUse);
byte clr[] = {8,8,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000,
    B00000000};
byte X[] = { 8,8,
    B10000001,
    B01000010,
    B00100100,
    B00011000,
    B00011000,
    B00100100,
    B01000010,
    B10000001};
byte O[] = {8,8,
    B00011000,
    B00100100,
    B01000010,
    B10000001,
    B10000001,
    B01000010,
    B00100100,
    B00011000};
byte T1[] = { 8,8,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B00011000,
  B11111111,
  B11111111};
byte T2[] = {8,8,
    B11111111,
    B11111111,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00011000};
byte I0[] = { 8,8,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B00011000};
byte A[] = { 8,8,
    B01111110,
    B11111111,
    B11000011,
    B11000011,
    B11111111,
    B11111111,
    B11000011,
    B11000011};
byte I1[] = { 8,8,
    B11111111,
    B11111111,
    B00011000,
    B00011000,
    B00011000,
    B00011000,
    B11111111,
    B11111111};
byte C2[] = { 8,8,
    B00111110,
    B01111110,
    B11000000,
    B11000000,
    B11000000,
    B11000000,
    B01111110,
    B00111110};
byte C1[] = {8,8,
    B01111100,
    B01111110,
    B00000011,
    B00000011,
    B00000011,
    B00000011,
    B01111110,
    B01111100};
byte E[] = { 8,8,
    B11111111,
    B11111111,
    B00000011,
    B01111111,
    B01111111,
    B00000011,
    B11111111,
    B11111111};

void welcome(){
    m.writeSprite(0*8,0,T1);
    m.writeSprite(1*8,0,I1);
    m.writeSprite(2*8,0,C1);
    m.writeSprite(3*8,0,C2);
    m.writeSprite(4*8,0,A);
    m.writeSprite(5*8,0,T2);
    m.writeSprite(6*8,0,T1);
    m.writeSprite(7*8,0,O);
    m.writeSprite(8*8,0,E);
}

void SetX(int p){
    int q;
    if(p==0){
      q = 0;
    }else if(p==1){
      q = 1;
    }else if(p==2){
      q = 2;
    }else if(p==3){
      q = 5;
    }else if(p==4){
      q = 4;
    }else if(p==5){
      q = 3;
    }else if(p==6){
      q = 6;
    }else if(p==7){
      q = 7;
    }else if(p==8){
      q = 8;
    }
    m.writeSprite(8*(q),0,X);
}

void SetO(int p){
    
    int q;
    if(p==0){
      q = 0;
    }else if(p==1){
      q = 1;
    }else if(p==2){
      q = 2;
    }else if(p==3){
      q = 5;
    }else if(p==4){
      q = 4;
    }else if(p==5){
      q = 3;
    }else if(p==6){
      q = 6;
    }else if(p==7){
      q = 7;
    }else if(p==8){
      q = 8;
    }
    m.writeSprite(8*(q),0,O);
}

void Setclr(){
    for(int i = 0;i<9;i++){
        m.writeSprite(i*8,0,clr);
    }
}

int flag=0;

void play(int key){
    if(key< '1' || key > '9'){
        if(key == 'A'){
            Setclr();
            flag = 0;
        }
    }else{
        key = key - '0';
        if(flag%2 == 0){
            SetX(key);
        }else{
            SetO(key);
        }
        flag++;
    }
}

int win(const int board[9]) {
    //determines if a player has won, returns 0 otherwise.
    unsigned wins[8][3] = {{0,1,2},{3,4,5},{6,7,8},{0,3,6},{1,4,7},{2,5,8},{0,4,8},{2,4,6}};
    int i;
    for(i = 0; i < 8; ++i) {
        if(board[wins[i][0]] != 0 &&
           board[wins[i][0]] == board[wins[i][1]] &&
           board[wins[i][0]] == board[wins[i][2]])
            return board[wins[i][2]];
    }
    return 0;
}

int minimax(int board[9], int player) {
    //How is the position like for player (their turn) on board?
    int winner = win(board);
    if(winner != 0) return winner*player;

    int move = -1;
    int score = -2;//Losing moves are preferred to no move
    int i;
    for(i = 0; i < 9; ++i) {//For all moves,
        if(board[i] == 0) {//If legal,
            board[i] = player;//Try the move
            int thisScore = -minimax(board, player*-1);
            if(thisScore > score) {
                score = thisScore;
                move = i;
            }//Pick the one that's worst for the opponent
            board[i] = 0;//Reset board after try
        }
    }
    if(move == -1) return 0;
    return score;
}

int computerMove(int board[9]) {
  Serial.println("hihi");
    int move = -1;
    int score = -2;
    int i;
    for(i = 0; i < 9; ++i) {
      Serial.println("bla");
        if(board[i] == 0) {
            board[i] = 1;
            int tempScore = -minimax(board, -1);
            board[i] = 0;
            if(tempScore > score) {
                score = tempScore;
                move = i;
            }
        }
    }
    //returns a score based on minimax tree at a given node.
    Serial.println("hehe");
    board[move] = 1;
    return move;
}

int playerMove(int board[9]) {
    int move = 0;
    do {
        start:
        Serial.print("\nInput move ([0..8]): ");
        char key;
        while(1){
            key = keypad.getKey();
            if (key){
                Serial.println(key);
                int inkey = (int)key;
                inkey = inkey - '0' - 1;
                Serial.println(inkey);
                if(inkey >= 0 || inkey <= 8){
                    move = inkey;
                    break;
                }
            }
        };
        if(board[move] != 0) {
            Serial.print("Its Already Occupied !");
            goto start;
        }
        Serial.print("\n");
    }while (move >= 9 || move < 0 && board[move] == 0);
    board[move] = -1;
    return move;
}

int player1Move(int board[9]) {
    int move = 0;
    do {
        start:
        Serial.print("\nInput move ([0..8]): ");
        char key;
        while(1){
                key = keypad.getKey();
                if (key){
                    Serial.println(key);
                    int inkey = (int)key;
                    inkey = inkey - '0' - 1;
                    Serial.println(inkey);
                    if(inkey >= 0 || inkey <= 8){
                        move = inkey;
                        break;
                    }
                }
            };
        if(board[move] != 0) {
            Serial.print("Its Already Occupied !");
            goto start;
        }
        Serial.print("\n");
    } while (move >= 9 || move < 0 && board[move] == 0);
    board[move] = 1;
    return move;
}

int player2Move(int board[9]) {
    int move = 0;
    do {
            start:
            Serial.print("\nInput move ([0..8]): ");
            char key;
            while(1){
                    key = keypad.getKey();
                    if (key){
                        Serial.println(key);
                        int inkey = (int)key;
                        inkey = inkey - '0' - 1;
                        Serial.println(inkey);
                        if(inkey >= 0 || inkey <= 8){
                            move = inkey;
                            break;
                        }
                    }
                };
            if(board[move] != 0) {
            Serial.print("Its Already Occupied !");
            goto start;
    }
    Serial.print("\n");
    } while (move >= 9 || move < 0 && board[move] == 0);
            board[move] = -1;
    return move;
}

int gametime() {
        
    int board[9] = {0,0,0,0,0,0,0,0,0};
    //computer squares are 1, player squares are -1.
    // Serial.print("Computer: O, You: X\nPlay (1)st or (2)nd? ");
    Setclr();
    int player=0;
    char key;
    while(1){
        key = keypad.getKey();
        if (key) {
            Serial.println(key);
            int inkey = (int)key;
            inkey = inkey - '0';
            if(inkey == 1 || inkey == 2){
                player = inkey;
                break;
            }
        }
    }
    Serial.print("\n");
    Setclr();
    unsigned turn = 0;
    if (player == 2){
        board[0] = 1;
        SetX(0);
        turn++;
    }
    for(; turn < 9 && win(board) == 0; ++turn) {
        if((turn+player) % 2 == 0){
            SetX(computerMove(board));
        }else{
            SetO(playerMove(board));
        }
    }

    while(1){
        key = keypad.getKey();
        if (key){
            Serial.println(key);
            if(key == 'A'){
                Setclr();
                return 0; 
            }   
        }
    }
}

int multigame() {
  
    int board[9] = {0,0,0,0,0,0,0,0,0};
    // Serial.print(" Player1: X, Player2: O\nPlay ");
    Setclr();
    char key;
    Serial.print("\n");
    Setclr();
    Setclr();
    unsigned turn = 0;
    for(; turn < 9 && win(board) == 0; ++turn) {
        if((turn) % 2 != 0){ 
            SetO(player2Move(board));
        }else{
            SetX(player1Move(board));
        }
    }
    while(1){
        key = keypad.getKey();
        if (key){
            Serial.println(key);
            if(key == 'A'){
               Setclr();
               return 0; 
            }
        }
    }
} 

void setup() {
    
    int i;
    m.init(); // MAX7219 initialization
    m.setIntensity(12);   // initial led matrix intensity, 0-15
    for(i=2; i<=9; i++){
      pinMode(i, INPUT);
    }
    
    
    Serial.begin(9600);
}

void loop() {
    //  Seting the LEDs On or Off at x,y or row,column position
    welcome();
    
    while(1){
     welcome();
        char key = keypad.getKey();
        if (key=='1' || key == '2' ){
            // Serial.println(key);
            if(key == '1'){
               gametime();
            }else{
                multigame();
            }
        }
    }
}

