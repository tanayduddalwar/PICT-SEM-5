import tkinter as tk
from tkinter import messagebox

class MarksWindow:
    def __init__(self, root):
        self.root = root
        self.root.title("Enter Marks")

        # Subject labels and entries
        self.subjects = ["Math", "Science", "English", "History", "Geography"]
        self.entries = []

        for subject in self.subjects:
            label = tk.Label(root, text=f"{subject} Marks:")
            label.pack(pady=5)
            entry = tk.Entry(root)
            entry.pack(pady=5)
            self.entries.append(entry)

        # Calculate button
        self.button_calculate = tk.Button(root, text="Calculate Percentage", command=self.calculate_percentage)
        self.button_calculate.pack(pady=20)

    def calculate_percentage(self):
        try:
            total_marks = 0
            max_marks = 100 * len(self.subjects)  # Assuming each subject is out of 100

            for entry in self.entries:
                marks = int(entry.get())
                if marks < 0 or marks > 100:
                    raise ValueError("Marks should be between 0 and 100.")
                total_marks += marks

            percentage = (total_marks / max_marks) * 100
            messagebox.showinfo("Percentage", f"Your percentage is: {percentage:.2f}%")
        except ValueError as e:
            messagebox.showerror("Invalid Input", f"Please enter valid marks. {e}")

def main():
    root = tk.Tk()
    marks_window = MarksWindow(root)
    root.mainloop()

if __name__ == "__main__":
    main()
