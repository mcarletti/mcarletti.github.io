[BACK](https://mcarletti.github.io/)

*Last update: November 20th, 2018*

# Steam in Wine: content servers unreachable (BUGFIX)

[ITALIAN]
```
Si è verificato un errore durante l'aggiornamento di NOMEGIOCO: Server dei contenuti non raggiungibili
```

It seems the error is a known bug on the [official bugtracker](https://bugs.winehq.org/show_bug.cgi?id=45329) of Wine.

#### CLOSE ALL WINE AND STEAM PROCESSES BEFORE APPLYING THE FIX
Otherwise the process might fail.

The solution proposed by a good boy on Reddit is the following:


1. navigate to `$HOME/.wine/drive_c/Program Files/Steam/config/`
1. [_optional_] create a copy of the file `config.vdf`
1. open the file `config.vdf` with a text editor
1. add the following line right after the `cip` entry:

```
"CS" "valve511.steamcontent.com;valve501.steamcontent.com;valve517.steamcontent.com;valve557.steamcontent.com;valve513.steamcontent.com;valve535.steamcontent.com;valve546.steamcontent.com;valve538.steamcontent.com;valve536.steamcontent.com;valve530.steamcontent.com;valve559.steamcontent.com;valve545.steamcontent.com;valve518.steamcontent.com;valve548.steamcontent.com;valve555.steamcontent.com;valve556.steamcontent.com;valve506.steamcontent.com;valve544.steamcontent.com;valve525.steamcontent.com;valve567.steamcontent.com;valve521.steamcontent.com;valve510.steamcontent.com;valve542.steamcontent.com;valve519.steamcontent.com;valve526.steamcontent.com;valve504.steamcontent.com;valve500.steamcontent.com;valve554.steamcontent.com;valve562.steamcontent.com;valve524.steamcontent.com;valve502.steamcontent.com;valve505.steamcontent.com;valve547.steamcontent.com;valve560.steamcontent.com;valve503.steamcontent.com;valve507.steamcontent.com;valve553.steamcontent.com;valve520.steamcontent.com;valve550.steamcontent.com;valve531.steamcontent.com;valve558.steamcontent.com;valve552.steamcontent.com;valve563.steamcontent.com;valve540.steamcontent.com;valve541.steamcontent.com;valve537.steamcontent.com;valve528.steamcontent.com;valve523.steamcontent.com;valve512.steamcontent.com;valve532.steamcontent.com;valve561.steamcontent.com;valve549.steamcontent.com;valve522.steamcontent.com;valve514.steamcontent.com;valve551.steamcontent.com;valve564.steamcontent.com;valve543.steamcontent.com;valve565.steamcontent.com;valve529.steamcontent.com;valve539.steamcontent.com;valve566.steamcontent.com;valve165.steamcontent.com;valve959.steamcontent.com;valve164.steamcontent.com;valve1611.steamcontent.com;valve1601.steamcontent.com;valve1617.steamcontent.com;valve1603.steamcontent.com;valve1602.steamcontent.com;valve1610.steamcontent.com;valve1615.steamcontent.com;valve909.steamcontent.com;valve900.steamcontent.com;valve905.steamcontent.com;valve954.steamcontent.com;valve955.steamcontent.com;valve1612.steamcontent.com;valve1607.steamcontent.com;valve1608.steamcontent.com;valve1618.steamcontent.com;valve1619.steamcontent.com;valve1606.steamcontent.com;valve1605.steamcontent.com;valve1609.steamcontent.com;valve907.steamcontent.com;valve901.steamcontent.com;valve902.steamcontent.com;valve1604.steamcontent.com;valve908.steamcontent.com;valve950.steamcontent.com;valve957.steamcontent.com;valve903.steamcontent.com;valve1614.steamcontent.com;valve904.steamcontent.com;valve952.steamcontent.com;valve1616.steamcontent.com;valve1613.steamcontent.com;valve958.steamcontent.com;valve956.steamcontent.com;valve906.steamcontent.com"
```

Tested on:
* Ubuntu 18.04 (Linux 4.15.0-39-generic #42-Ubuntu SMP x86_64 GNU/Linux)
* wine-3.0 (Ubuntu 3.0-1ubuntu1)

Credits: [this discussion on reddit.com](https://www.reddit.com/r/wine_gaming/comments/8r0gh6/steam_in_winedevel_content_servers_unreachable/)