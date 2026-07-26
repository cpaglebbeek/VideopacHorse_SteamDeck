# VideopacHorse_SteamDeck

Steam Deck-frontend (placeholder) van de VideopacHorse G7000-emulator: SDL2-schil om
de C11-core (zusterrepo `VideopacHorse_Core`) + Flatpak-manifest voor de bestaande
`/Deploy2SteamDeck`-route (zelfde flow als SteamDeckMSX).

**Status v0.0.1-Baer:** bouwt en start (zwart venster + versietitel, want de core is
nog een stub); geen Flatpak-bundle gepubliceerd.

```bash
make            # native build (Mac/Linux, vereist sdl2)
./videopachorse --bios /pad/o2rom.bin --cart /pad/game.bin
```

Geen ROMs/BIOS in deze repo — paden via argv, straks via Deck-UI.
