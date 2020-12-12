gcc:
	gcc -o vish main.c main_loop.c get_input.c Get_args.c Execute.c f_redirection.c f_launch.c Buildin.c f_piping.c -I .
clear:
	rm -rf *.0
	rm -rf vish
