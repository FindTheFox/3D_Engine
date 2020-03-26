SRCS_FILE	=	main.c \
				engine/draw.c \
				init/dynamic_tab.c \
				engine/clipping.c \
				engine/cube_point.c \
				engine/engine_tools.c \
				engine/pthread.c \
				engine/textured_tris.c \
				engine/color.c \
				engine/fill_triangle.c \
				engine/cube3d.c \
				engine/line.c \
				events/mesh_event.c \
				events/camera.c \
				events/event.c \
				exit/exit.c \
				vectors/vector_calc.c \
				matrices/init_matrice.c \
				obj_parser/obj_parser.c \
				obj_parser/file_parser.c \
				init/init_sdl.c \
				init/init_data.c \
				tools.c

OBJ_DIRS =		engine \
				exit \
				events \
				vectors \
				obj_parser \
				matrices