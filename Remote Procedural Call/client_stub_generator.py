import json
import sys
if(len(sys.argv)<2):
    print("Please provide contract file")

contractFile=str(sys.argv[1])
fd=open(contractFile)
definations=json.load(fd)
defList=definations["remote_procedures"]
clientStubFile = open("rpc_client.py", "w")

defList=definations["remote_procedures"]
serverStubFile = open("rpc_client.py", "w")
codestring="procedures_details = {"
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


clientStubFile.write(codestring)
clientStubFile.close()
fd.close()
