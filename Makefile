build:
	g++ -w -std=c++14 \
	./src/*.cpp \
	-o SDL_Game.o \
	-I"./lib/lua" \
	-L"./lib/lua" \
	-llua \
	-lSDL2 \
	-lSDL2_image \
	-lSDL2_ttf \
	-lSDL2_mixer;

clean:
	rm ./SDL_Game.o;

run:
	./SDL_Game.o;
