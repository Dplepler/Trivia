import socket


# config
IP_ADDR = '127.0.0.1'
PORT = 8008



def main():


    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    try:
        sock.connect((IP_ADDR, PORT))
    
    except Exception:
        print("Server offline!")
        return


    # try/except for cases where the connection closes in the middle of the conversation
    try:
        data = sock.recv(1024).decode()

        # right now the protocol isn't supported, so instead the client only reads five bytes from the server 
        # and then returns Hello to the server if he happens to get Hello from the server as well.
        print("Incoming message: {}".format(data))

        if(data == 'HELLO'):
            sock.send('HELLO'.encode())
    
    except Exception:
        print("Connection with socket suddenly closed")
    
    sock.close()
        






if __name__ == '__main__':
    main()