# jet-browser [![GitHub stars](https://img.shields.io/github/stars/MaiFOSS/jet-browser?style=social)](https://github.com/MaiFOSS/jet-browser)
Jet Browser: Be like a jet on the sky of the web, fast and secure.


## How to run


1. Ensure you have WebKitGTK installed::

- Debian based distributions:
    ```
    sudo apt install libwebkit2gtk-4.0-dev
    ```
- Nix package manager:
    You can add these three packages to your ```etc/nixos/configuration.nix``` file or install them directly.
    ```
    pkgs.webkitgtk.dev
    pkgs.pkg-config
    pkgs.gcc
    ```

for Windows, install it manually.

2. run the following commands:

```
gcc src/browser.c $(pkg-config --cflags --libs webkit2gtk-4.0) -o browser
```
Then, execute the compiled browser:
```
./browser
```
