#include <iostream>
#include <unordered_map>
#include <sstream>
#include <fstream>
using namespace std;

// A map to used to encrypt each letter to a phrase only using the words,
// "click" or "clack"
//The phrases are coordinated with morse code.
//Given a each letter in morse code has unique sequences, the file should encrypt

std::unordered_map<char, std::string> CodeEncryptionKey() {
    std::unordered_map<char, std::string> key_encryption;
    key_encryption['A'] = "click clack";
    key_encryption['B'] = "clack click click click";
    key_encryption['C'] = "clack click clack click";
    key_encryption['D'] = "clack click click";
    key_encryption['E'] = "click";
    key_encryption['F'] = "click click clack click";
    key_encryption['G'] = "clack clack click";
    key_encryption['H'] = "click click click click";
    key_encryption['I'] = "click click";
    key_encryption['J'] = "click clack clack clack";
    key_encryption['K'] = "clack click clack";
    key_encryption['L'] = "click clack click click";
    key_encryption['M'] = "clack clack";
    key_encryption['N'] = "clack click";
    key_encryption['O'] = "clack clack clack";
    key_encryption['P'] = "click clack clack click";
    key_encryption['Q'] = "clack clack click clack";
    key_encryption['R'] = "click clack click";
    key_encryption['S'] = "click click click";
    key_encryption['T'] = "clack";
    key_encryption['U'] = "click click clack";
    key_encryption['V'] = "click click click clack";
    key_encryption['W'] = "click clack clack";
    key_encryption['X'] = "clack click click clack";
    key_encryption['Y'] = "clack click clack clack";
    key_encryption['Z'] = "clack clack click click";

    // A FOR loop to include the key encryption for 
    //lowercase letters
    for (char ch = 'a'; ch <= 'z'; ++ch) {
        key_encryption[ch] = key_encryption[toupper(ch)];
    }
    return key_encryption;
}


//Creating a key to decrypt our encrypted retphrases back to letters
//We will use a loop to run through each letter and phrase pairs
// and reverse the order so the phrase is the first part of the pair
// and the letter is the second part of the pairs
std::unordered_map<std::string, char> CodeDecryptionKey (
    const std::unordered_map<char, std::string>& key_encryption) {
  std::unordered_map<std::string, char> decryption_key;
  for (const auto& pair : key_encryption) {
    decryption_key[pair.second] = pair.first;
  }
  return decryption_key;
}

//Function to encrypt text files
void EncryptFile() {
    std::unordered_map<char, std::string> encryptionKey = CodeEncryptionKey();
    
    std::string input_file_name;
    std::string output_file_name;
    std::cout << "Enter the input text file name: ";
    std::cin >> input_file_name;
    std::cout << "Enter the encrypted output file name: ";
    std::cin >> output_file_name;

    std::ifstream input_file(input_file_name);
    std::ofstream output_file(output_file_name);

    if (!input_file.is_open() || !output_file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }
    
    //Create a divisor to differente which set of phrase is which letter
    char ch;
    while (input_file.get(ch)) {
        if (encryptionKey.find(ch) != encryptionKey.end()) {
            output_file << encryptionKey[ch] << " clickclack ";
        } else {
            output_file << ch;
        }
    }
    input_file.close();
    output_file.close();
    std::cout << "File was sucessfully encrypted!" << std::endl;
}

//Function to decrypt the file back into the original text
void DecryptFile() {
    std::unordered_map<char, std::string> encryption_key = CodeEncryptionKey();
    std::unordered_map<std::string, char> decryption_key = CodeDecryptionKey(encryption_key);

    std::string input_file_name;
    std::string output_file_name;
    std::cout << "Enter the encrypted input file name: ";
    std::cin >> input_file_name;
    std::cout << "Enter the decrypted output file name: ";
    std::cin >> output_file_name;

    std::ifstream input_file(input_file_name);
    std::ofstream output_file(output_file_name);

    if (!input_file.is_open() || !output_file.is_open()) {
        std::cerr << "Error opening file!" << std::endl;
        return;
    }

    std::string word;
    std::string phrase;
    while (input_file >> word) {
      if (word == "clickclack") {
        if (!phrase.empty() && decryption_key.find(phrase) != decryption_key.end()) {
          output_file << decryption_key[phrase];
        }
         phrase.clear();
      } else {
        if (!phrase.empty()) phrase += " ";
        phrase += word;
      }
    }
    
    input_file.close();
    output_file.close();
    std::cout << "File was successfully decrypted!" << std::endl;
}

int main () {
    int selection;
    std::cout << "Welcome!\nMake a choice:\n";
    std::cout << "Choose '1' to Encrypt and '2' to Decrypt\n Your choice: ";
    std::cin >> selection;

    if (selection == 1) {
        EncryptFile();
    } else if (selection == 2) {
        DecryptFile();
    } else {
        std::cout << "Invalid choice!" << std::endl;
    }

    return 0;
}