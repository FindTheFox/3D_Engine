/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forge_ui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: brpinto <brpinto@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/01 11:25:38 by brpinto           #+#    #+#             */
/*   Updated: 2020/06/05 14:06:26 by brpinto          ###   ########.fr       */
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

static int button_collide(t_env *e, t_button *button)
{
	t_int		mouse;
	t_button	*curr;
	t_button	*prev;
	t_int		max;

	prev = e->f.buttons;
	curr = e->f.buttons;
	while (curr)
	{
		if (curr->cat == button->cat)
			break;
		curr = curr->next;
	}
	SDL_GetMouseState(&mouse.x, &mouse.y);
	if (e->event.type == SDL_MOUSEBUTTONDOWN && e->event.button.button == SDL_BUTTON_LEFT)
	{
		if (((mouse.x >= curr->x && mouse.x <= curr->x + 300) && (mouse.y >= curr->y && mouse.y <= curr->y + 30)))
		{
			while (prev)
			{
				if (prev->display == 1)
					break;
				prev = prev->next;
			}
			if (!prev && !curr->display)
				curr->display = 1;

			else if (prev && !((mouse.x >= prev->x + 10 && mouse.x <= prev->x + 310) && (mouse.y >= prev->y + 35 && mouse.y <= (prev->y + 35 + (prev->content.maxh * 30)))))
			{
				prev->display = 0;
				curr->display = 1;
			}
		}
		else if (curr->display && !((mouse.x >= curr->x + 10 && mouse.x <= curr->x + 310) && (mouse.y >= curr->y + 35 && mouse.y <= (curr->y + 35 + (curr->content.maxh * 30)))))
			curr->display = 0;
	}
}

static void    button_add(t_button **link, t_button *new)
{
	if (link)
		new->next = *link;
	*link = new;
}


void button_init(t_env *e, int x, int y, int cat, char *title)
{
	//	t_int size;
	t_button *button;

	if (!(button = malloc(sizeof(t_button))))
		return;
	button->title = title;
	button->w = 300;
	button->h = 30;
	button->x = x;
	button->y = y;
	//	size.x = button.w;
	//	size.y = button.h;
	button->display = 0;
	button->cat = cat;
	button->content.elem_num = 0;
	button->content.maxh = 0;
	button->next = NULL;
	//	printf("x = %d && y = %d\n", button->x, button->y);
	button_add(&e->f.buttons, button);
	//	draw_area(e, button.y, button.x, size, 0xffffff);
	//	printf("x = %d && y = %d\n", x, y);
	get_content(e, button);
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
		button_collide(e, tmp);
		display_name(e, tmp->y + 5, tmp->x + 5, tmp->title);
		if (tmp->display)
		{
			start.x = tmp->x;
			start.y = tmp->y;
			draw_list_component(e, start, size, tmp);
		}
		tmp = tmp->next;
	}
	//	draw_v(e);
	//	draw_list_component(e, start, size, 8, "Titre 1");
	//	start.y = 80;
	//	draw_list_component(e, start, size, 8, "Titre 2");

	draw_v(e);
	draw_area(e, 40, (W_W - (W_W / 3) + 20), size, 0x00ffff);
}

void forge_run(t_env *e)
{
	if (!e->f.initialized)
		init_forge(e);
	display_ui(e);
}
