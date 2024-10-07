import tkinter as tk
from tkinter import messagebox, filedialog, colorchooser
import random
from PIL import Image, ImageTk, ImageFilter, ImageDraw
import os

class GlassmorphicWidget(tk.Canvas):
    def __init__(self, parent, width, height, corner_radius=20, blur_intensity=2, transparency=0.7):
        super().__init__(parent, width=width, height=height, highlightthickness=0, bg='#f0f0f0')
        self.corner_radius = corner_radius
        self.blur_intensity = blur_intensity
        self.transparency = transparency
        self.create_glassmorphic_effect()

    def create_glassmorphic_effect(self):
        image = Image.new("RGBA", (self.winfo_reqwidth(), self.winfo_reqheight()), (255, 255, 255, 0))
        draw = ImageDraw.Draw(image)
        draw.rounded_rectangle((0, 0, self.winfo_reqwidth(), self.winfo_reqheight()),
                               fill=(255, 255, 255, int(255 * self.transparency)),
                               radius=self.corner_radius)
        blurred_image = image.filter(ImageFilter.GaussianBlur(self.blur_intensity))
        self.image = ImageTk.PhotoImage(blurred_image)
        self.create_image(0, 0, anchor="nw", image=self.image)

class AuthApp(tk.Tk):
    def __init__(self):
        super().__init__()
        self.title("Three-Layer Authentication")
        self.geometry("500x400")
        self.configure(bg="#f0f0f0")

        # Set correct values (in a real app, these would be securely stored)
        self.correct_password = "password123"
        self.correct_image_path = "img/4.jpg"  # Update this with your correct image path
        self.correct_color = "#FF5733"

        self.current_layer = 1
        self.setup_ui()

    def setup_ui(self):
        self.main_frame = GlassmorphicWidget(self, 480, 380)
        self.main_frame.place(relx=0.5, rely=0.5, anchor="center")

        self.info_label = tk.Label(self.main_frame, text="Layer 1: Enter Password",
                                   font=("Helvetica", 14), bg='#f0f0f0')
        self.info_label.place(relx=0.5, rely=0.1, anchor="center")

        self.input_field = tk.Entry(self.main_frame, show="*", font=("Helvetica", 12),
                                    bg="white", relief="flat", width=20)
        self.input_field.place(relx=0.5, rely=0.4, anchor="center")

        self.submit_button = tk.Button(self.main_frame, text="Submit", command=self.check_input,
                                       font=("Helvetica", 12), bg="#4CAF50", fg="white",
                                       relief="flat", padx=10, pady=5)
        self.submit_button.place(relx=0.5, rely=0.6, anchor="center")

        self.result_label = tk.Label(self.main_frame, text="", font=("Helvetica", 12),
                                     bg='#f0f0f0', fg="#333333")
        self.result_label.place(relx=0.5, rely=0.9, anchor="center")

    def check_input(self):
        if self.current_layer == 1:
            self.check_password()
        elif self.current_layer == 2:
            self.check_image()
        elif self.current_layer == 3:
            self.open_color_dialog()

    def check_password(self):
        if self.input_field.get() == self.correct_password:
            self.result_label.config(text="Password correct! Moving to Layer 2.")
            self.current_layer = 2
            self.setup_image_layer()
        else:
            self.result_label.config(text="Incorrect password. Try again.")

    def setup_image_layer(self):
        self.info_label.config(text="Layer 2: Select the correct image")
        self.input_field.place_forget()
        self.submit_button.place_forget()

        self.image_frame = tk.Frame(self.main_frame, bg='#f0f0f0')
        self.image_frame.place(relx=0.5, rely=0.5, anchor="center")

        # List of image paths (update these with your actual image paths)
        image_paths = [
            "img/1.jpg",
            "img/2.jpg",
            "img/3.jpg",
            self.correct_image_path
        ]
        random.shuffle(image_paths)

        self.image_buttons = []
        for i, path in enumerate(image_paths):
            img = Image.open(path).resize((100, 100))
            photo = ImageTk.PhotoImage(img)
            btn = tk.Button(self.image_frame, image=photo, command=lambda p=path: self.check_image(p))
            btn.image = photo
            btn.grid(row=i//2, column=i%2, padx=5, pady=5)
            self.image_buttons.append(btn)

    def check_image(self, selected_image_path):
        if selected_image_path == self.correct_image_path:
            self.result_label.config(text="Correct image! Moving to Layer 3.")
            self.current_layer = 3
            self.setup_color_layer()
        else:
            self.result_label.config(text="Incorrect image. Try again.")

    def setup_color_layer(self):
        self.info_label.config(text="Layer 3: Select the correct color")
        self.image_frame.place_forget()
        self.submit_button.config(text="Select Color")
        self.submit_button.place(relx=0.5, rely=0.5, anchor="center")

    def open_color_dialog(self):
        color = colorchooser.askcolor(title="Choose color")[1]
        if color:
            self.check_color(color)

    def check_color(self, selected_color):
        if selected_color.upper() == self.correct_color.upper():
            self.result_label.config(text="Correct color! Authentication successful.")
            self.submit_button.config(text="Close", command=self.quit)
        else:
            self.result_label.config(text="Incorrect color. Try again.")

if __name__ == "__main__":
    app = AuthApp()
    app.mainloop()
