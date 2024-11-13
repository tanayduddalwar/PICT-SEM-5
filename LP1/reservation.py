import tkinter as tk 
from tkinter import messagebox

class Railway:
    def __init__(self,root):
        self.root=root
        self.root.title("Railway Reservation System")
        self.root.geometry("400x300")

        self.name=tk.Label(root,text="Enter Train Number")
        self.name.pack(pady=10)
        self.name_entry=tk.Entry(root)
        self.name_entry.pack(pady=10)

        self.source=tk.Label(root,text="Enter Source")
        self.source.pack(pady=10)
        self.source_entry=tk.Entry(root)
        self.source_entry(pady=10)

        self.dest=tk.Label(root,text="Enter Destination")
        self.dest.pack(pady=10)
        self.dest_entry=tk.Entry(root)
        self.dest_entry(pady=10)

        self.nam=tk.Label(root,text="Enter Passenger Name")
        self.nam.pack(pady=10)
        self.nam_entry=tk.Entry(root)
        self.nam_entry(pady=10)

        self.seat=tk.Label(root,text="Select Class")
        self.seat.pack(pady=10)

        self.var=tk.StringVar(value="Sleeper")
        self.sleeper=tk.RadioButton(root,text="Sleeper",value="Sleeper",variable=self.var)
        self.sleeper.pack(pady=10)
        self.firstclass=tk.RadioButton(root,text="First Class",value="First Class",variable=self.var)
        self.firstclass.pack(pady=10)
        self.secondclass=tk.RadioButton(root,text="Second Class",value="Second Class",variable=self.var)
        self.secondclass.pack(pady=10)

        self.submit_button = tk.Button(root, text="Reserve Ticket", command=self.reserve_ticket)
        self.submit_button.pack(pady=20)

def reserve_ticket(root):
    train=self.name_entry.get()
    source=self.source_entry.get()
    destination=self.dest_entry.get()
    nam=self.name_entry.get()
    classtype=self.var.get()

    




        
    
