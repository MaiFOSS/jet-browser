# jet-browser [![GitHub stars](https://img.shields.io/github/stars/MaiFOSS/jet-browser?style=social)](https://github.com/MaiFOSS/jet-browser)
Jet Browser: Be like a jet on the sky of the web, fast and secure.


## How to test


1. make sure you have Web Kit GTK:

```
sudo apt install libwebkit2gtk-4.0-dev
```

for Windows, install it manually.

2. run the following commands:

```
gcc browser.c $(pkg-config --cflags --libs webkit2gtk-4.0) -o browser
```
then
```
./browser
```
