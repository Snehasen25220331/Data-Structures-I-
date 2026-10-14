# ==============================================================================
# LAB SHEET 7: Data Compression & File Optimization
# Syllabus Reference: Unit 7 (Lab Manual)
# Target Concepts: Huffman Tree builds, greedy merge patterns.
#
# STUDENT DETAILS:
# Name: Sneha Sen
# Student UID / Roll No: CU25220331 / 25220331
# GitHub Profile: https://github.com/Snehasen25220331
# Repository: https://github.com/Snehasen25220331/Data-Structures-I-
# Faculty Repository: https://github.com/aradhyacse/Data-Structures-I-
# Course: Data Structures & Algorithms I (Semester III)
# ==============================================================================

import heapq

# ==============================================================================
# TASK 1: Huffman Encoding Engine
# ==============================================================================
# Objective:
# Accept a set of characters and their frequencies. Continually combine
# the lowest-frequency node pairs into a binary tree structure to generate
# variable-length prefix codes.
# ==============================================================================

class HuffmanNode:
    def __init__(self, char, freq):
        self.char = char
        self.freq = freq
        self.left = None
        self.right = None

    # Comparison operator for priority queue (min-heap)
    def __lt__(self, other):
        return self.freq < other.freq

def build_huffman_tree(char_freqs):
    """
    Builds a Huffman Tree by repeatedly combining the two lowest-frequency nodes.
    """
    # Create min-heap of nodes
    heap = [HuffmanNode(ch, freq) for ch, freq in char_freqs.items()]
    heapq.heapify(heap)

    step = 1
    print("\n--- Huffman Tree Building Steps ---")
    while len(heap) > 1:
        # Extract two nodes of lowest frequency
        left = heapq.heappop(heap)
        right = heapq.heappop(heap)

        # Merge them into a new internal node
        merged_freq = left.freq + right.freq
        parent = HuffmanNode(None, merged_freq)
        parent.left = left
        parent.right = right

        ch_left = f"'{left.char}'" if left.char else "InternalNode"
        ch_right = f"'{right.char}'" if right.char else "InternalNode"
        print(f"Step {step}: Merged ({ch_left}: {left.freq}) + ({ch_right}: {right.freq}) -> Parent Freq: {merged_freq}")
        step += 1

        heapq.heappush(heap, parent)

    return heap[0] if heap else None

def generate_huffman_codes(root):
    """
    Traverses the Huffman tree to generate prefix codes (0 for left, 1 for right).
    """
    codes = {}

    def traverse(node, current_code):
        if not node:
            return
        # Leaf node
        if node.char is not None:
            codes[node.char] = current_code if current_code else "0"
            return
        traverse(node.left, current_code + "0")
        traverse(node.right, current_code + "1")

    traverse(root, "")
    return codes

def encode_text(text, codes):
    """Encodes input string into Huffman binary bitstream."""
    return "".join(codes[ch] for ch in text if ch in codes)

def decode_bitstream(bitstream, root):
    """Decodes binary bitstream back into original text using Huffman tree."""
    decoded = []
    curr = root
    for bit in bitstream:
        curr = curr.left if bit == "0" else curr.right
        if curr.char is not None:
            decoded.append(curr.char)
            curr = root
    return "".join(decoded)

def run_task1_huffman():
    print("=" * 70)
    print(" TASK 1: HUFFMAN ENCODING ENGINE - SNEHA SEN (CU25220331)")
    print("=" * 70)

    # Dataset of characters and frequencies
    frequencies = {
        'a': 45,
        'b': 13,
        'c': 12,
        'd': 16,
        'e': 9,
        'f': 5
    }

    print(f"Input Characters & Frequencies: {frequencies}")
    tree_root = build_huffman_tree(frequencies)
    codes = generate_huffman_codes(tree_root)

    print("\n" + "=" * 55)
    print(f"{'Character':<12}{'Frequency':<14}{'Huffman Code':<16}{'Bit Length':<10}")
    print("-" * 55)

    total_original_bits = 0
    total_compressed_bits = 0

    for ch in sorted(codes.keys()):
        f = frequencies[ch]
        c = codes[ch]
        total_original_bits += f * 8  # 8 bits standard ASCII
        total_compressed_bits += f * len(c)
        print(f"'{ch}':{'' :<8}{f:<14}{c:<16}{len(c):<10}")

    print("-" * 55)
    savings = (1 - (total_compressed_bits / total_original_bits)) * 100
    print(f"Original Size (8-bit ASCII) : {total_original_bits} bits")
    print(f"Compressed Size (Huffman)   : {total_compressed_bits} bits")
    print(f"Storage Space Savings       : {savings:.2f}%")
    print("=" * 55)

    # Encode & Decode demonstration
    sample_text = "abacafed"
    encoded_str = encode_text(sample_text, codes)
    decoded_str = decode_bitstream(encoded_str, tree_root)
    print(f"\nVerification:")
    print(f"Original text : {sample_text}")
    print(f"Encoded bits  : {encoded_str} ({len(encoded_str)} bits)")
    print(f"Decoded text  : {decoded_str}")
    print(f"Status        : {'SUCCESS (Exact Match!)' if sample_text == decoded_str else 'FAILED'}")


# ==============================================================================
# TASK 2: Optimal Merge Pattern Simulation
# ==============================================================================
# Objective:
# Write a routine that reads various file sizes and designs an optimal
# merge sequence that minimizes the total number of element moves.
# ==============================================================================

def optimal_merge_patterns(file_sizes):
    """
    Simulates optimal merge pattern using a Greedy Min-Heap approach.
    Minimizes total number of element move operations.
    """
    print("\n" + "=" * 70)
    print(" TASK 2: OPTIMAL MERGE PATTERN SIMULATION - SNEHA SEN (CU25220331)")
    print("=" * 70)
    print(f"Initial File Sizes: {file_sizes}")

    if not file_sizes:
        print("Empty file list provided.")
        return 0
    if len(file_sizes) == 1:
        print(f"Only 1 file present ({file_sizes[0]} elements). No merges needed.")
        return 0

    # Initialize Min-Heap
    heap = list(file_sizes)
    heapq.heapify(heap)

    total_moves = 0
    step = 1

    print("\n" + "-" * 65)
    print(f"{'Step':<8}{'Merging Files':<24}{'Step Cost':<16}{'Cumulative Moves':<16}")
    print("-" * 65)

    while len(heap) > 1:
        # Extract the two smallest files
        f1 = heapq.heappop(heap)
        f2 = heapq.heappop(heap)

        # Merge cost is sum of two file sizes
        merged_size = f1 + f2
        total_moves += merged_size

        print(f"#{step:<7}{f'{f1} + {f2}':<24}{merged_size:<16}{total_moves:<16}")
        step += 1

        # Insert merged file back into heap
        heapq.heappush(heap, merged_size)

    print("-" * 65)
    print(f"Final Merged File Size  : {heap[0]} elements")
    print(f"Total Minimum Moves     : {total_moves} operations")
    print("=" * 65)
    return total_moves


# ==============================================================================
# MAIN DRIVER EXECUTION
# ==============================================================================
if __name__ == "__main__":
    print("\n======================================================================")
    print("  DATA STRUCTURES I - PRACTICAL LAB SHEET 7 SUBMISSION")
    print("  STUDENT: SNEHA SEN | ROLL NO: CU25220331 / 25220331")
    print("======================================================================\n")

    # Run Task 1
    run_task1_huffman()

    # Run Task 2 (Test Case 1)
    optimal_merge_patterns([20, 30, 10, 5, 35])

    # Run Task 2 (Test Case 2)
    optimal_merge_patterns([2, 3, 4, 5, 6, 7])
