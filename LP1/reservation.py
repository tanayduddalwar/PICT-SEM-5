import tkinter as tk
from tkinter import messagebox

class RailwayReservation:
    def __init__(self, root):
        self.root = root
        self.root.geometry("400x500")
        self.root.title("Railway Reservation System")
        tk.Label(root, text="Train No").pack(pady=5)
        self.train_no_entry = tk.Entry(root)
        self.train_no_entry.pack(pady=5)
        tk.Label(root, text="Source").pack(pady=5)
        self.source_entry = tk.Entry(root)
        self.source_entry.pack(pady=5)

        tk.Label(root, text="Destination").pack(pady=5)
        self.destination_entry = tk.Entry(root)
        self.destination_entry.pack(pady=5)

        tk.Label(root, text="Passenger Name").pack(pady=5)
        self.name_entry = tk.Entry(root)
        self.name_entry.pack(pady=5)
        tk.Label(root, text="Passenger Age").pack(pady=5)
        self.age_entry = tk.Entry(root)
        self.age_entry.pack(pady=5)
        tk.Label(root, text="Select Class").pack(pady=5)
        self.class_var = tk.StringVar(value="Sleeper")
        tk.Radiobutton(root, text="First Class", variable=self.class_var, value="First Class").pack()
        tk.Radiobutton(root, text="Second Class", variable=self.class_var, value="Second Class").pack()
        tk.Radiobutton(root, text="Sleeper", variable=self.class_var, value="Sleeper").pack()
        self.submit_button = tk.Button(root, text="Reserve Ticket", command=self.reserve_ticket)
        self.submit_button.pack(pady=20)

    def reserve_ticket(self):
        train_no = self.train_no_entry.get()
        source = self.source_entry.get()
        destination = self.destination_entry.get()
        name = self.name_entry.get()
        age = self.age_entry.get()
        class_type = self.class_var.get()

        if not train_no or not source or not destination or not name or not age:
            messagebox.showwarning("Input Error", "Please fill all fields.")
            return

        message = (
            f"Ticket Reserved!\n\n"
            f"Train No: {train_no}\n"
            f"Source: {source}\n"
            f"Destination: {destination}\n"
            f"Passenger Name: {name}\n"
            f"Age: {age}\n"
            f"Class: {class_type}"
        )
        messagebox.showinfo("Reservation Confirmation", message)

def main():
    root = tk.Tk()
    app = RailwayReservation(root)
    root.mainloop()

if __name__ == "__main__":
    main()
