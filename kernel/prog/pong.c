/*
 * PONG!
*/

#include "pong.h"
#include "kernel.h"
#include "console.h"
#include "keyboard.h"
#include "time.h"

typedef struct paddle {
  unsigned int x, y;
  unsigned int width, height;
} paddle_t;

typedef struct player {
  unsigned char number;
  unsigned int score;
  paddle_t paddle;
} player_t;

typedef struct ball {
  unsigned int x, y;
  int x_vel, y_vel;
} ball_t;

static player_t player1, player2;
static ball_t ball;

static uint8_t playing = 0;

static void init_game(void) {

  ksetcursorxy(255, 255);

  player_t t1 = { 
    .number = 1,
    .score = 0,
    .paddle = {
      .x = 2,
      .y = 1,
      .width = 1,
      .height = 5,
    }
  };

  player_t t2 = { 
    .number = 2,
    .score = 0,
    .paddle = {
      .x = 77,
      .y = 1,
      .width = 1,
      .height = 5,
    }
  };

  player1 = t1;
  player2 = t2;
  
  ball_t tb = {
    .x = 40,
    .y = 13,
    .x_vel = -1,
    .y_vel = 1
  };

  ball = tb;

  kclear();
}

void draw_board(unsigned ticks) {
  if(ticks % 100 || !playing) {
    return;
  }  

  for(unsigned int i = 0; i < 80; ++i) {
    kputcxy('#', i, 0);
  }

  for(unsigned int i = 0; i < 80; ++i) {
    kputcxy('#', i, 24);
  }

  for(unsigned int i = 1; i < 24; ++i) {
    kputcxy('#', 0, i);
    for(unsigned int j = 1; j < 79; ++j) {
      kputcxy(' ', j, i);
    }
    kputcxy('#', 79, i);
  }

  // player 1 paddle
  for(unsigned int i = 0; i < player1.paddle.height; ++i) {
    for(unsigned int j = 0; j < player1.paddle.width; ++j) {
      kputcxy('|', player1.paddle.x + j, player1.paddle.y + i);
    }
  }

  // player 2 paddle
  for(unsigned int i = 0; i < player2.paddle.height; ++i) {
    for(unsigned int j = 0; j < player2.paddle.width; ++j) {
      kputcxy('|', player2.paddle.x + j, player2.paddle.y + i);
    }
  }

  kputcxy('O', ball.x, ball.y); 
}

void update_game(unsigned ticks) {
  if(ticks % 50 || !playing) {
    return;
  }
  
  if(ticks % 400 == 0) {
    ball.x = (unsigned int)((int)ball.x + ball.x_vel);
    ball.y = (unsigned int)((int)ball.y + ball.y_vel);
  }


  // scoring
  if(ball.x <= 1) {
    player2.score++;
    ball.x = 40;
  } else if(ball.x >= 79) {
    player1.score++;
    ball.x = 40;
  }

  // collision detection
  if(ball.x == player1.paddle.x && ball.y >= player1.paddle.y && ball.y <= player1.paddle.y + player1.paddle.height) {
    ball.x = player1.paddle.x + 1;
    ball.x_vel = -ball.x_vel;
  } else if(ball.x == player2.paddle.x && ball.y >= player2.paddle.y && ball.y <= player2.paddle.y + player2.paddle.height) {
    ball.x = player2.paddle.x - 1;
    ball.x_vel = -ball.x_vel;
  }

  if(ball.y < 1) {
    ball.y = 1;
    ball.y_vel = -ball.y_vel;
  } else if(ball.y > 23) {
    ball.y = 23;
    ball.y_vel = -ball.y_vel;
  }
  
  // cpu move
  if(ticks % 500 == 0) {
    if(player2.paddle.y < ball.y) {
      player2.paddle.y += 1;
    } else if(player2.paddle.y > ball.y) {
      player2.paddle.y -= 1;
    }

    if(player2.paddle.y <= 1) {
      player2.paddle.y = 1;
    } else if(player2.paddle.y + player2.paddle.height > 24) {
      player2.paddle.y = 24 - player2.paddle.height;
    }
  }

  unsigned char key = poll_key();

  if(key != 0) {
    if(key == KEY_UP) {
      player1.paddle.y -= 1;
      if(player1.paddle.y <= 1) {
        player1.paddle.y = 1;
      }
    }
    else if(key == KEY_DOWN) {
      player1.paddle.y += 1;
      if(player1.paddle.y + player1.paddle.height > 24) {
        player1.paddle.y = 24 - player1.paddle.height;
      }
    }

    else if(key == 'q') {
      playing = 0;
    }    
  }
}

void pong(void) {
  init_game();

  playing = true;

  while(playing) {
    unsigned ticks = get_ticks();

    while((ticks = get_ticks()) % 100) {}

    update_game(ticks);
    draw_board(ticks);
  }
  
  kclear();
  ksetcursorxy(0, 0);
  kputs("GAME OVER.\n\tFinal Score: player (");
  kputnum((int)player1.score, 10);
  kputs("), CPU (");
  kputnum((int)player2.score, 10);
  kputs(")\n");

  __asm__("cli;hlt");

  return;
}
