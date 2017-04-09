from Tkinter import *
#from pynput import ket,listener
#from PyCmdMessenger import PyCmdMessenger
import PyCmdMessenger
import matlab.engine
import serial
#import sys
#sys.exit(0)
#import arduino


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



