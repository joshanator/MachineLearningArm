from Tkinter import *
import random
#from pynput import ket,listener
from PyCmdMessenger import PyCmdMessenger
import PyCmdMessenger
import matlab.engine
import serial
#import sys
#sys.exit(0)
#import arduino

pressedB = ""
pressed = FALSE
letter = ""
i = 0
x = []
y = []
z = []


def main():
    global pressedB
    global pressed
    global letter
    global i
    global x
    global y
    global z

def find_shortest_path(graph, start, end, path=[]):
    path = path + [start]
    if start == end:
        return path
    if not graph.has_key(start):
        return None
    shortest = None
    for node in graph[start]:
        if node not in path:
            newpath = find_shortest_path(graph, node, end, path)
            if newpath:
                if not shortest or len(newpath) < len(shortest):
                    shortest = newpath
    return shortest


def dist(start, end):
    graph = {
        'Q': ['A', 'W'],
        'W': ['Q', 'S', 'E'],
        'E': ['W', 'D', 'R'],
        'R': ['E', 'F', 'T'],
        'T': ['R', 'G', 'Y'],
        'Y': ['T', 'H', 'U'],
        'U': ['Y', 'J', 'I'],
        'I': ['U', 'K', 'O'],
        'O': ['I', 'L', 'P'],
        'P': ['O', ';', '['],
        'A': ['T', 'H', 'U'],
        'S': ['A', 'X', 'D', 'W'],
        'D': ['S', 'C', 'F', 'E'],
        'F': ['D', 'V', 'G', 'R'],
        'G': ['F', 'T', 'H', 'V'],
        'H': ['Y', 'G', 'B', 'J'],
        'J': ['H', 'N', 'K', 'U'],
        'K': ['J', 'M', 'L', 'I'],
        'L': ['K', 'O'],
        'Z': ['X', 'A'],
        'X': ['Z', 'C', 'S'],
        'C': ['X', 'V', 'D'],
        'V': ['C', 'B', 'F'],
        'B': ['V', 'N', 'G'],
        'N': ['B', 'M', 'H'],
        'M': ['N', 'J']
    }
    return len(find_shortest_path(graph, start, end))


def keyPressed(e):
    print e.char
    global pressedB
    global pressed
    pressedB = str(e.char)
    pressedB = pressedB.upper()
    pressed = FALSE
    if(i!=0 & pressedB.isdigit() != TRUE):
        global z
        global letter
        z.append(dist(letter, pressedB))
    if(i>=3):
        normalCommand()
    else:
        randomCommand()




def randomCommand():
    if(i==0):
        main()
        global letter
        letter = input.get()
        letter = letter.upper()
        print(letter)

    global x
    global y
    x.append(random.randrange(200, 500))
    y.append(random.randrange(200, 650))
    pressed = TRUE

    c.send("Rotate", x[i])
    c.send("Wrist", y[i])
    c.send("Hammer")
    c.send("Return", y[i], x[i])
    global i
    i += 1



def normalCommand():
    eng = matlab.engine.connect_matlab()
    eng.cd(r'C:\Users\Joshua Peterson\Documents\GitHub\MachineLearningArm\MatLabScripts')
    out = eng.ConeFit(matlab.double(x), matlab.double(y), matlab.double(z))
    print(out)
    pressed = TRUE

    minX = (out % 1000)
    out = out - minX
    minY = out/1000
    print(minX)
    print(minY)

    #print(outy)
    x.append(minX)
    y.append(minY)


    c.send("Rotate", x[i])
    c.send("Wrist", y[i])
    c.send("Hammer")
    c.send("Return", y[i], x[i])

    global i
    i += 1



#future = matlab.engine.8uuurrrrrrrrrrrrrrrrrrrrrrrrrrconnect_matlab(async=True)
main()

board = PyCmdMessenger.ArduinoBoard("COM4",baud_rate=9600)
commands = [["Wrist","i"],["Hammer",""],["Rotate","i"],["Return","ii"]]
c = PyCmdMessenger.CmdMessenger(board,commands)

root = Tk()
root.bind('<KeyRelease>', keyPressed)

label = Label(root, text="test a letter")
label.pack(side = LEFT)

input = Entry()
input.pack(side = RIGHT)

#submit = Button(text="submit", command=buttonPressed)
#submit.pack()

root.mainloop()


