# SmartLab's light client
# Ethereum light client for smart labs
# Once the Raspberry pi is ready  and working Clone the repository and 
run the Mina.js file in case of the system running on LoRa gateway otherwise run app.js to connect to the BC.
# Install the Geth Arm7 arch on the RPI and then go to the repository folder and then run the Geth using light cliient mode

geth --light --port 30303 --networkid 6666  --datadir="data" --rpc --rpcport 8545
--rpcaddr <<your ip address>> --rpccorsdomain "*" --unlock 0 
--password="password.sec" --rpcapi "admin,eth,net,web3,personal" --lightserv 70
