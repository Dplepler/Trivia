import socket
import json


CHUNK_SIZE = 1024
# config
IP_ADDR = '127.0.0.1'
PORT = 8008

# msg codes
LOGIN_CODE = 0
SIGNUP_CODE = 1



def createLoginData():
    username = input("Please enter username: ")
    password = input("Please enter password: ")
    data = {"username" : username, "password" : password}
    return json.dumps(data)



def createSignupData():
    username = input("Please enter username: ")
    password = input("Please enter password: ")
    email = input("Please enter email address: ")
    data = {"username" : username, "password" : password, "mail" : email}
    return json.dumps(data)



def main():


    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    try:
        sock.connect((IP_ADDR, PORT))
    
    except Exception:
        print("Server offline!")
        return


    print("Please enter wether to send login msg or signup msg:")
    print("login - 1")
    print("signup - 2")
    option = int(input("Enter option here: "))
    while(option != 1) and (option != 2):
        print("Invalid option!\nplease enter option again")
        option = input("Enter option here: ")



    if option == 1:
        jsonData = createLoginData()
        code = LOGIN_CODE
    
    else:
        jsonData = createSignupData()
        code = SIGNUP_CODE

    
    msgLen = len(jsonData)
    print(msgLen)


    fullMsg = (code).to_bytes(1, byteorder = "big") + (msgLen).to_bytes(4, byteorder = "big") + bytes(jsonData, 'utf-8')

    # try/except for cases where the connection closes in the middle of the conversation
    try:
        
        sock.send(fullMsg)

    
    except Exception:
        print("Connection with socket suddenly closed")
    
    sock.close()
        






if __name__ == '__main__':
    main()