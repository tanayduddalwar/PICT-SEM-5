import tkinter as tk
from tkinter import messagebox

class CustomerFeedbackForm:
    def __init__(self, root):
        self.root = root
        self.root.title("Customer Feedback Form")

        # Customer Name
        self.label_name = tk.Label(root, text="Name:")
        self.label_name.pack(pady=10)
        self.entry_name = tk.Entry(root, width=30)
        self.entry_name.pack(pady=10)

        # Feedback Text
        self.label_feedback = tk.Label(root, text="Feedback:")
        self.label_feedback.pack(pady=10)
        self.text_feedback = tk.Text(root, height=5, width=40)
        self.text_feedback.pack(pady=10)

        # Quality Section
        self.quality_frame = tk.Frame(root)
        self.quality_frame.pack(pady=10)  # Packs vertically

        self.quality_label = tk.Label(self.quality_frame, text="Quality")
        self.quality_label.pack(pady=5)

        self.sports_rating = tk.IntVar()

        self.quality_excellent = tk.Checkbutton(
            self.quality_frame, text="Excellent", 
            variable=self.sports_rating, onvalue=5
        )
        self.quality_excellent.pack(side=tk.LEFT, padx=5)

        self.quality_good = tk.Checkbutton(
            self.quality_frame, text="Good", 
            variable=self.sports_rating, onvalue=4
        )
        self.quality_good.pack(side=tk.LEFT, padx=5)

        self.quality_poor = tk.Checkbutton(
            self.quality_frame, text="Poor", 
            variable=self.sports_rating, onvalue=3
        )
        self.quality_poor.pack(side=tk.LEFT, padx=5)

        # Hygiene Section
        self.hygiene_frame = tk.Frame(root)
        self.hygiene_frame.pack(pady=10) 
         # Below the Quality section
        self.hygiene_rating = tk.IntVar()

        self.hygiene_label = tk.Label(self.hygiene_frame, text="Hygiene")
        self.hygiene_label.pack(pady=5)

        self.hygiene_excellent = tk.Checkbutton(
            self.hygiene_frame, text="Excellent", 
            variable=self.hygiene_rating, onvalue=5
        )
        self.hygiene_excellent.pack(side=tk.LEFT, padx=5)

        self.hygiene_good = tk.Checkbutton(
            self.hygiene_frame, text="Good", 
            variable=self.hygiene_rating, onvalue=4
        )
        self.hygiene_good.pack(side=tk.LEFT, padx=5)

        self.hygiene_poor = tk.Checkbutton(
            self.hygiene_frame, text="Poor", 
            variable=self.hygiene_rating, onvalue=3
        )
        self.hygiene_poor.pack(side=tk.LEFT, padx=5)

        # Submit Button
        self.submit_button = tk.Button(root, text="Submit", command=self.submitfunc)
        self.submit_button.pack(padx=15, pady=10)

    def submitfunc(self):
        # Retrieve values
        name = self.entry_name.get()
        feedback = self.text_feedback.get("1.0", tk.END)
          # Get all text from the Text widget
        quality=self.sports_rating.get()
        hyg=self.hygiene_rating.get()

        # Displaying a message box with the input values
        messagebox.showinfo(
            "Feedback Submitted",
            f"Name: {name}\nFeedback: {feedback}\nQuality: {quality}\nHygiene: {hyg}"
        )

def main():
    root = tk.Tk()
    feedback = CustomerFeedbackForm(root)
    root.mainloop()

if __name__ == '__main__':
    main()
