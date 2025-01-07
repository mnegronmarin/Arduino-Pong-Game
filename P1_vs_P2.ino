#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// Define button pins for P1
#define UP_BUTTON1 13
#define DOWN_BUTTON1 12
// Define button pins for P2
#define UP_BUTTON2 2
#define DOWN_BUTTON2 3

// Define paddle and ball parameters
unsigned long PADDLE_RATE = 30;
float BALL_RATE = 20;
const uint8_t PADDLE_HEIGHT = 20;
const int MAX_SCORE = 3;

int PLAYER1_SCORE = 0;
int PLAYER2_SCORE = 0;

// Define buzzer pin
#define BUZZER_PIN 8

// Define OLED dimensions
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

// Initialize OLED display with I2C
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void drawCourt();
void displayScore();
void resetGame();
void playHitSound();
void playScoreSound(bool playerScored);
void playVictorySound();
void endGame(bool playerWon);

uint8_t ball_x = 64, ball_y = 32;
uint8_t ball_dir_x = 1, ball_dir_y = 1;
unsigned long ball_update;

unsigned long paddle1_update;
unsigned long paddle2_update;
const uint8_t P1_X = 12;
uint8_t p1_y = 22;

const uint8_t P2_X = 115;
uint8_t p2_y = 22;

bool nearEndGame = false;

void setup() {
  // Initialize Serial for debugging
  Serial.begin(115200);

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (1); // Halt if initialization fails
  }

  // Initialize buzzer
  pinMode(BUZZER_PIN, OUTPUT);

  // Display splash screen
  display.display();
  delay(2000);

  // Clear display and set up court
  display.clearDisplay();
  drawCourt();
  displayScore();
  display.display();

  // Initialize buttons
  pinMode(UP_BUTTON1, INPUT_PULLUP);
  pinMode(DOWN_BUTTON1, INPUT_PULLUP);

  pinMode(UP_BUTTON2, INPUT_PULLUP);
  pinMode(DOWN_BUTTON2, INPUT_PULLUP);

  ball_update = millis();
  paddle1_update = ball_update;
  paddle2_update = ball_update;
}

void loop() {

  bool update = false;
  unsigned long time = millis();

   // Continuously play background music

  static bool up_state1 = false;
  static bool down_state1 = false;

  static bool up_state2 = false;
  static bool down_state2 = false;

  // Read button states
  up_state1 |= (digitalRead(UP_BUTTON1) == LOW);
  down_state1 |= (digitalRead(DOWN_BUTTON1) == LOW);

  up_state2 |= (digitalRead(UP_BUTTON2) == LOW);
  down_state2 |= (digitalRead(DOWN_BUTTON2) == LOW);

  // Update ball position based on BALL_RATE
  if (time > ball_update + BALL_RATE) {
    ball_update = time; // Reset ball update timer

    uint8_t new_x = ball_x + ball_dir_x;
    uint8_t new_y = ball_y + ball_dir_y;

    // Check if we hit the vertical walls
    if (new_y == 0 || new_y == 63) {
      ball_dir_y = -ball_dir_y;
      new_y += ball_dir_y + ball_dir_y;
    }

    // Check if player 1 misses the ball
    if (new_x == 0) {
      PLAYER2_SCORE++; // increase

      if (PLAYER2_SCORE == MAX_SCORE - 1) {
        nearEndGame = true;
      } 
      if (PLAYER2_SCORE < MAX_SCORE - 1) {
        if(!nearEndGame) nearEndGame = false;
      }

      if (PLAYER2_SCORE < MAX_SCORE) {
        playScoreSound(true);
      }
      display.clearDisplay();
      drawCourt();
      if (PLAYER2_SCORE == MAX_SCORE) {
        playVictorySound();
        endGame(true);
        return;
      }
      resetGame();
      return;
    }

    // Check if player 2 misses the ball
    if (new_x == 127) {
      PLAYER1_SCORE++;

      // nearEndGame logic 
      if (PLAYER1_SCORE == MAX_SCORE - 1) {
        nearEndGame = true;
      } 
      if (PLAYER1_SCORE < MAX_SCORE - 1) {
        if(!nearEndGame) nearEndGame = false;
      }

      // Scoring and sound logic
      if (PLAYER1_SCORE < MAX_SCORE) {
        playScoreSound(true);
      }
      display.clearDisplay();
      drawCourt();
      if (PLAYER1_SCORE == MAX_SCORE) {
        playVictorySound();
        endGame(false);
        return;
      }
      resetGame();
      return;
    }
    // Check if we hit the top player 1 paddle
    if (new_x == P1_X && new_y >= p1_y && new_y <= p1_y + PADDLE_HEIGHT/2) {
      ball_dir_x = -ball_dir_x;
      new_x += ball_dir_x + ball_dir_x;
      
      playHitSound();
    }

    // Check if we hit the bottom CPU paddle
    if (new_x == P1_X && new_y > p1_y + PADDLE_HEIGHT / 2 && new_y <= p1_y + PADDLE_HEIGHT) {
      ball_dir_x = -ball_dir_x;
      new_x += ball_dir_x + ball_dir_x;
      ball_dir_y = -ball_dir_y;
      playHitSound();
    }

    // Check if we hit the top player paddle
    if (new_x == P2_X && new_y >= p2_y && new_y <= p2_y + PADDLE_HEIGHT/2) {
      ball_dir_x = -ball_dir_x;
      new_x += ball_dir_x + ball_dir_x;
      playHitSound();
    }
    
    // Check if we hit the bottom player paddle
    if (new_x == P2_X && new_y > p2_y + PADDLE_HEIGHT / 2 && new_y <= p2_y + PADDLE_HEIGHT) {
      ball_dir_x = -ball_dir_x;
      new_x += ball_dir_x + ball_dir_x;
      ball_dir_y = -ball_dir_y;
      playHitSound();
    }

    // Update ball position
    
    display.drawPixel(ball_x, ball_y, BLACK);
    display.drawPixel(new_x, new_y, WHITE);
    ball_x = new_x;      
    ball_y = new_y;

    update = true;
  }

  if (time > paddle2_update) {
    paddle2_update += PADDLE_RATE;
    paddle1_update += PADDLE_RATE;

    // Update player 2 paddle
    display.drawFastVLine(P2_X, p2_y, PADDLE_HEIGHT, BLACK);
    if (up_state2) p2_y -= 1;
    if (down_state2) p2_y += 1;
    up_state2 = down_state2 = false;
    if (p2_y < 1) p2_y = 1;
    if (p2_y + PADDLE_HEIGHT > 63) p2_y = 63 - PADDLE_HEIGHT;
    display.drawFastVLine(P2_X, p2_y, PADDLE_HEIGHT, WHITE);

    update = true;
  }

  // update player 1 paddle
  if (time > paddle1_update) {
    display.drawFastVLine(P1_X, p1_y, PADDLE_HEIGHT, BLACK);
    if (up_state1) p1_y -= 1;
    if (down_state1) p1_y += 1;
    up_state1 = down_state1 = false;
    if (p1_y < 1) p1_y = 1;
    if (p1_y + PADDLE_HEIGHT > 63) p1_y = 63 - PADDLE_HEIGHT;
    display.drawFastVLine(P1_X, p1_y, PADDLE_HEIGHT, WHITE);

    update = true;
  }

  if (update) {
    display.display();
    displayScore();
  }
}

// Method which draws the court (white rectangle around edge)
void drawCourt() {
  display.drawRect(0, 0, 128, 64, WHITE); // Draw court boundary
}

// Method which displays the game score 
void displayScore() {
  display.setCursor(5, 5);
  display.setTextSize(1);
  display.setTextColor(WHITE, BLACK);
  display.print("P1: ");
  display.print(PLAYER1_SCORE);
  display.print("  P2: ");
  display.print(PLAYER2_SCORE);
}

// Method to reset game
void resetGame() {
  ball_x = 64;
  ball_y = 32;
  ball_dir_x = 1;
  ball_dir_y = 1;
  drawCourt();
  displayScore();
  display.display();
}

// Method for when ball hits
void playHitSound() {
  tone(BUZZER_PIN, 1000, 100); // Play a 1kHz tone for 100ms
}

// Method for wwhen someone scores
void playScoreSound(bool playerScored) {
    tone(BUZZER_PIN, 1500, 300); // Higher pitch for player score
    delay(300);
    tone(BUZZER_PIN, 2000, 300);
}

// Method for victory sound
void playVictorySound() {
  tone(BUZZER_PIN, 2000, 500); // Long high-pitch tone for victory
  delay(500);
  tone(BUZZER_PIN, 2500, 500);
  delay(500);
  tone(BUZZER_PIN, 3000, 500);
}

void endGame(bool playerWon) {
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(10, 20);
  if (playerWon) {
    playVictorySound();
    display.print("P2 WON!");
  } else {
    display.print("P1 WON!");
  }
  display.display();
  delay(5000);
  PLAYER2_SCORE = 0;
  PLAYER1_SCORE = 0;
  resetGame();
  display.clearDisplay();
  drawCourt();
}
