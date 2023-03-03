# transaction-chain-chunking

Bitcoin has a maximum transaction size of 4 megabytes (MB). To add large amounts of data to the Bitcoin blockchain, chunking algorithms can be used to split the data into smaller pieces that can be added to the blockchain in separate transactions.

One such chunking algorithm is called "Merkle tree chunking." This algorithm involves splitting the data into small chunks and then hashing each chunk. The hashes are then combined into a Merkle tree, with each level of the tree representing a combination of the hashes from the level below. The top-level hash of the Merkle tree is then included in a Bitcoin transaction using the OP_RETURN opcode.

When the data needs to be retrieved from the blockchain, the top-level hash is used to prove the integrity of the data. The full data can be reconstructed by combining the individual chunks and verifying that the hashes match the ones in the Merkle tree.

Another algorithm that can be used is called "transaction chain chunking." In this method, the data is split into chunks and each chunk is added to a separate Bitcoin transaction, with each transaction referencing the previous one in the chain. The final transaction in the chain contains the full data, and the previous transactions can be used to verify the integrity of the data.

# src.cpp

This code defines a function chunk_transactions that takes a vector of transactions and returns a vector of vectors, where each inner vector represents a 4MB chunk of transactions. The function iterates through the transactions and accumulates them into a current chunk until the chunk size reaches 4MB, at which point it adds the current chunk to the list of chunks and starts a new chunk.

In the main function, the code connects to a Bitcoin Core node and retrieves the transactions for a given address using the list_unspent function. It then passes the transactions to the chunk_transactions function and outputs the resulting chunks to the console.
