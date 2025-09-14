# BinScribe

**BinScribe** je lagani, cross-platformski tekst editor otvorenog koda za konverziju tekstualnih datoteka u binarni zapis (0 i 1) i obrnuto.

Aplikacija omogućuje:
- Kreiranje novih dokumenata
- Otvaranje `.txt` datoteka (automatski detektira binarni ili UTF tekst)
- Spremanje teksta u binarnom formatu
- Jednostavno i intuitivno sučelje

## Verzija

Trenutna verzija: **1.1.2**  
- Dodana binarna dekripcija  
- Pametno otvaranje `.txt` datoteka (prepoznaje binarni zapis i pretvara u čitljiv tekst)
- Dodani segment o programu

## Platforma

- Windows build kao setup .exe 
- Linux build .deb i AppImage paket

## Screenshot

![BinScribe Screenshot](BinScribe.jpg)

## Linux

### Opcija A — AppImage (jedna datoteka, preporučeno)
1. Preuzmi `BinScribe-<ver>-x86_64.AppImage`.

2. Daj dopuštenje i pokreni <br />
    `chmod +x BinScribe-*.AppImage`<br />
    `./BinScribe-*.AppImage`<br />
    
3. Ako javlja FUSE error<br />
`sudo apt update && sudo apt install -y libfuse2`

4. Ako se žali na XCB/X11 (na “mršavim” sustavima)<br />
`sudo apt install -y libxcb-xinerama0 libxkbcommon-x11-0 libxcb-cursor0`<br />
ili bez FUSE-a:<br />
`./BinScribe-*.AppImage --appimage-extract-and-run`

### Opcija B — Debian/Ubuntu (.deb paket)
1. Instaliraj .deb<br />
`sudo apt install -y libqt6core6 libqt6gui6 libqt6widgets6 qt6-wayland libxkbcommon-x11-0 libxcb-cursor0 libxcb-xinerama0`<br />
`sudo dpkg -i binscribe-*.deb`<br />
ako prijavi nedostajuće ovisnosti<br />
`sudo apt -f install`

2. Pokretanje<br />
`BinScribe`

3. Deinstalacija<br />
`sudo apt remove binscribe`

4. Ako se launcher ne pojavi odmah u izborniku (opcionalno)<br />
`sudo update-desktop-database || true`<br />
`sudo gtk-update-icon-cache -f -q /usr/share/icons/hicolor || true`<br />

## Preuzimanje

Repozitorij: [github.com/dklobucaric/BinScribe](https://github.com/dklobucaric/BinScribe)

## SHA256 - za prebuild
1b83ba7a538195e382c2e932f51d4e05f0b0075039ec34a4a5d674aded321c46  binscribe-1.1.2-Linux.deb<br />
734ef0bd46b56b871aafcf67d2d71df3ac5cbe9614d794a93eefe6b7551058ba  BinScribe-x86_64.AppImage<br />
5f9ccc34b846b0325fe7b515d3969751bb6814bed6fa54c73997e9c9026a6b87  BinScribe-Setup-1.1.2.exe

## Licenca


**BinScribe (izvorni kod)** je objavljen pod **MIT licencom** – vidi datoteku `LICENSE`.

BinScribe binarne distribucije uključuju **Qt** biblioteke koje su licencirane pod **LGPLv3**.
Korisnik smije zamijeniti isporučene Qt DLL-ove vlastitim buildovima Qt-a.
Tekstovi licenci nalaze se u direktoriju `licenses/` (LGPL-3.0) i/ili na stranicama Qt projekta.

- Vaš kod: MIT
- Uključene biblioteke: Qt (LGPLv3)

© 2025 Dalibor Klobučarić

## Donacije

Ako ti se sviđa aplikacija ili ti je bila korisna — podrži projekt i počasti autora pivom 🍺  
👉 [Doniraj preko PayPal-a](https://www.paypal.com/paypalme/dklobucaric)

---

**Autor:** Dalibor Klobučarić  
📍 Šenkovec, Hrvatska
