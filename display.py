import tkinter as tk


def _create_circle(self, x, y, r, **kwargs):
    return self.create_oval(x - r, y - r, x + r, y + r, **kwargs)


def _from_rgb(rgb):
    """translates an rgb tuple of int to a tkinter friendly color code
    """
    return "#%02x%02x%02x" % rgb


def make_color(delta):
    if delta <= 250:
        return 250 - delta
    else:
        return delta - 250


with open('C:/Users/edgar/CLionProjects/sem-3-model-2/cmake-build-debug/deltas.txt', 'r', encoding="utf-8") as f:
    all_data = f.read()
    lines = all_data.split('\n')
    rads = []
    deltas = []
    for line in lines:
        if line != '':
            d = line.split(';')
            rads.append(int(float(d[0]) * 100000))
            deltas.append(int(d[1]))

    root = tk.Tk()
    canvas = tk.Canvas(root, width=800, height=800, borderwidth=0, highlightthickness=0,
                       bg="white")
    canvas.grid()

    tk.Canvas.create_circle = _create_circle

    for i in range(len(rads)):
        canvas.create_circle(400, 400, rads[i], outline=_from_rgb((0, make_color(deltas[i]) // 2, make_color(deltas[i]) // 2)), width=1)

    root.title("Circles and Arcs")
    root.mainloop()