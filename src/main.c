/*
 * main.c — VideopacHorse_SteamDeck placeholder (v0.0.1-Baer)
 * SDL2-schil om VideopacHorse_Core: venster + texture-blit van het RGBA-framebuffer,
 * SDL-audio-callback op g7k_audio_read, gamecontroller → g7k_joystick_set.
 * Bouwt en start zonder ROMs (toont zwart venster + versietitel); BIOS/cart via argv.
 */
#include <stdio.h>
#include <stdlib.h>
#include <SDL2/SDL.h>
#include "g7000.h"

static uint8_t *read_file(const char *file_arg, size_t *out_size)
{
    FILE *f = fopen(file_arg, "rb");
    if (!f) return NULL;
    fseek(f, 0, SEEK_END);
    long n = ftell(f);
    fseek(f, 0, SEEK_SET);
    if (n <= 0) { fclose(f); return NULL; }
    uint8_t *buf = malloc((size_t)n);
    if (buf && fread(buf, 1, (size_t)n, f) != (size_t)n) { free(buf); buf = NULL; }
    fclose(f);
    if (buf) *out_size = (size_t)n;
    return buf;
}

int main(int argc, char **argv)
{
    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_GAMECONTROLLER) != 0) {
        fprintf(stderr, "SDL_Init: %s\n", SDL_GetError());
        return 1;
    }

    g7k_sys *sys = g7k_create();
    if (!sys) return 1;

    for (int i = 1; i + 1 < argc; i += 2) {
        size_t n = 0;
        uint8_t *buf = NULL;
        if (SDL_strcmp(argv[i], "--bios") == 0 && (buf = read_file(argv[i + 1], &n)))
            g7k_load_bios(sys, buf, n);
        else if (SDL_strcmp(argv[i], "--cart") == 0 && (buf = read_file(argv[i + 1], &n)))
            g7k_load_cart(sys, buf, n);
        free(buf);
    }
    g7k_reset(sys, true);

    int w = g7k_fb_width(sys), h = g7k_fb_height(sys);
    char title[64];
    snprintf(title, sizeof title, "VideopacHorse %s", g7k_version());
    SDL_Window *win = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED,
                                       SDL_WINDOWPOS_CENTERED, w * 3, h * 3, SDL_WINDOW_RESIZABLE);
    SDL_Renderer *ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_PRESENTVSYNC);
    SDL_Texture *tex = SDL_CreateTexture(ren, SDL_PIXELFORMAT_ABGR8888,
                                         SDL_TEXTUREACCESS_STREAMING, w, h);

    bool running = true;
    while (running) {
        SDL_Event ev;
        while (SDL_PollEvent(&ev))
            if (ev.type == SDL_QUIT) running = false;

        g7k_run_frame(sys);
        SDL_UpdateTexture(tex, NULL, g7k_framebuffer(sys), w * 4);
        SDL_RenderClear(ren);
        SDL_RenderCopy(ren, tex, NULL, NULL);
        SDL_RenderPresent(ren);
    }

    SDL_DestroyTexture(tex);
    SDL_DestroyRenderer(ren);
    SDL_DestroyWindow(win);
    g7k_destroy(sys);
    SDL_Quit();
    return 0;
}
