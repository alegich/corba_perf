Simple program which calls given remote CORBA method N times.
For now it accepts only methods with string and long arguments.

**How to start**

1. Run "docker-compose -f docker-compose.yml build"
2. Start server by running "docker-compose -f docker-compose.yml up simple-server". This is default server from "corba-e2e-tests" project. Modify docker-compose.yml to use server of your interest.
3. Modify CALL_COUNT, METHOD_NAME, METHOD_ARGS, METHOD_TYPES to configure count of invocations and remote method.
	CALL_COUNT - number of invocations.
	METHOD_NAME - name of method (e.g. sendAlert).
	METHOD_ARGS - arguments values split by comma (,). 
	METHOD_TYPES - Types of arguments split by comma (,) For now only string (1) and long (2) are supported.
	IOR_INPUT_FILE - IOR file of the server, should be placed in .ior-volume/${IOR_INPUT_FILE} (by default 'server.ior').
4. Start program by running "docker-compose -f docker-compose.yml up corba_perf".
