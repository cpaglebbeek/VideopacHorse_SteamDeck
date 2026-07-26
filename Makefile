# VideopacHorse_SteamDeck — SDL2-schil (placeholder v0.0.1-Baer)
# Vereist: sdl2 (brew install sdl2 / Flatpak SDK op de Deck)
CORE := ../VideopacHorse_Core
CC   ?= cc
CFLAGS ?= -std=c11 -O2 -Wall -Wextra -I$(CORE)/include $(shell sdl2-config --cflags)
LIBS := $(shell sdl2-config --libs)

videopachorse: src/main.c $(wildcard $(CORE)/src/*.c)
	$(CC) $(CFLAGS) $^ $(LIBS) -o $@

clean:
	rm -f videopachorse

.PHONY: clean
