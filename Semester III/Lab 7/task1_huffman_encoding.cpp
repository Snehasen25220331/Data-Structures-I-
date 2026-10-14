/**
 * LAB SHEET 7 - Task 1: Huffman Encoding Engine
 * 
 * Objective:
 * Accept a set of characters and their frequencies.
 * Continually combine the lowest-frequency node pairs into a binary tree structure
 * to generate variable-length prefix codes.
 * 
 * Theory:
 * Greedy algorithm: Characters with higher frequencies get shorter binary codes,
 * while less frequent characters receive longer codes, optimizing overall transmission length.
 */

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <iomanip>

struct HuffmanNode {
    char data;
    int freq;
    HuffmanNode* left;
    HuffmanNode* right;

    HuffmanNode(char c, int f) : data(c), freq(f), left(nullptr), right(nullptr) {}
};

struct CompareNode {
    bool operator()(HuffmanNode* a, HuffmanNode* b) {
        return a->freq > b->freq; // Min-heap based on frequency
    }
};

class HuffmanEncoder {
private:
    HuffmanNode* root;
    std::map<char, std::string> huffmanCodes;
    std::map<char, int> charFreqs;

    void generateCodes(HuffmanNode* node, const std::string& code) {
        if (!node) return;

        // Leaf node contains actual character
        if (!node->left && !node->right) {
            huffmanCodes[node->data] = code.empty() ? "0" : code;
            return;
        }

        generateCodes(node->left, code + "0");
        generateCodes(node->right, code + "1");
    }

    void freeTree(HuffmanNode* node) {
        if (node) {
            freeTree(node->left);
            freeTree(node->right);
            delete node;
        }
    }

public:
    HuffmanEncoder() : root(nullptr) {}

    ~HuffmanEncoder() {
        freeTree(root);
    }

    void buildTree(const std::vector<std::pair<char, int>>& inputFreqs) {
        std::priority_queue<HuffmanNode*, std::vector<HuffmanNode*>, CompareNode> minHeap;

        for (const auto& p : inputFreqs) {
            charFreqs[p.first] = p.second;
            minHeap.push(new HuffmanNode(p.first, p.second));
        }

        std::cout << "\n--- BUILDING HUFFMAN TREE STEP-BY-STEP ---\n";
        int step = 1;

        while (minHeap.size() > 1) {
            // Extract two nodes with lowest frequencies
            HuffmanNode* left = minHeap.top(); minHeap.pop();
            HuffmanNode* right = minHeap.top(); minHeap.pop();

            std::cout << "Step " << std::setw(2) << step++ << ": Merged (" 
                      << (left->data ? std::string(1, left->data) : "*") << ":" << left->freq << ") + (" 
                      << (right->data ? std::string(1, right->data) : "*") << ":" << right->freq 
                      << ") -> Parent Node (freq=" << (left->freq + right->freq) << ")\n";

            // Create internal node with frequency equal to sum
            HuffmanNode* parent = new HuffmanNode('\0', left->freq + right->freq);
            parent->left = left;
            parent->right = right;

            minHeap.push(parent);
        }

        root = minHeap.top();
        generateCodes(root, "");
    }

    void displayCodebook() const {
        std::cout << "\n======================================================================\n";
        std::cout << "                  HUFFMAN PREFIX CODEBOOK TABLE                       \n";
        std::cout << "======================================================================\n";
        std::cout << std::left 
                  << std::setw(12) << "Character" 
                  << std::setw(14) << "Frequency" 
                  << std::setw(18) << "Huffman Code" 
                  << std::setw(14) << "Bit Length" 
                  << "\n";
        std::cout << "----------------------------------------------------------------------\n";

        int totalOriginalBits = 0;
        int totalCompressedBits = 0;

        for (const auto& pair : huffmanCodes) {
            char c = pair.first;
            std::string code = pair.second;
            int freq = charFreqs.at(c);

            totalOriginalBits += freq * 8; // 8-bit standard ASCII
            totalCompressedBits += freq * static_cast<int>(code.length());

            std::cout << std::left 
                      << std::setw(12) << (std::string("'") + c + "'") 
                      << std::setw(14) << freq 
                      << std::setw(18) << code 
                      << std::setw(14) << code.length() 
                      << "\n";
        }

        std::cout << "----------------------------------------------------------------------\n";
        std::cout << "Original Size (8-bit ASCII) : " << totalOriginalBits << " bits\n";
        std::cout << "Compressed Size (Huffman)   : " << totalCompressedBits << " bits\n";
        double savings = (1.0 - (static_cast<double>(totalCompressedBits) / totalOriginalBits)) * 100.0;
        std::cout << "Storage Space Reduction     : " << std::fixed << std::setprecision(2) 
                  << savings << "% savings\n";
        std::cout << "======================================================================\n";
    }

    std::string encode(const std::string& text) const {
        std::string encoded = "";
        for (char c : text) {
            if (huffmanCodes.count(c)) {
                encoded += huffmanCodes.at(c);
            }
        }
        return encoded;
    }

    std::string decode(const std::string& bitstream) const {
        std::string decoded = "";
        HuffmanNode* curr = root;
        for (char bit : bitstream) {
            if (bit == '0') curr = curr->left;
            else curr = curr->right;

            if (!curr->left && !curr->right) {
                decoded += curr->data;
                curr = root;
            }
        }
        return decoded;
    }
};

int main() {
    std::cout << "======================================================================\n";
    std::cout << "            LAB 7 - TASK 1: HUFFMAN ENCODING ENGINE                   \n";
    std::cout << "======================================================================\n";

    // Dataset of characters and frequencies
    std::vector<std::pair<char, int>> frequencies = {
        {'a', 45},
        {'b', 13},
        {'c', 12},
        {'d', 16},
        {'e', 9},
        {'f', 5}
    };

    HuffmanEncoder encoder;
    encoder.buildTree(frequencies);
    encoder.displayCodebook();

    // Demonstration of encoding and decoding
    std::string sample = "abacafed";
    std::string encodedBits = encoder.encode(sample);
    std::string decodedText = encoder.decode(encodedBits);

    std::cout << "\n--- ENCODING & DECODING VERIFICATION ---\n";
    std::cout << "Input String : " << sample << "\n";
    std::cout << "Encoded Bits : " << encodedBits << " (" << encodedBits.size() << " bits)\n";
    std::cout << "Decoded Text : " << decodedText << "\n";
    std::cout << "Verification : " << (sample == decodedText ? "SUCCESS (Matched!)" : "FAILED") << "\n";
    std::cout << "======================================================================\n";

    return 0;
}
