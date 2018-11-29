[BACK](https://mcarletti.github.io/)

*Last update: November 29th, 2018*

# Boot message: "error: no symbol table" (BUGFIX)

It seems to be a [known issue](https://bugs.launchpad.net/ubuntu/+source/linux/+bug/1633839). After kernel boot and before login screen, the following message appears:

```
error: no symbol table
Press any key to continue...
```

According to the above discussion and the [official documentation](https://help.ubuntu.com/community/Grub2/Installing#Reinstalling_GRUB_2_from_a_Working_System), you can fix this error by updating `grub`.

**X** is the drive (letter) on which you want GRUB to write the boot information. Normally users should not include a partition number, which would produce an error message as the command would attempt to write the information to a partition. 

```bash
sudo apt update
sudo grub-install /dev/sdX # example: sudo grub-install /dev/sda
sudo update-grub
```

Tested on:
* Ubuntu 18.04 (Linux 4.15.0-39-generic #42-Ubuntu SMP x86_64 GNU/Linux)
