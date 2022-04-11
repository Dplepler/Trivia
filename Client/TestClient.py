import socket
import json
from unittest import skip


# config
IP_ADDR = '127.0.0.1'
PORT = 8008

# msg codes
LOGIN_CODE = 102
SIGNUP_CODE = 101

# General constants

CHUNK_SIZE = 1024
LOGIN_OPTION = 1
SIGNUP_OPTION = 2
HEADER_LEN = 5


# Gets Login info from the user(username, password) and serializes it to a json format string
def createLoginData():
    username = input("Please enter username: ")
    password = input("Please enter password: ")
    data = {"username" : username, "password" : password}
    return json.dumps(data)



# Gets Signup info from the user(username, password and email) and serializes it to a json format string
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


    # getting user option (Login/Signup)
    print("Please enter wether to send login msg or signup msg:")
    print("login - 1")
    print("signup - 2")
    option = int(input("Enter option here: "))
    while(option != LOGIN_OPTION) and (option != SIGNUP_OPTION):
        print("Invalid option!\nplease enter option again")
        try:
            option = input("Enter option here: ")
        
        except Exception:
            skip




    # Getting the respective info from the user based on the option
    if option == LOGIN_OPTION:
        jsonData = createLoginData()
        code = LOGIN_CODE
    
    else:
        jsonData = createSignupData()
        code = SIGNUP_CODE

    
    
    msgLen = len(jsonData)


    # Builds the full, serialized message
    fullMsg = (code).to_bytes(1, byteorder = "big") + (msgLen).to_bytes(HEADER_LEN - 1, byteorder = "big") + bytes(jsonData, 'utf-8')

    # try/except for cases where the connection closes in the middle of the conversation
    try:
        
        sock.send(fullMsg)

        msg = sock.recv(CHUNK_SIZE)
        
        # deserializes msg
        msgData = json.loads(msg)

        for(key, value) in msgData:
            print("{}: {}".format(key, value))

    
    except Exception:
        print("Connection with socket suddenly closed")
    
    sock.close()
        



if __name__ == '__main__':
    main()