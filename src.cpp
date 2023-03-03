#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <bitcoin/bitcoin.hpp>

// Function to chunk transactions into 4MB chunks
std::vector<std::vector<bc::transaction>> chunk_transactions(const std::vector<bc::transaction>& transactions)
{
    std::vector<std::vector<bc::transaction>> chunks;
    std::vector<bc::transaction> current_chunk;

    size_t current_chunk_size = 0;
    for (const auto& tx : transactions)
    {
        size_t tx_size = bc::satoshi_size(bc::serialize(tx));
        if (current_chunk_size + tx_size > 4000000)
        {
            chunks.push_back(current_chunk);
            current_chunk.clear();
            current_chunk_size = 0;
        }
        current_chunk.push_back(tx);
        current_chunk_size += tx_size;
    }

    if (!current_chunk.empty())
    {
        chunks.push_back(current_chunk);
    }

    return chunks;
}

int main()
{
    // Connect to Bitcoin Core
    bc::config::endpoint endpoint("127.0.0.1", "8332");
    bc::client::obelisk_client client(endpoint);

    // Get the transactions for a given address
    bc::payment_address address("1SomeAddress");
    std::vector<bc::transaction> transactions;
    client.list_unspent(address, transactions);

    // Chunk the transactions into 4MB chunks
    std::vector<std::vector<bc::transaction>> chunks = chunk_transactions(transactions);

    // Output the chunks
    for (size_t i = 0; i < chunks.size(); ++i)
    {
        std::cout << "Chunk " << i << ":" << std::endl;
        for (const auto& tx : chunks[i])
        {
            std::cout << "  " << bc::encode_base16(bc::serialize(tx)) << std::endl;
        }
    }

    return 0;
}
