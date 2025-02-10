# osu Custom Key Overlay 🎮✨

This project allows osu players to use a customizable key overlay with a configuration file. You can adjust the keys, the colors of the keys, sliders, borders, and even add a custom image. All configurations are made through an `.ini` file.

## Features 🔧

- **Key Visualization**: Visualize the key signal when pressing your keys.
- **Customizable Key Codes**: Choose which keys you want to display.
- **Customizable Keys**: Change the background and border colors of the keys.
- **Customizable Sliders**: Modify the background and border colors of the sliders that extend from the keys.
- **Custom Image**: Replace the default image with your own (PNG format, 75x75px). If you don't want an image, simply leave a blank one.
- **Page Icon**: Change the icon of the page that opens.

## Installation ⚙️

1. Download the latest release.
2. Modify the `.ini` configuration file according to your preferences (briefly explain the structure of the `.ini` file if needed).
3. Launch the `.exe` file to start the overlay.

## Folder Structure 📁

- `img/`: Folder containing the images used for the keys and sliders.
- `config.ini`: Configuration file to customize the overlay.

## Overlay Demo With Default Configuration 🎥

![Overlay Demo](img/demo_default_config.gif)

Here’s a preview of the overlay in action. The GIF below shows the customized overlay with modified keys, sliders, and images.

## Example Configuration (`config.ini`) ⚡

Here’s an example configuration in the `.ini` file:

```ini
[General]
Key_1=83
Key_2=68

[images]
key_1=img/logo.png
key_2=img/logo.png

[icon]
path=icon.ico

[colors]
background_key_1="transparent"
background_key_2="transparent"
border_key_1="transparent"
border_key_2="transparent"
slider_1="transparent"
slider_2="transparent"
slider_border_1="transparent"
slider_border_2="transparent"

[colors_on_pressing]
background_key_1="transparent"
background_key_2="transparent"
border_key_1="transparent"
border_key_2="transparent"

[slider_images]
key_1=img/slider.png
key_2=img/slider.png
```

## KeyCode configuration ➡️

By default, keys Q and W are used, but you can change them:

```ini
[General]
Key_1=81
Key_2=87
```

with this list:

```
0 = 48
1 = 49
2 = 50
3 = 51
4 = 52
5 = 53
6 = 54
7 = 55
8 = 56
9 = 57
A = 65
B = 66
C = 67
D = 68
E = 69
F = 70
G = 71
H = 72
I = 73
J = 74
K = 75
L = 76
M = 77
N = 78
O = 79
P = 80
Q = 81
R = 82
S = 83
T = 84
U = 85
V = 86
W = 87
X = 88
Y = 89
Z = 90
```

## Code Editor ⚙️

If you want to edit the code:

1. Clone the repository.
2. Install Qt Community Edition.
3. Add the `config.ini` file.
4. Open the project in Qt Creator.
5. According the ressource file with the `img` folder.
