[BACK](https://mcarletti.github.io/)

*Last update: Jenuary 29th, 2019*

# **Pylint E1101 Module** '*module_name*' **has no** '*member_name*' **member** (BUGFIX)

Sometimes, your preferred Python IDE does not find member functions, causing intellinsense highlights them as errors with a message similar to the following:

```
Pylint E1101 Module 'torch' has no 'from_numpy' member
```

This is very annoying, but some kind guy on the web gives a really nice solution :)

Actually, you could choose between two possibilities. First one is about changing your IDE settings (e.g. Visual Studio Code). Secondly, you could generate a 'global' resource file that is loaded from your pylint environment at runtime.

## Solution 1: change IDE settings

This is tested on Visual Studio Code, but the same idea should maps on other softwares.

Follow these instructions:

1. Open user-settings file (`File > Preferences > Settings` or use the shortcut `Ctrl-,`).
1. Type `python.linting.banditArgs` in the search bar.
1. Click on the `Edit settings.json` link to open the corresponding file.
1. Add the following snippet to the user settings (right column):

```
"python.linting.pylintArgs": [
    "--errors-only",
    "--generated-members=numpy.*,torch.*,cv2.*"
]
```

5. Restart the IDE.


## Solution 2: generate pylint resource file

1. Generate the pylint configuration file in your home folder. You could also consider to change the destination file with `/etc/pylintrc` (default global configuration).
```bash
pylint --generate-rcfile > .pylintrc
```
2. Update the TYPECHECK section to add the desired modules which function members list needs to be generated. For example, add `numpy.*` to generate the numpy member names.
```bash
[TYPECHECK]

# List of members which are set dynamically and missed by pylint inference
# system, and so shouldn't trigger E1101 when accessed. Python regular
# expressions are accepted.
generated-members=numpy.*,torch.*,cv2.*
```
3. Restart the IDE.

---

I personally prefer Solution 2 since I consider it more elegant and IDE-agnostic.

Enjoy :)

Tested on:
* Ubuntu 18.04 (Linux 4.15.0-39-generic #42-Ubuntu SMP x86_64 GNU/Linux)
* Visual Studio Code 1.30.2

Credits:

* [stackoverflow](https://stackoverflow.com/a/22449845/1358091)
* [github pytorch issues](https://github.com/pytorch/pytorch/issues/701#issuecomment-378048755)
