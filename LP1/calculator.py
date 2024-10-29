import tkinter as tk
from tkinter import messagebox

class Calculator:
    def __init__(self, root):
        self.root = root
        self.root.title("Calculator")
        self.root.geometry("400x400")

        # Input Frame 1
        input_frame = tk.Frame(root)
        input_frame.pack(pady=10)

        self.num1_label = tk.Label(input_frame, text="Num1:")
        self.num1_label.pack(side=tk.LEFT, pady=10)

        self.entry_num1 = tk.Entry(input_frame)
        self.entry_num1.pack(side=tk.LEFT, pady=4)

        # Input Frame 2
        input_frame2 = tk.Frame(root)
        input_frame2.pack(pady=10)

        self.label_num2 = tk.Label(input_frame2, text="Num2:")
        self.label_num2.pack(pady=10, side=tk.LEFT)

        self.entry_num2 = tk.Entry(input_frame2)
        self.entry_num2.pack(pady=10, side=tk.LEFT)

        # Result Label
        self.result_label = tk.Label(root, text="Result: ")
        self.result_label.pack(pady=10)

        # Button Frame 1
        button_frame1 = tk.Frame(root)
        button_frame1.pack(pady=5)

        self.add_button = tk.Button(button_frame1, text="ADDITION", width=15, command=self.add)
        self.add_button.pack(side=tk.LEFT, padx=10)

        self.sub_button = tk.Button(button_frame1, text="SUBTRACTION", width=15, command=self.sub)
        self.sub_button.pack(side=tk.LEFT, padx=10)

        # Button Frame 2
        button_frame2 = tk.Frame(root)
        button_frame2.pack(pady=5)

        self.multiply_button = tk.Button(button_frame2, text="MULTIPLICATION", width=15, command=self.multiply)
        self.multiply_button.pack(side=tk.LEFT, padx=10)

        self.divide_button = tk.Button(button_frame2, text="DIVISION", width=15, command=self.divide)
        self.divide_button.pack(side=tk.LEFT, padx=10)

    def add(self):
        try:
            num1 = float(self.entry_num1.get())
            num2 = float(self.entry_num2.get())
            result = num1 + num2
            self.result_label.config(text=f"Result: {result}")
        except ValueError:
            messagebox.showerror("Invalid Input", "Please enter valid numbers")

    def sub(self):
        try:
            num1 = float(self.entry_num1.get())
            num2 = float(self.entry_num2.get())
            result = num1 - num2
            self.result_label.config(text=f"Result: {result}")
        except ValueError:
            messagebox.showerror("Invalid Input", "Please enter valid numbers")

    def multiply(self):
        try:
            num1 = float(self.entry_num1.get())
            num2 = float(self.entry_num2.get())
            result = num1 * num2
            self.result_label.config(text=f"Result: {result}")
        except ValueError:
            messagebox.showerror("Invalid Input", "Please enter valid numbers")

    def divide(self):
        try:
            num1 = float(self.entry_num1.get())
            num2 = float(self.entry_num2.get())
            if num2 == 0:
                raise ZeroDivisionError
            result = num1 / num2
            self.result_label.config(text=f"Result: {result}")
        except ValueError:
            messagebox.showerror("Invalid Input", "Please enter valid numbers")
        except ZeroDivisionError:
            messagebox.showerror("Division Error", "Cannot divide by zero")

def main():
    root = tk.Tk()
    calc = Calculator(root)
    root.mainloop()

if __name__ == "__main__":
    main()
