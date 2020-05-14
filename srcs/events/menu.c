#include "../../includes/3d_engine.h"

// TEST MENU
int menu(SDL_Surface* screen, int menu)//Menu
{
    int continuer = 1, buttonRequest = 1; //buttonRequest renvoie une valeur selon où a cliqué l'utilisateur
    SDL_Surface *button, *text, *saveScreen;
    SDL_Color textColor = {51, 153, 204}, bgColor = {0, 0, 0};
    SDL_Rect button1Pos, button2Pos, button3Pos, textPos;
    SDL_Event event;
 
    // SDL_EnableUNICODE(1);
 
    while(menu)
    {
 
        if(menu == MAIN_MENU)
        {
            printf("TEST\n");
            // clearScreen(screen); // REMPLIR L'ECRAN DE L'IMAGE MEUNU
            TTF_Font* font = TTF_OpenFont("includes/assets/AmazDooMLeft.ttf", 100);
            text = TTF_RenderText_Shaded(font, "DooM", textColor, bgColor);
            printf("text w = %d\n", text->w);
            textPos.x = (screen->w - text->w) / 2;
            textPos.y = 30;
            // SDL_BlitSurface(text, NULL, screen, &textPos);
            button = IMG_Load("includes/assets/tiles/buttonStock1d.png");
            // if(!button) 
            //     printf("IMG_Load: %s\n", IMG_GetError());
            button1Pos.x = button2Pos.x = button3Pos.x = (screen->w - button->w) / 2;
            button1Pos.y = (screen->h / 2) - (button->h * 1.5) - BUTTON_MARGE;
            SDL_BlitSurface(button, NULL, screen, &button1Pos);
            button = IMG_Load("includes/assets/tiles/buttonStock1d.png");
            button2Pos.y = (screen->h - button->h) / 2;
            SDL_BlitSurface(button, NULL, screen, &button2Pos);
            button = IMG_Load("includes/assets/tiles/buttonStock1d.png");
            button3Pos.y = (screen->h + button->h) / 2 + BUTTON_MARGE;
            SDL_BlitSurface(button, NULL, screen, &button3Pos);
 
            continuer = 1;
        }
        else if(menu == CONTROLS_MENU)
        {
            printf("TEST1\n");

            // clearScreen(screen); // REMPLIR L'ECRAN DE L'IMAGE CONTROLS MENU
            TTF_Font *font = TTF_OpenFont("assets/AmazDooMLeft.ttf", 50);
 
            textPos.x = screen->w / 3.5;
            textPos.y = ((screen->h - 140) / 8) - (text->h / 2) + 40; //Blitage des définitions
            text = TTF_RenderText_Shaded(font, "Up (player 1)", textColor, bgColor);
            SDL_BlitSurface(text, NULL, screen, &textPos);
            textPos.y = ((screen->h - 140) / 8) + text->h  + 40;
            text = TTF_RenderText_Shaded(font, "Down (player 1)", textColor, bgColor);
            SDL_BlitSurface(text, NULL, screen, &textPos);
            textPos.y = ((screen->h - 140) / 8) + (text->h * 2) + (text->h / 2)  + 40;
            text = TTF_RenderText_Shaded(font, "Left (player 1)", textColor, bgColor);
            SDL_BlitSurface(text, NULL, screen, &textPos);
            textPos.y = ((screen->h - 140) / 8) + (text->h * 4)  + 40;
            text = TTF_RenderText_Shaded(font, "Right (player 1)", textColor, bgColor);
            SDL_BlitSurface(text, NULL, screen, &textPos);
            textPos.y = ((screen->h - 140) / 8) + (text->h * 5) + (text->h / 2)  + 40;
            text = TTF_RenderText_Shaded(font, "Up (player 2)", textColor, bgColor);
            SDL_BlitSurface(text, NULL, screen, &textPos);
            textPos.y = ((screen->h - 140) / 8) + (text->h * 7)  + 40;
            text = TTF_RenderText_Shaded(font, "Down (player 2)", textColor, bgColor);
            SDL_BlitSurface(text, NULL, screen, &textPos);
            textPos.y = ((screen->h - 140) / 8) + (text->h * 8) + (text->h / 2)  + 40;
            text = TTF_RenderText_Shaded(font, "Left (player 2)", textColor, bgColor);
            SDL_BlitSurface(text, NULL, screen, &textPos);
            textPos.y = ((screen->h - 140) / 8) + (text->h * 10)  + 40;
            text = TTF_RenderText_Shaded(font, "Right (player 2)", textColor, bgColor);
            SDL_BlitSurface(text, NULL, screen, &textPos);
 
            textPos.x = screen->w / 2;
 
            textPos.y = ((screen->h - 140) / 8) - (text->h / 2) + 40; //Blitage des touches
            text = TTF_RenderText_Shaded(font, "\"I\"", textColor, bgColor);
            SDL_BlitSurface(text, NULL, screen, &textPos);
            textPos.y = ((screen->h - 140) / 8) + text->h  + 40;
            text = TTF_RenderText_Shaded(font, "\"J\"", textColor, bgColor);
            SDL_BlitSurface(text, NULL, screen, &textPos);
            textPos.y = ((screen->h - 140) / 8) + (text->h * 2) + (text->h / 2)  + 40;
            text = TTF_RenderText_Shaded(font, "\"K\"", textColor, bgColor);
            SDL_BlitSurface(text, NULL, screen, &textPos);
            textPos.y = ((screen->h - 140) / 8) + (text->h * 4)  + 40;
            text = TTF_RenderText_Shaded(font, "\"L\"", textColor, bgColor);
            SDL_BlitSurface(text, NULL, screen, &textPos);
            textPos.y = ((screen->h - 140) / 8) + (text->h * 5) + (text->h / 2)  + 40;
            text = TTF_RenderText_Shaded(font, "\"Z\"", textColor, bgColor);
            SDL_BlitSurface(text, NULL, screen, &textPos);
            textPos.y = ((screen->h - 140) / 8) + (text->h * 7)  + 40;
            text = TTF_RenderText_Shaded(font, "\"Q\"", textColor, bgColor);
            SDL_BlitSurface(text, NULL, screen, &textPos);
            textPos.y = ((screen->h - 140) / 8) + (text->h * 8) + (text->h / 2)  + 40;
            text = TTF_RenderText_Shaded(font, "\"S\"", textColor, bgColor);
            SDL_BlitSurface(text, NULL, screen, &textPos);
            textPos.y = ((screen->h - 140) / 8) + (text->h * 10)  + 40;
            text = TTF_RenderText_Shaded(font, "\"D\"", textColor, bgColor);
            SDL_BlitSurface(text, NULL, screen, &textPos);
 
            button = IMG_Load("assets/tiles/buttonStock1d.png");
            button1Pos.x = 25;
            button1Pos.y = screen->h - 70;
            SDL_BlitSurface(button, NULL, screen, &button1Pos);
 
            continuer = 1;
        }
        else if(menu == PAUSE_MENU)
        {

            // saveScreen = SDL_DisplayFormat(screen);
            button = IMG_Load("includes/assets/tiles/buttonStock1d.png");
            //button = SDL_LoadBMP("doom.bmp");
            printf("caca");
            printf("TEST2\n s->w %d\n", screen->w);
            button1Pos.x = button2Pos.x = (screen->w - button->w) / 2;
            button1Pos.y = (screen->h - BUTTON_MARGE) / 2 - button->h;
            SDL_BlitSurface(button, NULL, screen, &button1Pos);
            button = IMG_Load("includes/assets/tiles/buttonStock1d.png");
            
            button2Pos.y = (screen->h + BUTTON_MARGE) / 2;
            SDL_BlitSurface(button, NULL, screen, &button2Pos);
 
            continuer = 1;
        }
 
        // SDL_Flip(screen);
 
        while(continuer)
        {
            while (SDL_PollEvent(&event))
            {
                switch(event.type)
                {
                    case SDL_QUIT:
                        continuer = 0;
                        menu = 0;
                        buttonRequest = 0;
                        break;
                    case SDL_KEYDOWN:
                        switch(event.key.keysym.mod)
                        {
                        case SDLK_ESCAPE:
                            continuer = 0;
                            if(menu == MAIN_MENU)
                            {
                                buttonRequest = 0;
                                menu = EXIT_MENU;
                            }
                            else if(menu == CONTROLS_MENU)
                            {
                                menu = MAIN_MENU;
                            }
                            else if(menu == PAUSE_MENU)
                            {
                                menu = EXIT_MENU;
                            }
                            break;
                        }
                        break;
                    case SDL_MOUSEBUTTONUP:
                        if(event.button.y > button1Pos.y
                          && event.button.y <= button1Pos.y + button->h
                          && event.button.x > button1Pos.x
                          && event.button.x <= button1Pos.x + button->w)
                          {
                              continuer = 0;
                              if(menu == MAIN_MENU)
                              {
                                  menu = EXIT_MENU;
                                  buttonRequest = 2;
                              }
                              else if(menu == CONTROLS_MENU)
                              {
                                  menu = MAIN_MENU;
                              }
                              else if(menu == PAUSE_MENU)
                              {
                                  SDL_BlitSurface(saveScreen, &button1Pos, screen, &button1Pos);
                                  SDL_BlitSurface(saveScreen, &button2Pos, screen, &button2Pos);
                                //   SDL_Flip(screen);
                                  menu = EXIT_MENU;
                              }
                          }
                        else if(event.button.y > button2Pos.y
                          && event.button.y <= button2Pos.y + button->h
                          && event.button.x > button2Pos.x
                          && event.button.x <= button2Pos.x + button->w)
                          {
                              if(menu == MAIN_MENU)
                              {
                                  continuer = 0;
                                  menu = CONTROLS_MENU;
                              }
                              else if(menu == PAUSE_MENU)
                              {
                                  continuer = 0;
                                  menu = MAIN_MENU;
                              }
 
                          }
                        else if(event.button.y > button3Pos.y
                          && event.button.y <= button3Pos.y + button->h
                          && event.button.x > button3Pos.x
                          && event.button.x <= button3Pos.x + button->w)
                          {
                              if(menu == MAIN_MENU)
                              {
                                  continuer = 0;
                                  menu = EXIT_MENU;
                                //   ft_exit(env, "fini\n", 1);
                                  buttonRequest = 0;
                              }
                          }
                        break;
                }
                SDL_Delay(20);
            }
        }
    }
 
    SDL_FreeSurface(button);
    SDL_FreeSurface(text);
    SDL_FreeSurface(saveScreen);
 
    return buttonRequest;
}
// FIN TEST MENU