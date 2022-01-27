import code
import json
import sys
if(len(sys.argv)<2):
    print("Please provide contract file")

contractFile=str(sys.argv[1])
print(contractFile)
fd=open(contractFile)
definations=json.load(fd)

codestring="import ast\nimport server_procedures as pro\nimport socket\n\n"
codestring+="func_obj = pro.procedures()\n\n"

defList=definations["remote_procedures"]
serverStubFile = open("rpc_server.py", "w")
codestring+="procedures_details = {"
total=len(defList)
funcount=0
for funcDef in defList:
    codestring+="'"+funcDef["procedure_name"]+"'"
    codestring+=":["
    paramList=funcDef["parameters"]
    count=0
    numofParams=len(paramList)
    for paramDict in paramList:
        codestring+="'"+paramDict["data_type"]+"'"
        count+=1
        if count<numofParams: 
            codestring+=","

    codestring+="]"
    funcount+=1
    if funcount<total:
        codestring+=","
codestring+="}\n\n"

codestring+="def performComputation(Client_connection):\n    request = client_connection.recv(65536).decode()\n    funcDef=ast.literal_eval(request)\n    fname=list(funcDef.keys())[-1]\n    parameters=funcDef[fname]\n    num_arguments=len(parameters)\n    if fname in procedures_details.keys():\n        client_connection.send(str(getattr(func_obj,fname)(*parameters)).encode())\n    else:\n        client_connection.send(str('Function name not in contract!!').endcode())\n\n    return True\n\n\n"
codestring+="SERVER_HOST='127.0.0.1'\nSERVER_PORT=9999\nserver_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)\nserver_socket.bind((SERVER_HOST, SERVER_PORT))\nserver_socket.listen(5)\n"
codestring+="\n\n"

codestring+="while True:\n    client_connection, client_address = server_socket.accept()\n    print('connection accepted.listening to this address ',client_address)\n    performComputation(client_connection)\n    client_connection.close()"

serverStubFile.write(codestring)
serverStubFile.close()
fd.close()