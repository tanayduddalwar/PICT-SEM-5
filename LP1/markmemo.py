import tkinter as tk
from tkinter import messagebox

class MarksWindow:
    def __init__(self,root):
        self.root=root
        self.root.geometry("400x300")
        self.root.title("Marksheet")
        self.subjects=["Maths","Science","Physics"]
        self.marks_list=[]

        for i in self.subjects:
            label=tk.Label(root,text=f"Enter Marks of{i}")
            label.pack(pady=10)
            entry=tk.Entry(root)
            entry.pack(pady=10)
            self.marks_list.append(entry)
        self.click_button=tk.Button(root,text="Calculate Percentage",command=self.cal_percent)
        self.click_button.pack(pady=10)    
    def cal_percent(self):
        total_marks=0
        max_marks=100* len(self.marks_list)
        for i in self.marks_list:
            marks=int(i.get())
            total_marks=total_marks+marks
        percentage=(total_marks/max_marks)*100
        messagebox.showinfo("Percentage",f"Your percentage is{percentage}.02f%")    
def main():
    root=tk.Tk()
    window=MarksWindow(root)
    root.mainloop()


if __name__=="__main__":
    main()