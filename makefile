src_path = src
build_path = build
output_file_name = $(build_path)/a.out

build:  engine.o glad.o main.o resource_manager.o scene_base.o scene_main.o \
		shader.o sprite_renderer.o stb_image.o texture.o
	clang++ -g \
		$(build_path)/engine.o \
		$(build_path)/glad.o \
		$(build_path)/main.o \
		$(build_path)/resource_manager.o \
		$(build_path)/scene_base.o \
		$(build_path)/scene_main.o \
		$(build_path)/shader.o \
		$(build_path)/sprite_renderer.o \
		$(build_path)/stb_image.o \
		$(build_path)/texture.o \
		-lglfw \
		-o $(output_file_name)

engine.o: $(src_path)/engine.cpp
	clang++ -g -c -x c++ $(src_path)/engine.cpp -o $(build_path)/engine.o
glad.o: $(src_path)/glad.c
	clang++ -g -c -x c $(src_path)/glad.c -o $(build_path)/glad.o
main.o: $(src_path)/main.cpp
	clang++ -g -c -x c++ $(src_path)/main.cpp -o $(build_path)/main.o
resource_manager.o: $(src_path)/resource_manager.cpp
	clang++ -g -c -x c++ -std=c++11 $(src_path)/resource_manager.cpp -o $(build_path)/resource_manager.o
scene_base.o: $(src_path)/scene_base.cpp
	clang++ -g -c -x c++ $(src_path)/scene_base.cpp -o $(build_path)/scene_base.o
scene_main.o: $(src_path)/scene_main.cpp
	clang++ -g -c -x c++ $(src_path)/scene_main.cpp -o $(build_path)/scene_main.o
shader.o: $(src_path)/shader.cpp
	clang++ -g -c -x c++ $(src_path)/shader.cpp -o $(build_path)/shader.o
sprite_renderer.o: $(src_path)/sprite_renderer.cpp
	clang++ -g -c -x c++ $(src_path)/sprite_renderer.cpp -o $(build_path)/sprite_renderer.o
stb_image.o: $(src_path)/stb_image.cpp
	clang++ -g -c -x c++ $(src_path)/stb_image.cpp -o $(build_path)/stb_image.o
texture.o: $(src_path)/texture.cpp
	clang++ -g -c -x c++ $(src_path)/texture.cpp -o $(build_path)/texture.o

clean:
	rm $(output_file_name)
	rm $(build_path)/*.o

run:
	./$(output_file_name)
