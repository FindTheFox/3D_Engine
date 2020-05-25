/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forge_ui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpinto <brpinto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 11:25:38 by brpinto           #+#    #+#             */
/*   Updated: 2020/05/25 17:27:37 by brpinto          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/3d_engine.h"

/*
   void __attribute((destructor)) checkleaks();

   void checkleaks()
   {
   printf("Après l'exit ?\n");
   while (1)
   ;
   }
   */

static void button_collide(t_env *e, int cat)
{
	t_int mouse;
	t_button *tmp;

	tmp = e->f.buttons;
	while (tmp)
	{
		if (tmp->cat == cat)
			break;
		tmp = tmp->next;
	}
	// poll event loop pas bon
	//	while (SDL_PollEvent(&evt))
	//	{
	SDL_GetMouseState(&mouse.x, &mouse.y);
	if (e->event.type == SDL_MOUSEBUTTONDOWN)
	{
		if ((mouse.x >= tmp->x && mouse.x <= tmp->x + 300) && (mouse.y >= tmp->y && mouse.y <= tmp->y + 30))
		{
			if (!tmp->display)
				tmp->display = 1;
		/* si display_content est à 0 on 
		affiche le contenu en allant chercher la position dans une liste de bouton et on passe display à 1 */
		}
		else
			tmp->display = 0;
	}
}

/*
 ** create button ajoute un bouton dans une liste chainnée.
 ** En fonction de la où on clique on va chercher l'identifiant qui correspond
 ** On passe le display à 1
 ** On affiche la liste déroulant qui correspond en récupérant les infos dans la struct
 */

static void    button_add(t_button **link, t_button *new)
{
	if (link)
		new->next = *link;
	*link = new;
}


void button_init(t_env *e, int x, int y, int cat, int elem_num)
{
//	t_int size;
	t_button *button;
	if (!(button = malloc(sizeof(t_button))))
		return;
	button->w = 300;
	button->h = 30;
	button->x = x;
	button->y = y;
//	size.x = button.w;
//	size.y = button.h;
	button->display = 0;
	button->cat = cat;
	button->next = NULL;
//	printf("x = %d && y = %d\n", button->x, button->y);
	button_add(&e->f.buttons, button);
//	draw_area(e, button.y, button.x, size, 0xffffff);
}

static void display_ui(t_env *e)
{
	t_int size;
	t_int button_size;
	t_button *tmp;
	t_int start;

	//	start.x = (W_W - (W_W / 3)) + 40;
	//	start.y = 40;
	size.x = 10;
	size.y = 30;
	tmp = e->f.buttons;
	while (tmp)
	{
		button_size.x = 300;
		button_size.y = 30;
		draw_area(e, tmp->y, tmp->x, button_size, 0xffffff);
//		printf("x = %d && y = %d\n", tmp->x, tmp->y);
		button_collide(e, tmp->cat);
		if (tmp->display)
		{
			start.x = tmp->x;
			start.y = tmp->y;
			draw_list_component(e, start, size, 6, "Titre 1");
		}
		tmp = tmp->next;
	}
	//	draw_v(e);
	//	draw_list_component(e, start, size, 8, "Titre 1");
	//	start.y = 80;
	//	draw_list_component(e, start, size, 8, "Titre 2");

	draw_v(e);
//	button_init(e, (W_W - (W_W / 3) + 40), 40, 0, 3);
//	button_init(e, (W_W - (W_W / 3) + 40), 80, 1, 3);
//
	draw_area(e, 40, (W_W - (W_W / 3) + 20), size, 0x00ffff);
}

void forge_run(t_env *e)
{
	if (!e->f.initialized)
		init_forge(e);
	display_ui(e);
}
