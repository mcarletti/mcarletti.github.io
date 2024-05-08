# mcarletti.github.io

Hi, this is Marco 👋  
This is my simple blog and personal frontpage.

## Getting started

I'm not a webmaster nor a designer, so I decided to use [Hugo](https://gohugo.io/) to build this site.  
I know nothing about Go, but I found Hugo easier than the alternatives.

### Installation

First of all, download this repository and all submodules.

```bash
git clone git@github.com:mcarletti/mcarletti.github.io.git
git submodule update --init --recursive
```

To build a local website, you need to install Hugo. Unfortunately, `apt` package manager brings an old version of the library, so I suggest you to install it via `snap`. At the time of writing, the latest version is 0.125.6.

```bash
snap install hugo
```

To build the website and get a local server, you simply need to run the following command from the root folder of the project.

```bash
hugo server -D
```

The `-D` is optional but it allows you to see draft content.

### Deployment

You need to create an Action in the action group and... Nevermind.  
Hugo has a fairly simple [documentation](https://gohugo.io/hosting-and-deployment/hosting-on-github/), but it works.  
If I was able to do it, you can do it too. Read it.

After that, make your changes and push them to the `main` branch.  
Let the buider action do the rest and enjoy your new website in a few seconds 🚀

## Notes

I still don't understand why images are not displayed if they are located in the `assets` folder.  
Maybe it's the theme I'm using, but I don't care too much (hey, I simply want my website published).  
I found [this](https://discourse.gohugo.io/t/cannot-get-images-to-appear-in-content-and-main-page/14017) workaround: I put the images in the `static` folder and I reference them with the `/` prefix.

## Licence

[mcarletti.github.io](https://github.com/mcarletti/mcarletti.github.io) © 2024 by [Marco Carletti](https://www.marcocarletti.it/) is licensed under [CC BY 4.0](https://creativecommons.org/licenses/by/4.0/?ref=chooser-v1).
