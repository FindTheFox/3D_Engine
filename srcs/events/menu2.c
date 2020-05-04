#include "../../includes/3d_engine.h"

void    main_menu(t_env *env)
{
    env->menu.textColor = (SDL_Color){0, 0, 0, 0};
    env->menu.bgColor = (SDL_Color){0, 0, 0};

    SDL_FillRect(env->winsurf, NULL, 0x00000000);
    if(SDL_BlitSurface(env->menu.menu1, NULL, env->winsurf, NULL) == -1)
        printf("error blitsurface");
    // clearScreen(screen); // REMPLIR L'ECRAN DE L'IMAGE MEUNU
    TTF_Font* font = TTF_OpenFont("includes/assets/AmazDooMLeft.ttf", 40);
    if(!(env->menu.text = TTF_RenderText_Solid(font, "ESC to RAGEQUIT", env->menu.textColor)))
        {
           printf("%s\n", TTF_GetError());
        }
    env->menu.textPos.x = (env->winsurf->w / 2) - (env->menu.text->w / 2);
    env->menu.textPos.y = (env->winsurf->h - env->menu.text->h);
    SDL_BlitSurface(env->menu.text, NULL, env->winsurf, &env->menu.textPos);
    env->menu.button = IMG_Load("includes/assets/tiles/buttonMenu.png");
    if(!env->menu.button) 
        printf("IMG_Load: %s\n", IMG_GetError());
    env->menu.button1Pos.y = env->menu.button2Pos.y = (env->winsurf->h - env->menu.button->h) * 0.99;
    env->menu.button1Pos.x = (env->winsurf->w / 2) - (env->menu.button->w) - BUTTON_MARGE;
    if(SDL_BlitSurface(env->menu.button, NULL, env->winsurf, &env->menu.button1Pos) == -1)
        printf("error blitsurface");
    
    if(!(env->menu.text = TTF_RenderText_Solid(font, "PLAY", (SDL_Color){255, 255, 255})))
    {
        printf("%s\n", TTF_GetError());
    }
    env->menu.textPos.x = env->menu.button1Pos.x + env->menu.button->w * 0.4;
    env->menu.textPos.y = env->menu.button1Pos.y + env->menu.button->h * 0.4;
    SDL_BlitSurface(env->menu.text, NULL, env->winsurf, &env->menu.textPos);

    env->menu.button2Pos.x = (env->winsurf->w / 2) + BUTTON_MARGE;
    SDL_BlitSurface(env->menu.button, NULL, env->winsurf, &env->menu.button2Pos);

    if(!(env->menu.text = TTF_RenderText_Solid(font, "FORGE", (SDL_Color){255, 255, 255})))
    {
        printf("%s\n", TTF_GetError());
    }
    env->menu.textPos.x = env->menu.button2Pos.x + env->menu.button->w * 0.4;
    env->menu.textPos.y = env->menu.button2Pos.y + env->menu.button->h * 0.4;
    SDL_BlitSurface(env->menu.text, NULL, env->winsurf, &env->menu.textPos);
}

void       pause_menu(t_env *env)
{
    SDL_FillRect(env->winsurf, NULL, 0x00000000);
    if(SDL_BlitSurface(env->menu.menu2, NULL, env->winsurf, NULL) == -1)
        printf("error blitsurface");
    //saveScreen = SDL_DisplayFormat(screen);
    env->menu.button = IMG_Load("includes/assets/tiles/buttonMenu.png");
    //button = SDL_LoadBMP("doom.bmp");
    //printf("caca");
    //printf("TEST2\n s->w %d\n", env->winsurf->w);
    env->menu.button1Pos.x = env->menu.button2Pos.x = (env->winsurf->w - env->menu.button->w) / 2;
    env->menu.button1Pos.y = (env->winsurf->h - BUTTON_MARGE) / 2 - env->menu.button->h;
    SDL_BlitSurface(env->menu.button, NULL, env->winsurf, &env->menu.button1Pos);
    env->menu.button = IMG_Load("includes/assets/tiles/buttonMenu.png");
            
    env->menu.button2Pos.y = (env->winsurf->h + BUTTON_MARGE) / 2;
    SDL_BlitSurface(env->menu.button, NULL, env->winsurf, &env->menu.button2Pos);
            
}

void    event_MainMenu(t_env *env)
{
    while(SDL_PollEvent(&env->event))
    {
        if ((env->event.key.keysym.scancode == SDL_SCANCODE_ESCAPE
		    && env->event.type == SDL_KEYDOWN)
                || env->event.type == SDL_QUIT)
            ft_exit(env, "fini\n", 1);
        key_tab(env);
    }
    SDL_GetMouseState(&env->mouse.x, &env->mouse.y);
        SDL_ShowCursor(1);
        if (env->key[LCLICK])
        {
            //printf("MOUSE X: %d         MOUSE Y: %d\n", env->mouse.x, env->mouse.y);
            printf("SCREENCOLOR: %x\n", get_color(env->winsurf, env->mouse.x, env->mouse.y));
            //printf("TRI_ID: %d\n", env->depth_buff[pos].tri_id);
            env->key[LCLICK] = 0;
        }
}