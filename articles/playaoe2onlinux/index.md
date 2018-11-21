[BACK](https://mcarletti.github.io/)

*Last update: November 21th, 2018*

# Play Age of Empires 2 HD with expansions on Linux (through wine+Steam)

Yes. You can play AOE2 HD on Linux.

## How to install

Install `wine` and `winetricks` using the following commands:
```
sudo apt update
sudo apt install wine-stable winetricks
```
See at the end of the page to check the version of these softwares at the time of writing.

Install `steam` through winetricks:
```
winetricks steam
```
If it does not work, download the [Windows installer](https://store.steampowered.com/about/) and run it using wine:
```
wine SteamSetup.exe
```

Now you are ready to run Steam and install your AOE2 HD.

If you encounter connection problems and you are not able to download the game, check this article about the [CONTENT SERVER UNREACHABLE bugfix](https://mcarletti.github.io/articles/steamwineunreachableservers/).

#### CLOSE ALL WINE AND STEAM PROCESSES BEFORE APPLYING THE FIX

## Missing DLLs

After the bugfix you should be able to download the game without problems.

Unfortunately, you could have problems related to missing DLL, in particular `msc140u.dll`. To fix this:

#### CLOSE ALL WINE AND STEAM PROCESSES BEFORE APPLYING THE FIX
Otherwise the installation might fail.

Open winetricks:
```
winetricks
```

* select the `Select the default wineprefix` option and click OK
* select the `Install a Windows DLL or component` option and click OK
* check the last Visual C++ runtimes (in my case, `vcrun2017`) and click OK

These operations will install the missing runtimes and DLLs you need to install AOE 2 HD.

Now, the game should start. Probably you could encounter an issue on the Gecko renderer used by the game launcher (something related to the HTML interface bla bla... I don't kknow. Who cares if I can play AOE2?). I have not fixed it yet.

BTW, clicking on the first (top-left) button of the launcher, the game will start.

Enjoy :)

Tested on:
* Ubuntu 18.04 (Linux 4.15.0-39-generic #42-Ubuntu SMP x86_64 GNU/Linux)
* wine-3.0 (Ubuntu 3.0-1ubuntu1)
* wintricks (20180217 - sha256sum: 1b156c616174f41df79d72a90c52eb2b110c63a6e8ecb865d303a8f9f0908924)
