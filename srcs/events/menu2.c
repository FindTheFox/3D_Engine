#include "../../includes/3d_engine.h"

void    makebutton(t_env *env, char *quote, SDL_Rect buttonPos)
{
    SDL_Surface *text;
    SDL_Rect textPos;

    if(SDL_BlitSurface(env->menu.button, NULL, env->winsurf, &buttonPos) == -1)
        printf("error blitsurface");
    //Ecrire sur le button
    if(!(text = TTF_RenderText_Solid(env->menu.font, quote, (SDL_Color){255, 255, 255})))
           printf("%s\n", TTF_GetError());
    textPos.x = buttonPos.x + env->menu.button->w * 0.4;
    textPos.y = buttonPos.y + env->menu.button->h * 0.4;
    SDL_BlitSurface(text, NULL, env->winsurf, &textPos);
    SDL_FreeSurface(text);
}

void    WriteOnScreen(t_env *env, char* quote, SDL_Color textColor)
{
    SDL_Surface *text;

    if(!(text = TTF_RenderText_Solid(env->menu.font, quote, textColor)))
           printf("%s\n", TTF_GetError());
    SDL_BlitSurface(text, NULL, env->winsurf, &env->menu.textPos);
    SDL_FreeSurface(text);
}

void    main_menu(t_env *env)
{
    env->menu.textColor = (SDL_Color){0, 0, 0, 0};

    SDL_FillRect(env->winsurf, NULL, 0x00000000);
    if(SDL_BlitSurface(env->menu.menu1, NULL, env->winsurf, NULL) == -1)
        printf("error blitsurface");
    //Ecrire le RAGEQUIT
    env->menu.textPos.x = (env->winsurf->w / 2) - (env->menu.text->w / 2);
    env->menu.textPos.y = (env->winsurf->h - env->menu.text->h);
    WriteOnScreen(env, "ESC TO RAGEQUIT", env->menu.textColor);

    //affiche le button1
    env->menu.button1Pos.x = (env->winsurf->w / 2) - (env->menu.button->w) - BUTTON_MARGE;
    env->menu.button1Pos.y = env->menu.button2Pos.y = (env->winsurf->h - env->menu.button->h) * 0.99;
    makebutton(env, "PLAY", env->menu.button1Pos);
    
    //affiche le button2
    env->menu.button2Pos.x = (env->winsurf->w / 2) + BUTTON_MARGE;
    makebutton(env, "FORGE", env->menu.button2Pos);
}

void       pause_menu(t_env *env)
{
    SDL_FillRect(env->winsurf, NULL, 0x00000000);
    if(SDL_BlitSurface(env->menu.menu2, NULL, env->winsurf, NULL) == -1)
        printf("error blitsurface");

    env->menu.button1Pos.x = env->menu.button2Pos.x = (env->winsurf->w / 2 - env->menu.button->w) / 2;
    env->menu.button1Pos.y = (env->winsurf->h - BUTTON_MARGE) / 2 - env->menu.button->h;
    makebutton(env, "RESUME", env->menu.button1Pos);
            
    env->menu.button2Pos.y = (env->winsurf->h + BUTTON_MARGE) / 2;
    makebutton(env, "OPTIONS", env->menu.button2Pos);    
}

void    option_menu(t_env *env)
{
    SDL_Rect textPos;
    SDL_Surface *text;
    SDL_FillRect(env->winsurf, NULL, 0x00000000);
    if(SDL_BlitSurface(env->menu.menu3, NULL, env->winsurf, NULL) == -1)
        printf("error blitsurface");
    //if(!(text = TTF_RenderText_Solid(env->menu.font, "TEST", env->menu.textColor)))
    //       printf("%s\n", TTF_GetError());
 
    env->menu.textPos.x = 25;
    env->menu.textPos.y = ((env->winsurf->h - 140) / 8) - (env->menu.text->h / 2) + 40; //Blitage des définitions
    WriteOnScreen(env, "MOVE FORWARD", (SDL_Color){255, 255, 255});
    env->menu.textPos.y = ((env->winsurf->h - 140) / 8) + env->menu.text->h  + 40;
    WriteOnScreen(env, "MOVE BACKWARD", (SDL_Color){255, 255, 255});
    env->menu.textPos.y = ((env->winsurf->h - 140) / 8) + (env->menu.text->h * 2) + (env->menu.text->h / 2)  + 40;
    WriteOnScreen(env, "STRAF LEFT", (SDL_Color){255, 255, 255});
    env->menu.textPos.y = ((env->winsurf->h - 140) / 8) + (env->menu.text->h * 4)  + 40;
    WriteOnScreen(env, "STRAF RIGHT", (SDL_Color){255, 255, 255});
    env->menu.textPos.y = ((env->winsurf->h - 140) / 8) + (env->menu.text->h * 5) + (env->menu.text->h / 2)  + 40;
    WriteOnScreen(env, "JUMP / GO UP", (SDL_Color){255, 255, 255});
    env->menu.textPos.y = ((env->winsurf->h - 140) / 8) + (env->menu.text->h * 7)  + 40;
    WriteOnScreen(env, "CROUCH / GO DOWN", (SDL_Color){255, 255, 255});
    //env->menu.textPos.y = ((env->winsurf->h - 140) / 8) + (env->menu.text->h * 8) + (env->menu.text->h / 2)  + 40;
    //WriteOnScreen(env, "ESC TO RAGEQUIT", (SDL_Color){255, 255, 255});
    //env->menu.textPos.y = ((env->winsurf->h - 140) / 8) + (env->menu.text->h * 10)  + 40;
    //WriteOnScreen(env, "ESC TO RAGEQUIT", (SDL_Color){255, 255, 255});
 
    env->menu.textPos.x = env->winsurf->w / 3.5;
 
    env->menu.textPos.y = ((env->winsurf->h - 140) / 8) - (env->menu.text->h / 2) + 40; //Blitage des touches
    WriteOnScreen(env, ":W", (SDL_Color){255, 255, 255});
    env->menu.textPos.y = ((env->winsurf->h - 140) / 8) + env->menu.text->h  + 40;
    WriteOnScreen(env, ":S", (SDL_Color){255, 255, 255});
    env->menu.textPos.y = ((env->winsurf->h - 140) / 8) + (env->menu.text->h * 2) + (env->menu.text->h / 2)  + 40;
    WriteOnScreen(env, ":A", (SDL_Color){255, 255, 255});
    env->menu.textPos.y = ((env->winsurf->h - 140) / 8) + (env->menu.text->h * 4)  + 40;
    WriteOnScreen(env, ":D", (SDL_Color){255, 255, 255});
    env->menu.textPos.y = ((env->winsurf->h - 140) / 8) + (env->menu.text->h * 5) + (env->menu.text->h / 2)  + 40;
    WriteOnScreen(env, ":SPACE", (SDL_Color){255, 255, 255});
    env->menu.textPos.y = ((env->winsurf->h - 140) / 8) + (env->menu.text->h * 7)  + 40;
    WriteOnScreen(env, ":CTRL", (SDL_Color){255, 255, 255});
    //env->menu.textPos.y = ((env->winsurf->h - 140) / 8) + (env->menu.text->h * 8) + (env->menu.text->h / 2)  + 40;
    //WriteOnScreen(env, "ESC TO RAGEQUIT", (SDL_Color){255, 255, 255});
    //env->menu.textPos.y = ((env->winsurf->h - 140) / 8) + (env->menu.text->h * 10)  + 40;
    //WriteOnScreen(env, "ESC TO RAGEQUIT", (SDL_Color){255, 255, 255});
 
    env->menu.button1Pos.y = env->winsurf->h - env->menu.button->h;
    env->menu.button1Pos.x = env->winsurf->w - env->menu.button->w;
    makebutton(env, "BACK", env->menu.button1Pos);
    //SDL_BlitSurface(env->menu.button, NULL, env->winsurf, &env->menu.button1Pos);
    SDL_FreeSurface(text);
}

void    event_MainMenu(t_env *env)
{
    while(SDL_PollEvent(&env->event))
    {
        if ((env->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE
		    && env->event.type == SDL_KEYDOWN)
                || env->event.type == SDL_QUIT)
            ft_exit(env, "fini\n", 1);
        if(env->key[LCLICK] == 1 && env->event.button.button == SDL_BUTTON_LEFT)
                    {
                        SDL_GetMouseState(&env->clicks.x, &env->clicks.y);
                        printf("%d, %d\n", env->clicks.x, env->clicks.y);
                        if(env->clicks.y > env->menu.button1Pos.y
                          && env->clicks.y <= env->menu.button1Pos.y + env->menu.button->h
                          && env->clicks.x > env->menu.button1Pos.x
                          && env->clicks.x <= env->menu.button1Pos.x + env->menu.button->w)
                          {
                              if(env->usr.platform == MENU)
                              {
                                  printf("GAME\n");
                                  env->usr.platform = GAME;
                              }
                              else if(env->usr.platform == PAUSE)
                              {
                                  printf("GAME\n");
                                  env->usr.platform = GAME;
                              }
                              else if(env->usr.platform == OPTION)
                              {
                                  printf("PAUSE\n");
                                  env->usr.platform = PAUSE;
                              }
                          }
                        else if(env->clicks.y > env->menu.button2Pos.y
                          && env->clicks.y <= env->menu.button2Pos.y + env->menu.button->h
                          && env->clicks.x > env->menu.button2Pos.x
                          && env->clicks.x <= env->menu.button2Pos.x + env->menu.button->w)
                          {
                              if(env->usr.platform == MENU)
                              {
                                  printf("FORGE\n");
                                  //env->usr.platform = FORGE;
                              }
                              else if(env->usr.platform == PAUSE)
                              {
                                  //printf("OPTION\n");
                                  env->usr.platform = OPTION;
                              }
                          }
                        break;
                    }
        key_tab(env);
    }
    //SDL_FreeSurface(env->menu.button);
    //SDL_FreeSurface(env->menu.text);
}