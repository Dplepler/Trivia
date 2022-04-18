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
def createLoginData(username, password):
    
    data = {"username" : username, "password" : password}
    return json.dumps(data)



# Gets Signup info from the user(username, password and email) and serializes it to a json format string
def createSignupData():
    username = input("Please enter username: ")
    password = input("Please enter password: ")
    email = input("Please enter email address: ")
    data = {"username" : username, "password" : password, "mail" : email}
    return json.dumps(data)


def sendMessage(fullMsg):

    # try/except for cases where the connection closes in the middle of the conversation
    try:
        
        sock.send(fullMsg)

        msg = sock.recv(CHUNK_SIZE)

        # deserializes msg and return it
        return json.loads(msg[5: ].decode('utf-8'))

    
    except Exception:
        print("Connection with socket suddenly closed")


def buildMessage(jsonData, msgLen, code):

    # Builds the full, serialized message
    return (code).to_bytes(1, byteorder = "big") + (msgLen).to_bytes(HEADER_LEN - 1, byteorder = "big") + bytes(jsonData, 'utf-8')
    

def printServerMessage(msgData):

    for key in msgData:
        print("{} -> {}".format(key, msgData[key]))

def main():


    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    
    try:
        sock.connect((IP_ADDR, PORT))
    
    except Exception:
        print("Server offline!")
        return
    

    print("Test 1: Entering an unregistered user")
       
    jsonData = createLoginData("Shmoolik", "Shm00l1k")
    serverMsg = sendMessage(buildMessage(jsonData, len(jsonData), LOGIN_CODE))
    printServerMessage(serverMessage)
    
    print("Test 2: Trying to sign up the same user twice")
   
    jsonData = createSignupData("Nahum", "Takum")
    sendMessage(buildMessage(jsonData, len(jsonData), SIGNUP_CODE))
    
    jsonData = createSignupData("Nahum", "Takum")
    serverMsg = sendMessage(buildMessage(jsonData, len(jsonData), SIGNUP_CODE))
    printServerMessage(serverMessage)

    
    print("Test 3: Trying to log in logged user")
    
    jsonData = createLoginData("Nahum", "Takum")
    sendMessage(buildMessage(jsonData, len(jsonData), LOGIN_CODE))
    
    jsonData = createLoginData("Nahum", "Takum")
    serverMsg = sendMessage(buildMessage(jsonData, len(jsonData), LOGIN_CODE))
    printServerMessage(serverMessage)
    
    print("Test 4: entering 4 bad names")
    
    jsonData = createLoginData("", "123")
    serverMsg = sendMessage(buildMessage(jsonData, len(jsonData), LOGIN_CODE))
    printServerMessage(serverMessage)
    
    jsonData = createLoginData("123", "")
    serverMsg = sendMessage(buildMessage(jsonData, len(jsonData), LOGIN_CODE))
    printServerMessage(serverMessage)
    
    jsonData = createLoginData("123", "")
    serverMsg = sendMessage(buildMessage(jsonData, len(jsonData), SIGNUP_CODE))
    printServerMessage(serverMessage)
    
    jsonData = createLoginData("", "123")
    serverMsg = sendMessage(buildMessage(jsonData, len(jsonData), SIGNUP_CODE))
    printServerMessage(serverMessage)
    

    # Getting the respective info from the user based on the option
    if option == LOGIN_OPTION:
        jsonData = createLoginData()
        code = LOGIN_CODE
    
    else:
        jsonData = createSignupData()
        code = SIGNUP_CODE

   

    
    sock.close()
        



if __name__ == '__main__':
    main()

