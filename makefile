src_path = src/
output_file_name = build/a.out

build: $(src_path)main.cpp $(src_path)engine.cpp
	clang++ -x c $(src_path)glad.c \
		-x c++ $(src_path)main.cpp \
		-x c++ $(src_path)engine.cpp \
		-x c++ $(src_path)scene_base.cpp \
		-x c++ $(src_path)scene_main.cpp \
		-lglfw \
	-o $(output_file_name)

clean:
	rm $(output_file_name)

run:
	./$(output_file_name)
