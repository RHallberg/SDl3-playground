#define SDL_MAIN_USE_CALLBACKS 1  /* use the callbacks instead of main() */
#include <stdlib.h>
#include <SDL3/SDL.h>
#include <SDL3/SDL_main.h>

#define OUTLINE_SIZE 5

/* We will use this renderer to draw into this window every frame. */
static SDL_Window *window = NULL;
static SDL_Renderer *renderer = NULL;
typedef struct {
    int x;
    int y;
} MousePos;
MousePos mpos = {0, 0};
typedef struct {
  unsigned char r;
  unsigned char g;
  unsigned char b;
  unsigned char a;
} Clr;

void cycleClr(Clr *clr)
{

  int rng = rand() % 3 + 1;
  int crng = rand() % 5 + 1;

  switch(rng)
  {
    case 1:
      clr->r = clr->r + crng;
      break;
    case 2:
      clr->g = clr->g + crng;
      break;
    case 3:
      clr->b = clr->b + crng;
      break;
  }
}

Clr color = {1,1,1,255};

/* This function runs once at startup. */
SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
    SDL_SetAppMetadata("Test for menus", "1.0", "com.testing.menu");

    if (!SDL_Init(SDL_INIT_VIDEO)) {
        SDL_Log("Couldn't initialize SDL: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    if (!SDL_CreateWindowAndRenderer("examples/renderer/lines", 640, 480, SDL_WINDOW_RESIZABLE, &window, &renderer)) {
        SDL_Log("Couldn't create window/renderer: %s", SDL_GetError());
        return SDL_APP_FAILURE;
    }

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs when a new event (mouse input, keypresses, etc) occurs. */
SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
    if (event->type == SDL_EVENT_QUIT || (event->type == SDL_EVENT_KEY_DOWN && event->key.key == SDLK_Q)) {
        return SDL_APP_SUCCESS;  /* end the program, reporting success to the OS. */
    }
    else if(event->type == SDL_EVENT_MOUSE_MOTION){
      mpos.x = event->motion.x;
      mpos.y = event->motion.y;
      cycleClr(&color);
    }
    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once per frame, and is the heart of the program. */
SDL_AppResult SDL_AppIterate(void *appstate)
{

    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(renderer);  /* start with a blank canvas. */

    int w_w;
    int w_h;
    SDL_GetWindowSize(window, &w_w, &w_h);

    SDL_FRect rect = {(w_w/2.0)-250,w_h/2.0,500,200};

    if(rect.x <= mpos.x && mpos.x <= rect.x + rect.w && rect.y <= mpos.y && mpos.y <= rect.y + rect.h){
      SDL_FRect outline = {
          rect.x - OUTLINE_SIZE,
          rect.y - OUTLINE_SIZE,
          rect.w + OUTLINE_SIZE * 2,
          rect.h + OUTLINE_SIZE * 2
      };
      SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
      SDL_RenderFillRect(renderer, &outline);

    }
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, SDL_ALPHA_OPAQUE);
    SDL_RenderFillRect(renderer, &rect);
    SDL_RenderPresent(renderer);

    return SDL_APP_CONTINUE;  /* carry on with the program! */
}

/* This function runs once at shutdown. */
void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
    /* SDL will clean up the window/renderer for us. */
}
