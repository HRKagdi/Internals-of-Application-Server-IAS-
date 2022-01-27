This is a simple project illustrating Remote Procedural call.
Here we can expose the functionalities implementted at the server side.
The functionilties implemented are very simple (for illustration only).

We can dynamically add services at server side.
Communication is achieved using sockets only.
Stub files at both side(server and client) are generated dynamically.

You can run the project using the following commands:-

1) Genearte client_side_stub file using the command:-       python3 client_stub_generator.py contract.json
It will generate rpc_client.py file

2) Genearte server_side_stub file using the command:-       python3 code_generator_server.py contract.json
It will generate rpc_server.py file

3) To run the server:-      python3 rpc_server.py
4) TO run the client:-      python3 client.py
