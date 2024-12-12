# ICP - Interakce člověka s počítačem

## Literatura
- OpenGL Programming Guide
- OpenGL Superbible
- Computer Graphics Programing in Opengl with C++
- [shadertoy](www.shadertoy.com)

## Zkouška
Máme velkou semestrálku.

### Semestrální práce
Požadavky:
- Přepínání aplikace mezi window/fullsreen.
- 60fps 3D grafika. 
- Odevzdání klidně příští semestr.
- Nahrát na git, link emailem.

Bude se ptát proč to nefunguje a kdo za to může.

Nepoužívat knihovnu `GLUT`, zastaralá.
## Poznámky

> [!warning] 
> Nepoužívat `using namespace [];`
> Nevíte z jaké knihovny se funkce volají!

![[Více vláknové programování]]
### Shader
Program pro GPU.

![[3D Grafika]]

## Cvičení

cv6:
- [[tasks.md]]
- [Installing GLFW on Ubuntu](https://shnoh171.github.io/gpu%20and%20gpu%20programming/2019/08/26/installing-glfw-on-ubuntu.html)

cv8:
- [[TUL-navazující_studium/3. semestr/ICP-Interakce_cloveka_s_pocitacem/cviceni/08cv - pipe,VAO,shaders/README|tasks]]
- [x] draw single triangle
- [x] Change the color of the triangle
	- add key handling to change r,g,b
	- change r,g,b based on running time
cv9:
- [x] Kompilace generických shaderů definových v souboru
- [ ] Na-cache-ování uniform location pro zrychlení předání hodnot grafice.
- [x] Přidání Mash, model, vertex
- [ ] Vyřešit aby se zdrojové soubory ne-includovali několikrát.
cv10:
- [ ] Načtěte alespoň dva objekty
- [ ] Inicializujte perspektivu
- [ ] Kamera:
	- [ ] Kolečko myši -> zoomování
	- [ ] Klávesnice -> pohyb kamery
Proplouvání kamerou mezi 3 krychličkami.

> [!tip] Používejte smart pointery

cv11:
- [[TUL-navazující_studium/3. semestr/ICP-Interakce_cloveka_s_pocitacem/cviceni/11cv - tex/README|tasks]]
- [ ] Udělejte screenshot
	- `glReadPixels(x_start, y_start, width, height, format, type, *pixels)`
	- `format` -> gl_rgb, gl_bgr
	- `type` -> uchar
	- Přidat time k názvu screenshotu
```C
cv::MAT img;
cv_u8c3 // tri barevne kanaly
img.resite(cv::size(h,w))
...
file_name = "screenshot.jpg"
cv::imwrite(img, file_name)
```
- [ ] Zapauzování aplikace pokud se nikdo nedívá do kamery
	- počet nalezených obličejů: 0
- [ ] Klonování obrazu z kamery na zem bludiště.
cv12:
- [ ] Vykreslit alespoň jeden průhledný objekt.
cv13:
- [ ] 4 zdroje světla:
	- [ ] Ambient
	- [ ] Směrový `L = vec3(const)`
	- [ ] Bodový `L = vec3(const) - P.xyz`
	- [ ] Reflektor

Texturovací jednotky
Kolik jich máme?
Jak budeme bindovat textury?

> [!tip] Textury jsou vzhůru nohama?
```C
m = cv::imread
m.flip(0,1)
```

> [!question] Co dělat když se nenačtou textury?
Defaultní textura
```C
cv::MAT(2x2, u8_C3)
```
bílá, černá
černá, bílá
Nastavit opakování

> [!info] SoA vs AoS
> Structure of arrays versus Array of structures.
> Struktura polí je rychlejší na přístup do paměti s CACHE.

> [!info] Ambient
> Nedávat ambientní složku k směrovému, bodovému, reflektoru, protože to vypadá blbě. 


