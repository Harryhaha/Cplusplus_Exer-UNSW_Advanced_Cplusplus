/*
 * File: WordLadder.cpp
 * --------------------
 * Name: [TODO: word ladder by harry with supporting code]
 * This file is the starter project for the word ladder problem on Assignment #1.
 */
#include "genlib.h"
#include "lexicon.h"
#include <queue>
#include <vector>
#include <iostream>
#include <string>
#include <algorithm>
#include <unordered_map>

int main() {
    std::string start_word, goal_word;
    std::cout << "Enter start word (RETURN to quit): "; std::cin >> start_word;
    std::cout << "Enter destination word: "; std::cin >> goal_word;

    std::transform(start_word.begin(), start_word.end(), start_word.begin(), ::tolower);  // To lowercase
    std::transform(goal_word.begin(), goal_word.end(), goal_word.begin(), ::tolower);     // To lowercase

    Lexicon english_words("EnglishWords.dat");
    // No ladder if start_word or goal_word is not valid word or they are equal
    if( !english_words.containsWord(start_word) || !english_words.containsWord(goal_word) || start_word == goal_word ){
        std::cout << "No ladder found." << std::endl; return 0;
    }

    std::queue<vector<string>> queue_of_paths;      // the queue store all partial possible intermediate vector paths
    std::unordered_map<string,int> word_depth_map;  // store key-value {word: depth} for checking/avoid overlapping path
    std::vector<string> solutions;                  // All possible path(s)

    std::vector<string> start_path{start_word};
    queue_of_paths.push(start_path);
    word_depth_map[start_word] = 1;                 // The depth of start_word is 1

    bool check_flag = false;                        // Set the flag when hit the goal string to stop longer path
    size_t minimum_depth = 0;                       // Get the length of path when hit the goal string to stop longer path
    while( !queue_of_paths.empty() ){
        std::vector<string> frontest_path = queue_of_paths.front();
        std::string last_string = frontest_path.back();
        queue_of_paths.pop();                       // Pop the vector string path after retrieve it

        if( check_flag == true && frontest_path.size() == minimum_depth ) break; // Longer path should be stop checking

        for(size_t i=0; i<last_string.length(); i++){
            for(char c='a'; c<='z'; c++){
                if(c == last_string[i]) continue;

                std::string new_string = last_string;
                new_string[i] = c;
                if( new_string == goal_word ){       // Hit the goal string
                    check_flag = true;
                    minimum_depth = frontest_path.size()+1;

                    string path_of_solution("");
                    for(auto iter=frontest_path.begin(); iter!=frontest_path.end(); iter++){
                        path_of_solution += *iter + " ";
                    }
                    path_of_solution += new_string;   // Concatenate the subpath vector to be a whole string
                    solutions.push_back(path_of_solution);
                    break;
                }

                int depth_of_newStr = frontest_path.size()+1;  // Get the depth of the new string
                if( english_words.containsWord(new_string) &&
                    (depth_of_newStr <= word_depth_map[new_string] || word_depth_map[new_string]==0 ) ){
                    // This new term is a word && it is not in longer ladder than previous one(s) if it exists
                    word_depth_map[new_string] = depth_of_newStr;
                    std::vector<string> new_path(frontest_path);
                    new_path.push_back(new_string);
                    queue_of_paths.push(new_path);             // Push it into the path queue
                }
            }
        }
    }

    if( solutions.size() == 0 ){
        std::cout << "No ladder found." << std::endl;
    } else {
        std::sort(solutions.begin(), solutions.end());
        std::cout << "Found ladder: ";
        for(auto iter=solutions.begin(); iter!=solutions.end(); iter++){
            std::cout << *iter << std::endl;
        }
    }

    return 0;
}
