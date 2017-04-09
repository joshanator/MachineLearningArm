from tkinter import *
#from pynput import ket,listener
#from PyCmdMessenger import PyCmdMessenger
import PyCmdMessenger2 as PyCmdMessenger
import serial
#import sys
#sys.exit(0)
#import arduino

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

    c.send("Rotate",300)
    c.send("Wrist",200)
    c.send("Hammer")
    c.send("Return",200,300)
    #while TRUE:



submit = Button(text = "submit", command = submitLetter)
submit.pack()



root.mainloop()



