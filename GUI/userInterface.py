from tkinter import *
#from pynput import ket,listener
import PyCmdMessenger

arduino = PyCmdMessenger.ArduinoBoard("/dev/ttyACM0",baud_rate=9600)
commands = [[]]
c = PyCmdMessenger.CmdMessenger(arduino,commands)

root = Tk()

letter = ""

label = Label(root, text="test a letter")
label.pack(side = LEFT)

input = Entry()
input.pack(side = RIGHT)

def submitLetter():
    letter = input.get()
    #while TRUE:



submit = Button(text = "submit", command = submitLetter)
submit.pack()



root.mainloop()



