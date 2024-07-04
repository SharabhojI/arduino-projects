import threading
import socket
import tkinter as tk
from tkinter import scrolledtext

## Configuration ##
host = ''
port = 80

## Morse Dictionary ##
MORSE_CODE_DICT = {
    '...': 'S', '---': 'O'
}

## Decode Function ##
def decode_message(msg):
    return MORSE_CODE_DICT.get(msg.strip(), 'Unknown Character')

## Transmission Function ##
def send_message():
    msg = message_entry.get()
    morse_msg = "... --- ..." # Sample Message (SOS) @TODO: Replace with conv logic
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((host, port))
        s.sendall(morse_msg.encode())
    message_entry.delete(0, tk.END)

## Receive and Decode) ##
def receive_message():
    with socket.socket(socket.AF_INET, socket.SOCK_STREAM) as s:
        s.connect((host, port))
        while True:
            data = s.recv(1024)
            if data:
                morse_msg = data.decode()
                decoded_msg = decode_message(morse_msg)
                display_text.insert(tk.END, f"Recieved: {decoded_msg}\n")

## GUI Setup ##
root = tk.Tk()
root.title("Morse Communicator")
frame = tk.Frame(root)
frame.pack(pady=20)

message_label = tk.Label(frame, text="Enter Message:")
message_label.grid(row=0, column=0, padx=10)
message_entry = tk.Entry(frame, width=50)
message_entry.grid(row=0, column=1, padx=10)
send_button = tk.Button(frame, text="Send", command=send_message)
send_button.grid(row=0, column=2, padx=10)
display_text = scrolledtext.ScrolledText(root, width=60, height=20)
display_text.pack(pady=20)

## Receive Messages in new Thread ##
receive_thread = threading.Thread(target=receive_message)
reveive_thread.start()

## Start the GUI Event Loop ##
root.mainloop()
