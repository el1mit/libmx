NAME_LIB = libmx.a

FLAGS = -std=c11 -Wall -Wextra -Werror -Wpedantic

all: create_obj LIBMX create_lib clean

create_obj:
	mkdir obj
	cp inc/*.h src

LIBMX:
	clang $(FLAGS) -c src/*.c
	mv *.o obj/

create_lib:
	ar -rc $(NAME_LIB) obj/*.o
	ranlib $(NAME_LIB)

clean:
	rm -rf obj
	rm src/*.h

uninstall:
	rm -rf obj
	rm -rf $(NAME_LIB)

reinstall:
	make uninstall
	make

