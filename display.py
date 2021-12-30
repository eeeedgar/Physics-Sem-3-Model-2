import tkinter as tk
from math import *

def _create_circle(self, x, y, r, **kwargs):
    return self.create_oval(x - r, y - r, x + r, y + r, **kwargs)


def Red(lyambda):
    if 560 < lyambda <= 760:
        return 255
    elif 495 < lyambda <= 555:
        return 0
    elif 570 < lyambda <= 580:
        return int(127.5 + 127.5 * (lyambda - 570) / 10)
    elif 555 < lyambda <= 570:
        return int(127.5 * (lyambda - 555) / 15)
    elif 480 < lyambda <= 495:
        return int(127.5 - 127.5 * (lyambda - 480) / 15)
    elif 380 < lyambda <= 480:
        return int(255 - 127.5 * (lyambda - 380) / 100)


def Blue(lyambda):
    if 380 < lyambda <= 525:
        return 255
    elif 555 < lyambda <= 760:
        return 0
    elif 540 < lyambda <= 555:
        return int(127.5-127.5*(lyambda-540)/15)
    elif 525 < lyambda <= 540:
        return int(255-127.5*(lyambda-525)/15)


def Green(lyambda):
    if 525 < lyambda <= 580:
        return 255
    elif 380 < lyambda <= 495:
        return 0
    elif 610 < lyambda <= 760:
        return int(63.5-63.5*(lyambda-610)/150)
    elif 600 < lyambda <= 610:
        return int(127.5-63.5*(lyambda-600)/10)
    elif 590 < lyambda <= 600:
        return int(190.5-63.5*(lyambda-590)/10)
    elif 580 < lyambda <= 590:
        return int(255-63.5*(lyambda-580)/10)
    elif 495 < lyambda <= 510:
        return int(127.5*(lyambda-495)/15)
    elif 510 < lyambda <= 525:
        return int(127.5+127.5*(lyambda-510)/15)

def _from_rgb(rgb):
    """translates an rgb tuple of int to a tkinter friendly color code
    """
    return "#%02x%02x%02x" % rgb


def intensity(delta):
    it = 1
    return (it + it * cos(2 * pi * delta / wave_length)) / 2


with open("config.txt", 'r', encoding="utf-8") as f:
    all_data = f.read()
    lines = all_data.split('\n')
    wave_length = int(lines[2])

with open('deltas.txt', 'r', encoding="utf-8") as f:
    all_data = f.read()
    lines = all_data.split('\n')
    rads = []
    deltas = []
    for line in lines:
        if line != '':
            d = line.split(';')
            rads.append(int(float(d[0]) * 200000))
            deltas.append(int(d[1]))

    root = tk.Tk()
    canvas = tk.Canvas(root, width=800, height=800, borderwidth=0, highlightthickness=0,
                       bg="white")
    canvas.grid()

    tk.Canvas.create_circle = _create_circle

    for i in range(len(rads)):
        canvas.create_circle(400, 400, rads[i], outline=_from_rgb((int(Red(wave_length) * intensity(deltas[i])), int(Green(wave_length) * intensity(deltas[i])), int(Blue(wave_length) * intensity(deltas[i])))), width=2)


    root.title("Circles and Arcs")
    root.mainloop()
