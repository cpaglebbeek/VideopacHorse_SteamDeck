# ARCHITECTURE.md — VideopacHorse_SteamDeck (placeholder)

## Componenten

| Component | Bestand | Rol |
|---|---|---|
| SDL2-schil | `src/main.c` | venster, texture-blit RGBA-framebuffer, audio-callback, gamecontroller→joystick, argv-ROM-laden |
| Build | `Makefile` | native build tegen zusterrepo-core |
| Flatpak | `flatpak/nl.icthorse.VideopacHorse.yml` | bundel voor /Deploy2SteamDeck |

## Data-flow

argv `--bios/--cart` → `g7k_load_*` → per vsync-tick `g7k_run_frame` →
`SDL_UpdateTexture(ABGR8888)` → renderer; audio straks via `SDL_AudioCallback` op
`g7k_audio_read`; SDL_GameController → `g7k_joystick_set`.

## Ontwerpbeslissingen

1. **PRESENTVSYNC als frame-pacer** in de placeholder; bij echte engine wordt audio de
   meester-klok (zelfde beslissing als _Web) en PAL 50Hz op de 60Hz-Deck opgelost via
   audio-gedreven pacing.
2. **ABGR8888-textureformaat** matcht de little-endian RGBA-byteorde van de core zonder swizzle.
3. Flatpak `--filesystem=home:ro` zodat de gebruiker ROMs uit ~/ kan laden zonder kopie.
