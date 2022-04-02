import socket

IP_ADDR = '127.0.0.1'
PORT = 8008



def main():


    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    try:
        sock.connect((IP_ADDR, PORT))
    
    except Exception:
        print("Server offline!")
        return


    try:
        data = sock.recv(1024).decode()

        print("Incoming message: {}".format(data))

        if(data == 'HELLO'):
            sock.send('HELLO'.encode())
    
    except Exception:
        print("Connection with socket suddenly closed")
    
    sock.close()
        






if __name__ == '__main__':
    main()