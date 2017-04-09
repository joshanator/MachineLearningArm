from Tkinter import *
#from pynput import ket,listener
#from PyCmdMessenger import PyCmdMessenger
import PyCmdMessenger
import matlab.engine
import serial
#import sys
#sys.exit(0)
#import arduino

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



#future = matlab.engine.connect_matlab(async=True)
eng = matlab.engine.connect_matlab()
eng.cd(r'C:\Users\Joshua Peterson\Documents\GitHub\MachineLearningArm\MatLabScripts')
x = matlab.double([1,2,3])
y = matlab.double([1,2,3])
z = matlab.double([1,2,3])
out = eng.ConeFit(x,y,x)
print(out)



board = PyCmdMessenger.ArduinoBoard("COM4",baud_rate=9600)
commands = [["Wrist","i"],["Hammer",""],["Rotate","i"],["Return","ii"]]
c = PyCmdMessenger.CmdMessenger(board,commands)

root = Tk()

letter = ""

label = Label(root, text="test a letter")
label.pack(side = LEFT)

input = Entry()
input.pack(side = RIGHT)

def submitLetter():
    letter = input.get()
    print(letter)
    

    c.send("Rotate",500)
    c.send("Wrist", 00)
    c.send("Hammer")
    c.send("Return",00,500)
    #while TRUE:


submit = Button(text = "submit", command = submitLetter)
submit.pack()

def keyPressed(e):
    print e.char

root.bind('<KeyRelease>',keyPressed)

root.mainloop()


